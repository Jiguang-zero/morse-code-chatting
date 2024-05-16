cmake_minimum_required(VERSION 3.26)
project(morseCodeChatting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(morseCodeChatting main.cpp
        utils/Logger.h
        utils/Logger.cpp
        utils/myDate.h
        utils/myDate.cpp
        morse_tree/MorseCodeTree.cpp
        morse_tree/MorseCodeTree.h
        network/client.h
        input/Input.cpp
        input/Input.h
)
target_link_libraries(morseCodeChatting ws2_32.lib)

add_executable(morseCodeChattingServer network/server.cpp)
target_link_libraries(morseCodeChattingServer ws2_32.lib)