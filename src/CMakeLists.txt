# src/CarParkSimLib/CMakeLists.txt

# Collect all .cpp and header files in this folder (non-recursive)
file(GLOB CARPARK_SOURCES CONFIGURE_DEPENDS
    "CarParkSimLib/*.cpp"
    "CarParkSimLib/*.cxx"
)

file(GLOB CARPARK_HEADERS CONFIGURE_DEPENDS
    "CarParkSimLib/*.h"
    "CarParkSimLib/*.hpp"
)

# Sort lists for deterministic ordering
list(SORT CARPARK_SOURCES)
list(SORT CARPARK_HEADERS)

# Create static library from the collected source files (CPP files will be listed in generated project)
add_library(libcarparksim STATIC ${CARPARK_SOURCES})

# Add headers to the target so IDEs / solution explorers show them
if(CARPARK_HEADERS)
    target_sources(libcarparksim PUBLIC ${CARPARK_HEADERS})
endif()

target_include_directories(libcarparksim
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(libcarparksim PUBLIC cxx_std_20)
