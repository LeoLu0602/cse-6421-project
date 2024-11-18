#ifndef _PREDICTOR_H_
#define _PREDICTOR_H_

#include "utils.h"
#include "tracer.h"
#include <bitset>
#include <cmath>

#define UINT16 unsigned short int
#define HIST_LEN 62   // history length
#define TABLE_LEN 512 // table length
#define THRESHOLD floor(1.93 * HIST_LEN + 14)

class PREDICTOR
{
private:
  bitset<HIST_LEN> ghr;
  int table[TABLE_LEN][HIST_LEN + 1];
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
