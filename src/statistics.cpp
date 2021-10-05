#include "../include/statistics.h"
#include "../include/utils.h"

void Statistics::ApplyErrorCode(Code &code_param, int position) {
    code_param.SetBit(position, code_param.GetBit(position) ^ 1);
}

int Statistics::CountUnitBits(int number) {
    int cnt = 0;
    while (number) {
        if (number & 1)
            cnt++;
        number >>= 1;
    }
    return cnt;
}

int Statistics::GetBits(int number, std::vector<short> &result) {
    int cnt = 0;
    int k = 0;
    while (number) {
        result[k++] = number % 2;
        cnt += (number % 2);
        number /= 2;
    }
    return cnt;
}

std::vector<Stats> Statistics::GetStats(Code &code, Encoder *encoder, Decoder *decoder) {
    Code encoded(code);
    encoder->Encode(encoded);
    int length = encoded.GetLength();

    stats.clear();
    stats.resize(length);
    int max_number = 0;
    for (int freq = 1; freq <= length; ++freq) {
        max_number += Power(2, freq - 1);
        stats[freq - 1].SummaryCountErrors = CountCombinations(length, freq);
    }

    std::vector<short> bits(length, 0);
    int cnt = 0;
    for (int i = 1; i <= max_number; ++i) {
        std::fill(bits.begin(), bits.end(), 0);
        cnt = GetBits(i, bits);
        for (int j = 0; j < length; ++j) {
            if (bits[j])
                ApplyErrorCode(encoded, j);
        }
        Code decoded(encoded);
        bool error = decoder->Decode(decoded);
        for (int j = 0; j < length; ++j) {
            if (bits[j])
                ApplyErrorCode(encoded, j);
        }

        stats[cnt - 1].FoundedErrorsCount += error;
        stats[cnt - 1].FixesCount += (decoded.AreCodesEqual(decoded, code) ? 1 : 0);
    }
    for (int freq = 1; freq <= length; ++freq) {
        stats[freq - 1].FindingRate =
                (double) stats[freq - 1].FoundedErrorsCount / (double) stats[freq - 1].SummaryCountErrors;
        stats[freq - 1].FixingRate = (double) stats[freq - 1].FixesCount / (double) stats[freq - 1].SummaryCountErrors;
    }
    return stats;
}