cmake_minimum_required(VERSION 3.20)
project(LinearCodes)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(LinearCodes src/main.cpp src/controller.h src/encoders/encoder.h src/factory.h src/encoders/hamming_encoder.h src/decoders/decoder.h src/decoders/hamming_decoder.h src/ui/cli.h src/ui/cli.cpp src/controller.cpp src/ui/ui.h src/code/code.h src/code/code.cpp src/factory.cpp src/encoders/hamming_encoder.cpp src/decoders/hamming_decoder.cpp src/utils.cpp src/utils.h src/encoders/cyclic_encoder.h src/decoders/cyclic_decoder.h src/decoders/cyclic_decoder.cpp src/encoders/cyclic_encoder.cpp)
