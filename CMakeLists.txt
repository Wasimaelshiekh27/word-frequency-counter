project(word-frequency-counter)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(word-frequency-counter src/main.cpp src/word_counter.cpp)