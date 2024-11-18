#include "predictor.h"
#include <cstdlib> // For abs()

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
  UINT32 index = Hash(PC);

  // x0 is always set to 1, providing a "bias" input
  y = table[index][0];

  for (int i = 1; i < HIST_LEN; i++)
  {
    if (ghr[i - 1])
    {
      y += table[index][i];
    }
    else
    {
      y -= table[index][i];
    }
  }

  return y >= 0;
}

void PREDICTOR::UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget)
{
  UINT32 index = Hash(PC);

  if (resolveDir != predDir || abs(y) <= THRESHOLD)
  {
    int t = resolveDir ? 1 : -1;
    int x = 1;

    table[index][0] += t * x;

    for (int i = 1; i < HIST_LEN; i++)
    {
      x = ghr[i - 1] ? 1 : -1;
      table[index][i] += t * x;
    }
  }

  ghr = ghr << 1;
  ghr.set(0, resolveDir);
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
