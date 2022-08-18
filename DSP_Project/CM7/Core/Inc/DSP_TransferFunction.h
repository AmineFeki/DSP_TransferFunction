/*
 * DSP_TransferFunction.h
 *
 *  Created on: Aug 17, 2022
 *      Author: LENOVO
 */

#ifndef INC_DSP_TRANSFERFUNCTION_H_
#define INC_DSP_TRANSFERFUNCTION_H_

#include <string.h>
#include <stdlib.h>
#include "DSP_Types.h"
#include "DSP_Polynom.h"

DSP_Return_ten DSP_CreateTransferFunction(char* Numerator,char* denominator, DSP_TF_tst* Tf);
DSP_Return_ten DSP_C2D(DSP_TF_tst ContTF, DSP_TF_tst* DiscTF, DSP_ZAlgorithm_ten Algo);
void DSP_vGenerateSignal(DSP_TF_tst* tf);
float DSP_fRecurringEquationRoutine(DSP_TF_tst* tf);

#endif /* INC_DSP_TRANSFERFUNCTION_H_ */
