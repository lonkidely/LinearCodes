cmake_minimum_required(VERSION 3.16)
project(LinearCodes)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -pedantic -Werror)

add_executable(LinearCodes src/main.cpp src/controller.h src/encoders/encoder.h src/factory.h src/encoders/hamming_encoder.h src/decoders/decoder.h src/decoders/hamming_decoder.h src/ui/cli.h src/ui/cli.cpp src/controller.cpp src/ui/ui.h src/code/code.h src/factory.cpp src/encoders/hamming_encoder.cpp src/decoders/hamming_decoder.cpp src/encoders/cyclic_encoder.h src/decoders/cyclic_decoder.h src/decoders/cyclic_decoder.cpp src/encoders/cyclic_encoder.cpp src/code/hamming_code.cpp src/code/hamming_code.h src/code/cyclic_code.cpp src/code/cyclic_code.h src/code/binary_code.cpp src/code/binary_code.h)
