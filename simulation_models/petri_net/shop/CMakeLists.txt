add_executable(Shop_petri_net
        src/main_shop_petri_net.cpp # this could be simplified to main.cpp
        src/manager.cpp
        src/customer.cpp
        src/shop.cpp
        src/line.cpp
        src/cash.cpp
        src/graph.cpp
)

target_link_libraries(
        Shop_petri_net PRIVATE Simulation_interface
)