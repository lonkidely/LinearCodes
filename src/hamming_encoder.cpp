#include "../include/hamming_encoder.h"

TypeOfCode HammingEncoder::GetType() {
    return kHamming;
}

void HammingEncoder::Encode(Code &code) {
    int add = CountPowerOfTwo(code.GetLength());
    if (Power(2, add) <= code.GetLength() + add) add++;

    int new_length = code.GetLength() + add;

    bool *old_code = code.GetCode();
    bool *new_code = new bool[new_length];
    for (int i = 1, j = 0; i <= new_length; ++i) {
        new_code[i - 1] = 0;
        if (!IsItPowerOfTwo(i))
            new_code[i - 1] = old_code[j++];
    }

    for (int i = 1; i <= new_length; ++i) {
        if (IsItPowerOfTwo(i)) {
            int j = i - 1;
            while (j <= new_length) {
                for (int k = j; k < j + i && k < new_length; ++k) {
                    new_code[i - 1] = new_code[i - 1] ^ new_code[k];
                }

                j += 2 * i;
            }
        }
    }
    code.SetCode(new_code);
    code.SetLength(new_length);
    delete[] old_code;
}