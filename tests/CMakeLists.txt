if (BUILD_TESTING)

    include(FetchContent)

    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.0
    )
    FetchContent_MakeAvailable(catch2)

    add_executable(carparksim_tests
        Car_test.cpp
        TicketManager_test.cpp)

    target_link_libraries(carparksim_tests
        PRIVATE
            libcarparksim
            Catch2::Catch2WithMain
    )

    add_test(NAME CarParkSimTests COMMAND carparksim_tests)

endif()