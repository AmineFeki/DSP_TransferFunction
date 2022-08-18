/*
 * DSP_Polynom.h
 *
 *  Created on: Aug 17, 2022
 *      Author: LENOVO
 */

#ifndef INC_DSP_POLYNOM_H_
#define INC_DSP_POLYNOM_H_

#include <string.h>
#include <stdlib.h>
#include "DSP_Types.h"

DSP_Return_ten DSP_PolynomInit(DSP_Polynom_tst* Polynom_st);

DSP_Return_ten DSP_PolynomCreate(char* PolynomChar , DSP_Polynom_tst* Polynom_st);
DSP_Return_ten DSP_SumPolynom(DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst Polynom2_st, DSP_Polynom_tst* PolynomSum_st);
DSP_Return_ten DSP_MulPolynom(DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst Polynom2_st, DSP_Polynom_tst* PolynomMul_st);
DSP_Return_ten DSP_MulScalarPolynom(float Scalar, DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst* PolynomMul_st);
DSP_Return_ten DSP_DevideScalarPolynom(float Scalar, DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst* PolynomMul_st);
DSP_Return_ten DSP_PowPolynom(DSP_Polynom_tst Polynom_st, uint8_t pow , DSP_Polynom_tst* PolynomMul_st);
DSP_Return_ten DSP_CpyPolynom(DSP_Polynom_tst* Polynom1_st , DSP_Polynom_tst Polynom2_st);


#endif /* INC_DSP_POLYNOM_H_ */
