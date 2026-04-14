add_executable(carpark_demo main.cpp)

target_link_libraries(carpark_demo
    PRIVATE
        libcarparksim
)
