#ifndef _PREDICTOR_H_
#define _PREDICTOR_H_

#include "utils.h"
#include "tracer.h"
#include <bitset>

#define UINT16 unsigned short int

class PREDICTOR
{
private:
  bitset<59> ghr;
  int table[512][60];
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
