add_executable(Shop_reactive
    src/main_shop_reactive.cpp # this could be simplified to main.cpp
    src/manager.cpp
    src/customer.cpp
    src/shop.cpp
    src/line.cpp
    src/cash.cpp
    src/graph.cpp
)

target_link_libraries(
    Shop_reactive PRIVATE Simulation_interface
)
