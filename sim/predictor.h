#ifndef _PREDICTOR_H_
#define _PREDICTOR_H_

#include "utils.h"
#include "tracer.h"
#include <bitset>

#define UINT16 unsigned short int

// Total predictor storage should not exceed 128KB.

/////////////// HARDWARE BUDGET ////////////////
// Budget: 128 KB
//
// GHR: 59 bits
// Table: 512 * (59 + 1) * 8 bits
//
// 59 bits + 512 * 60 * 8 bits ≈ 30 KB
////////////////////////////////////////////////

class PREDICTOR
{
private:
  bitset<59> ghr;
  // Use int8_t instead of int to fit more perceptrons under budget
  int8_t table[512][60];
  int y;

public:
  // The interface to the four functions below CAN NOT be changed

  PREDICTOR(void);
  bool GetPrediction(UINT32 PC);
  void UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget);
  void TrackOtherInst(UINT32 PC, OpType opType, UINT32 branchTarget);

  // Contestants can define their own functions below
  UINT32 Hash(UINT32 PC);
};

#endif
