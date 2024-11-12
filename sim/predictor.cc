#include "predictor.h"

PREDICTOR::PREDICTOR(void)
{
}

bool PREDICTOR::GetPrediction(UINT32 PC)
{
  return true;
}

void PREDICTOR::UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget)
{
}

void PREDICTOR::TrackOtherInst(UINT32 PC, OpType opType, UINT32 branchTarget)
{
  // This function is called for instructions which are not
  // conditional branches, just in case someone decides to design
  // a predictor that uses information from such instructions.
  // We expect most contestants to leave this function untouched.
}
