#include "../include/hamming_encoder.h"
#include "../include/utils.h"

TypeOfCode HammingEncoder::GetType() {
    return TypeOfCode::kHamming;
}

void HammingEncoder::Encode(Code &code) {
    int add = static_cast<int>(CountPowerOfTwo(code.GetLength()));
    if (Power(2, add) <= static_cast<int>(code.GetLength()) + add) add++;

    size_t new_length = code.GetLength() + add;

    bool *old_code = code.GetCode();
    bool *new_code = new bool[new_length];
    for (size_t i = 1, j = 0; i <= new_length; ++i) {
        new_code[i - 1] = false;
        if (!IsItPowerOfTwo(i))
            new_code[i - 1] = old_code[j++];
    }

    for (size_t i = 1; i <= new_length; ++i) {
        if (IsItPowerOfTwo(i)) {
            size_t j = i - 1;
            while (j <= new_length) {
                for (size_t k = j; k < j + i && k < new_length; ++k) {
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