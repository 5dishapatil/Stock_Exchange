cmake_minimum_required(VERSION 3.24) #handles better fetch content than previous versions

project(stock_exchange LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# include(Dependencies)

add_library(stock_exchange_project INTERFACE)

target_include_directories(
    stock_exchange_project
    INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_features(stock_exchange_project INTERFACE cxx_std_20)

if(MSVC)
    target_compile_options(
        stock_exchange_project
        INTERFACE
        /W4
    )

else()
    target_compile_options(
        stock_exchange_project
        INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -fno-exceptions
    )
endif()

# we are not using any external libraries, so we don't need to link anything here. and we are doing this because we want to use the stock_exchange_project as an interface library, which means that it will not be built into a binary, but rather it will be used to provide include directories and compile options to other targets that link against it.
# and try catch can silently go through an invisible door, or run to the L2 Cache instead of the L1i Cache, which makes the latency go up.
# since exception handling would be more costly, we avoid it altogether, and return a value if errors are caught or simply abort the program.

add_executable(
    stock_exchange
    src/stock_exchange_main.cpp
)

target_link_libraries(
    stock_exchange
    PRIVATE 
    stock_exchange_project   
)

set_target_properties(
    stock_exchange
    PROPERTIES 
    OUTPUT_NAME "stock_exchange"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/src"
)

add_executable(
    trader_terminal
    tools/trader_terminal.cpp
)

target_link_libraries(
    trader_terminal
    PRIVATE
    stock_exchange_project
)

set_target_properties(
    trader_terminal
    PROPERTIES
    OUTPUT_NAME "trader terminal"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tools"
)

add_executable(
    liquidity_bot
    tools/liquidity_bot.cpp 
)

target_link_libraries(
    liquidity_bot
    PRIVATE 
    stock_exchange_project
)

set_target_properties(
    liquidity_bot
    PROPERTIES 
    OUTPUT_NAME "liquidity_bot"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tools"
)

