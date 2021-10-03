#ifndef LINEARCODES_STATISTICS_H
#define LINEARCODES_STATISTICS_H

#include "encoder.h"
#include "decoder.h"
#include "utils.h"
#include <vector>

struct Stats {
    int SummaryCountErrors;
    int FoundedErrorsCount;
    int FixesCount;
    double FindingRate;  // = founded / summary
    double FixingRate; // = fixes / summary
};

class Statistics {
private:
    std::vector<Stats> stats;

    void ApplyErrorCode(Code &code_param, int position);

    int CountUnitBits(int number);

    int GetBits(int number, std::vector<short> &result);

public:
    std::vector<Stats> GetStats(Code &code, Encoder *encoder, Decoder *decoder);
};

#endif //LINEARCODES_STATISTICS_H
