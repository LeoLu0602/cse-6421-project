#include "predictor.h"
#include <cstdlib> // For abs()
#include <cmath>

#define HIST_LEN 62
#define TABLE_LEN 1024

PREDICTOR::PREDICTOR(void)
{
  ghr = bitset<HIST_LEN>();

  // Each row in the table contains HIST_LEN + 1 perceptrons
  // w0...n, n = HIST_LEN
  for (int i = 0; i < TABLE_LEN; i++)
  {
    for (int j = 0; j <= HIST_LEN; j++)
    {
      table[i][j] = 0;
    }
  }

  y = 0;
}

bool PREDICTOR::GetPrediction(UINT32 PC)
{
  UINT32 index = Hash(PC);

  y = 0; // reset y

  for (int i = 0; i <= HIST_LEN; i++)
  {
    int8_t x = (i == 0 || ghr[i - 1]) ? 1 : -1; // x0 is always set to 1, providing a "bias" input

    y += x * table[index][i];
  }

  return y >= 0;
}

void PREDICTOR::UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget)
{
  UINT32 index = Hash(PC);

  if (resolveDir != predDir || abs(y) <= floor(1.93 * HIST_LEN + 14))
  {
    int8_t t = resolveDir ? 1 : -1;

    for (int i = 0; i <= HIST_LEN; i++)
    {
      int8_t x = (i == 0 || ghr[i - 1]) ? 1 : -1; // x0 is always set to 1, providing a "bias" input
      int new_w = table[index][i] + t * x;

      // to prevent overflow (range: [-128, 127])
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
  return PC % TABLE_LEN;
}
