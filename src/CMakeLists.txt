# src/CarParkSimLib/CMakeLists.txt

# Collect all .cpp files in this folder
file(GLOB CARPARK_SOURCES
    CarParkSimLib/*.cpp
)

add_library(libcarparksim STATIC ${CARPARK_SOURCES})

target_include_directories(libcarparksim
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(libcarparksim PUBLIC cxx_std_20)
