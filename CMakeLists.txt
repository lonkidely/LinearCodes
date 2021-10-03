cmake_minimum_required(VERSION 3.20)
project(LinearCodes)

set(CMAKE_CXX_STANDARD 17)

add_executable(LinearCodes src/main.cpp include/controller.h include/encoder.h include/factory.h include/hamming_encoder.h include/decoder.h include/hamming_decoder.h include/statistics.h include/cli.h src/cli.cpp src/controller.cpp include/ui.h include/code.h src/code.cpp src/factory.cpp src/hamming_encoder.cpp src/hamming_decoder.cpp src/utils.cpp include/utils.h src/statistics.cpp)
