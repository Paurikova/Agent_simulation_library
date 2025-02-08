
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <vector>

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

void drawBarChart(sf::RenderWindow& window, std::vector<int>& data);

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dynamic Bar Chart");

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Initial data (values of the bars)
    std::vector<int> data = {5, 8, 3, 6, 10};

    // Clock to control the time between updates
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update data every 1 second
        if (clock.getElapsedTime().asSeconds() >= 1.0f) {
            // Generate random values for the bars (range from 1 to 15)
            for (auto& value : data) {
                value = std::rand() % 15 + 1;  // Random values between 1 and 15
            }

            // Reset the clock to track the next update time
            clock.restart();
        }

        // Clear the window with a background color
        window.clear(sf::Color::White);

        // Draw the bar chart
        drawBarChart(window, data);

        // Display the window content
        window.display();
    }

    return 0;
}

void drawBarChart(sf::RenderWindow& window, std::vector<int>& data) {
    float barWidth = 50.f;
    float spaceBetweenBars = 20.f;

    // Load the system font (DejaVu Sans as a default on Linux)
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Failed to load DejaVuSans font!" << std::endl;
        return;
    }

    // Draw bars
    for (size_t i = 0; i < data.size(); ++i) {
        // Create a rectangle shape for each bar
        sf::RectangleShape bar(sf::Vector2f(barWidth, -data[i] * 10)); // Height scaled by 10

        // Position the bar
        bar.setPosition(i * (barWidth + spaceBetweenBars) + 100.f, window.getSize().y - 50);

        // Set the color of the bar (gradient from green to blue)
        int blueValue = (data[i] * 25) % 255;  // Gradually change the blue intensity based on data value
        bar.setFillColor(sf::Color(0, 0, blueValue));  // Green to Blue variation

        // Draw the bar
        window.draw(bar);

        // Display the value on top of each bar
        sf::Text text;
        text.setString(std::to_string(data[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);

        // Set position for the value text above the bar
        // Adjust the y position so it's above the bar
        text.setPosition(bar.getPosition().x + barWidth / 2 - text.getLocalBounds().width / 2,
                         bar.getPosition().y - text.getLocalBounds().height - 5);

        // Draw the number on top of the bar
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
    title.setString("Dynamic Bar Chart");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::Black);

    title.setFont(font);

    title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 20.f);
    window.draw(title);

    // Draw column names (x-axis labels)
    for (size_t i = 0; i < data.size(); ++i) {
        std::ostringstream columnText;
        columnText << "C" << i + 1;

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