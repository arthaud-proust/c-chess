cmake_minimum_required(VERSION 3.29)
project(chess C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        Tau
        URL https://github.com/jasmcaus/tau/archive/dev.zip
)

FetchContent_MakeAvailable(Tau)

add_executable(host main.c
        core.c
        socket.c
        socket.h
        ui.c
        ui.h)

add_executable(client main.c
        core.c
        socket.c
        socket.h
        ui.c
        ui.h)

enable_testing()

add_executable(
        Test
        core.c
        test.c
)

target_link_libraries(
        Test
        Tau
)
