#ifndef _PREDICTOR_H_
#define _PREDICTOR_H_

#include "utils.h"
#include "tracer.h"

#define UINT16 unsigned short int

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

class PREDICTOR
{
private:
public:
  // The interface to the four functions below CAN NOT be changed

  PREDICTOR(void);
  bool GetPrediction(UINT32 PC);
  void UpdatePredictor(UINT32 PC, bool resolveDir, bool predDir, UINT32 branchTarget);
  void TrackOtherInst(UINT32 PC, OpType opType, UINT32 branchTarget);

  // Contestants can define their own functions below
};

/***********************************************************/
#endif
