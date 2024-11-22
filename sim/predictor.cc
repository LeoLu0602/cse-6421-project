#include "predictor.h"
#include <cstdlib> // For abs()
#include <cmath>

PREDICTOR::PREDICTOR(void)
{
  ghr = bitset<62>();

  for (int i = 0; i < 2080; i++)
  {
    for (int j = 0; j <= 62; j++)
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

  for (int i = 1; i <= 62; i++)
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

  if (resolveDir != predDir || abs(y) <= floor(1.93 * 62 + 14))
  {
    int t = resolveDir ? 1 : -1;
    int x = 1; // x0 is always set to 1, providing a "bias" input
    int8_t new_w = 0;

    for (int i = 0; i <= 62; i++)
    {
      if (i > 0)
      {
        x = ghr[i - 1] ? 1 : -1;
      }

      // to prevent overflow (range: [-128, 127])
      new_w = table[index][i] + t * x;
      new_w = (new_w > 127) ? 127 : (new_w < -128) ? -128
                                                   : new_w;

      table[index][i] = new_w;
    }
  }

  ghr = (ghr << 1);
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
  return PC % 2080;
}
