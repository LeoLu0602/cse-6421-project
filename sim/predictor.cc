#include "predictor.h"

// Total predictor storage should not exceed 128KB.

PREDICTOR::PREDICTOR(void)
{
  ghr = bitset<HIST_LEN>();

  for (int i = 0; i < TABLE_LEN; i++)
  {
    for (int j = 0; j < HIST_LEN; j++)
    {
      table[i][j] = 0;
    }
  }

  y = 0;
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

UINT32 PREDICTOR::Hash(UINT32 PC)
{
  return PC % TABLE_LEN;
}
