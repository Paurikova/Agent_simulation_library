#include "graph.h"

void Graph::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a background color
        window.clear(sf::Color::White);

        //create data
        std::vector<float> data;
        data.push_back(stateShop->custInShop);  // current number of customers in shop
        data.push_back(stateShop->custInLine[0]); // current number of customers in line 1
        data.push_back(stateShop->custInLine[1]); //current number of customers in line 2
        data.push_back(stateShop->shoppingTime/stateShop->customers);  // mean shopping time
        data.push_back(stateShop->waitingTime[0]/stateShop->totalCustInLine[0]); // mean waiting time line 1
        data.push_back(stateShop->waitingTime[1]/stateShop->totalCustInLine[1]); //mean waiting time line 2
        data.push_back((stateShop->shoppingTime + stateShop->waitingTime[0] + stateShop->waitingTime[1] +
        stateShop->payedTime[0] + stateShop->payedTime[1])/stateShop->customers); // mean spending time in shop
        // Draw the bar chart
        drawBarChart(data);

        // Display the window content
        window.display();
    }
    //TODO send
}

void Graph::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        draw(pSender, pReceiver, pExecTime, state);
    });

void Graph::drawBarChart(std::vector<float>& data) {
    float barWidth = 50.f;
    float spaceBetweenBars = 20.f;

    // Draw bars
    for (size_t i = 0; i < data.size(); ++i) {
        // Create a rectangle shape for each bar
        sf::RectangleShape bar(sf::Vector2f(barWidth, -data[i] * 10)); // Height scaled by 10

        // Position the bar
        bar.setPosition(i * (barWidth + spaceBetweenBars) + 100.f, window.getSize().y - 50);

        // Set the color of the bar
        int blueValue = (data[i] * 25) % 255;  // Gradually change the blue intensity based on data value
        bar.setFillColor(sf::Color(0, 0, blueValue));  // Green to Blue variation

        // Draw the bar
        window.draw(bar);

        // Display the value on top of each bar
        sf::Text text;
        text.setString(std::to_string(data[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);

        // Load the system font (DejaVu Sans as a default on Linux)
        if (!text.getFont()) {
            sf::Font font;
            if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
                std::cerr << "Failed to load DejaVuSans font!" << std::endl;
                return;
            }
            text.setFont(font);
        }

        // Set position for the value text above the bar
        text.setPosition(bar.getPosition().x + barWidth / 2 - text.getLocalBounds().width / 2,
                         bar.getPosition().y - text.getLocalBounds().height - 5);

        window.draw(text);
    }

    // Draw X and Y axis lines
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(100.f, window.getSize().y - 50.f);
    xAxis[1].position = sf::Vector2f(window.getSize().x - 50.f, window.getSize().y - 50.f);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].color = sf::Color::Black;
    window.draw(xAxis);

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(100.f, window.getSize().y - 50.f);
    yAxis[1].position = sf::Vector2f(100.f, 50.f);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].color = sf::Color::Black;
    window.draw(yAxis);

    // Draw Title
    sf::Text title;
    title.setString("Shop simulation");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Black);

    // Use a system font (DejaVu Sans or fallback)
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Failed to load DejaVuSans font!" << std::endl;
        return;
    }
    title.setFont(font);

    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 20.f);
    window.draw(title);

    // Draw column names (x-axis labels)
    for (size_t i = 0; i < names.size(); ++i) {
        std::ostringstream columnText;
        columnText << "C" << i;

        sf::Text columnLabel(columnText.str(), font, 20);
        columnLabel.setFillColor(sf::Color::Black);
        columnLabel.setPosition(i * (barWidth + spaceBetweenBars) + 100.f + barWidth / 2 - columnLabel.getLocalBounds().width / 2,
                                window.getSize().y - 30.f);
        window.draw(columnLabel);
    }

    // Draw Y axis values (scale them)
    for (int i = 0; i <= 10; ++i) {
        std::ostringstream yValue;
        yValue << i * 10;  // Scale 10 times to fit the chart

        sf::Text yText(yValue.str(), font, 20);
        yText.setFillColor(sf::Color::Black);
        yText.setPosition(60.f, window.getSize().y - 50.f - i * 40);  // Position Y values along the Y-axis
        window.draw(yText);
    }
}