#include "../include/hamming_decoder.h"
#include <iostream>
#include <algorithm>

TypeOfCode HammingDecoder::GetType() {
    return kHamming;
}

int HammingDecoder::Decode(Code &code) {
    int length = code.GetLength();
    int new_length = length - CountPowerOfTwo(length);

    bool *input_code = code.GetCode();
    bool *help_code = new bool[new_length];

    int index = 0, step = 0;

    for (int i = 1; i <= length; ++i) {
        if (IsItPowerOfTwo(i)) {
            bool control_bit = false;
            int j = i - 1;
            while (j <= length) {
                for (int k = j; k < j + i && k < length; ++k) {
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

    for (int i = 1, p = 0; i <= length; ++i) {
        if (!IsItPowerOfTwo(i)) {
            help_code[p++] = input_code[i - 1];
        }
    }

    delete[] input_code;
    code.SetCode(help_code);
    code.SetLength(new_length);
    return index != 0;
}