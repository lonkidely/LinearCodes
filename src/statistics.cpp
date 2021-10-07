#include "../include/statistics.h"
#include "../include/utils.h"
#include <numeric>

void Statistics::ApplyErrorCode(Code &code_param, int position) {
    code_param.SetBit(position, code_param.GetBit(position) ^ 1);
}

//new result = old_result + 1 in binary code
int Statistics::GetBits(std::vector<int> &result) {
    int k = 1;
    for (size_t i = 0; i < result.size() && k; ++i) {
        result[i] = result[i] ^ k;
        k = result[i] ^ k;
    }
    return std::accumulate(result.begin(), result.end(), 0);
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

    std::vector<int> bits(length, 0);
    int cnt = 0;
    for (int i = 1; i <= max_number; ++i) {
        cnt = GetBits(bits);
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
        stats[cnt - 1].FixesCount += (Code::AreCodesEqual(decoded, code) ? 1 : 0);
    }
    for (int freq = 1; freq <= length; ++freq) {
        stats[freq - 1].FindingRate =
                (double) stats[freq - 1].FoundedErrorsCount / (double) stats[freq - 1].SummaryCountErrors;
        stats[freq - 1].FixingRate = (double) stats[freq - 1].FixesCount / (double) stats[freq - 1].SummaryCountErrors;
    }
    return stats;
}