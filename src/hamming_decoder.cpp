#include "../include/hamming_decoder.h"
#include "../include/utils.h"

TypeOfCode HammingDecoder::GetType() {
    return TypeOfCode::kHamming;
}

int HammingDecoder::Decode(Code &code) {
    size_t length = code.GetLength();
    size_t new_length = length - CountPowerOfTwo(length);

    bool *input_code = code.GetCode();
    bool *help_code = new bool[new_length];

    int index = 0, step = 0;

    for (size_t i = 1; i <= length; ++i) {
        if (IsItPowerOfTwo(i)) {
            bool control_bit = false;
            size_t j = i - 1;
            while (j <= length) {
                for (size_t k = j; k < j + i && k < length; ++k) {
                    control_bit ^= input_code[k];
                }

                j += 2 * i;
            }
            index += Power(2, step) * control_bit;
            step++;
        }
    }

    if (index != 0)
        input_code[index - 1] ^= 1;

    for (size_t i = 1, p = 0; i <= length; ++i) {
        if (!IsItPowerOfTwo(i)) {
            help_code[p++] = input_code[i - 1];
        }
    }

    delete[] input_code;
    code.SetCode(help_code);
    code.SetLength(new_length);
    return index;
}