/*
 * DSP_Polynom.c
 *
 *  Created on: Aug 17, 2022
 *      Author: LENOVO
 */

#ifndef SRC_DSP_POLYNOM_C_
#define SRC_DSP_POLYNOM_C_

#include "DSP_Polynom.h"


DSP_Return_ten DSP_PolynomInit(DSP_Polynom_tst* Polynom_st)
{
	Polynom_st->degree = 0;
	for (int8_t i = 0 ; i < 10 ; i++)
	{
		Polynom_st->coef[i] = 0.0;
	}
	return DSP_Ok_en;
}

DSP_Return_ten DSP_PolynomCreate(char* PolynomChar , DSP_Polynom_tst* Polynom_st)
{
	DSP_Return_ten Return = DSP_Ok_en;
	char CoefChar[10];

	uint8_t index = 0;
	uint8_t PolynomCharLength = 0;

	uint8_t NextCoefIndex = 1;

	uint8_t CoefNumber = 0;

	uint8_t LastCoefGot = 0;

	for (int8_t i = 0 ; i<10 ; i++)
	{
		CoefChar[i] = '\0';
	}

	PolynomCharLength = strlen(PolynomChar);
	if ((PolynomChar[0] == '[') && (PolynomChar[PolynomCharLength-1] == ']'))
	{
		index = 2;
		for (int8_t i = index ; i < PolynomCharLength ; i++)
		{
			if ((PolynomChar[i] == '0')
					|| (PolynomChar[i] == '1')
					|| (PolynomChar[i] == '2')
					|| (PolynomChar[i] == '3')
					|| (PolynomChar[i] == '4')
					|| (PolynomChar[i] == '5')
					|| (PolynomChar[i] == '6')
					|| (PolynomChar[i] == '7')
					|| (PolynomChar[i] == '8')
					|| (PolynomChar[i] == '9')
					|| (PolynomChar[i] == '.')
					|| (PolynomChar[i] == ']')
					|| (PolynomChar[i] == ' ')
					|| (PolynomChar[i] == '-')
					)
			{
				if (PolynomChar[i] == ' ')
				{
					strncpy(CoefChar,&(PolynomChar[NextCoefIndex]), i - NextCoefIndex);
					//strcat(CoefChar,(const char*)(ZeroChar) );
					CoefNumber ++;
					Polynom_st->coef[CoefNumber-1] = atof(CoefChar);

					if (i+1 == PolynomCharLength - 1)
					{
						LastCoefGot = 1;
					}
					else
					{
						NextCoefIndex = i + 1;
					}
				}
				else if ((PolynomChar[i] == ']'))
				{
					if (LastCoefGot == 0)
					{
						strncpy(CoefChar,&(PolynomChar[NextCoefIndex]), i - NextCoefIndex);
						//strcat(CoefChar,(const char*)(ZeroChar) );
						CoefNumber ++;
						Polynom_st->coef[CoefNumber-1] = atof(CoefChar);

						NextCoefIndex = 0xff;
					}
					else
					{
						/*
						 * Last coef already got
						 * nothing to do
						 * */
					}
				}
				else
				{
					/* do nothing */
				}
			}
			else
			{
				/* wrong input */
				Return = DSP_Error_en;
			}
		}
	}
	else
	{
		/* Polynom not valid */
		Return = DSP_Error_en;
	}
	Polynom_st->degree = CoefNumber - 1;

	return Return;
}

DSP_Return_ten DSP_SumPolynom(DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst Polynom2_st , DSP_Polynom_tst* PolynomSum_st)
{
	DSP_Return_ten Return = DSP_Ok_en;

	if (Polynom1_st.degree == Polynom2_st.degree)
	{
		PolynomSum_st->degree = Polynom1_st.degree;
	}
	else if (Polynom1_st.degree > Polynom2_st.degree)
	{
		PolynomSum_st->degree = Polynom1_st.degree;
	}
	else
	{
		PolynomSum_st->degree = Polynom2_st.degree;
	}

	for (int8_t i = 0; i < PolynomSum_st->degree + 1 ; i++)
	{
		PolynomSum_st->coef[i] = Polynom1_st.coef[i] + Polynom2_st.coef[i];
	}

	while (PolynomSum_st->coef[PolynomSum_st->degree] == 0.0)
	{
		PolynomSum_st->degree = PolynomSum_st->degree - 1 ;
	}

	return Return;
}

DSP_Return_ten DSP_MulPolynom(DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst Polynom2_st, DSP_Polynom_tst* PolynomMul_st)
{
	DSP_Return_ten Return = DSP_Ok_en;

//	float PolynomProduct[10][10];

	PolynomMul_st->degree = Polynom1_st.degree + Polynom2_st.degree;

	for (int8_t i = 0 ; i < Polynom1_st.degree +1 ; i++)
	{
		// select the line
		for (int8_t j = 0 ; j <Polynom2_st.degree+1 ; j++)
		{
			// select the row
//			PolynomProduct[i][j] = Polynom1_st.coef[i] * Polynom2_st.coef[j];
			PolynomMul_st->coef[i+j] = PolynomMul_st->coef[i+j] + (Polynom1_st.coef[i] * Polynom2_st.coef[j]);
		}
	}

	return Return;
}

DSP_Return_ten DSP_MulScalarPolynom(float Scalar, DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst* PolynomMul_st)
{
	PolynomMul_st->degree = Polynom1_st.degree;
	for (int8_t i = 0; i < Polynom1_st.degree + 1 ; i++)
	{
		PolynomMul_st->coef[i] = Scalar * Polynom1_st.coef[i];
	}
	return DSP_Ok_en;
}

DSP_Return_ten DSP_DevideScalarPolynom(float Scalar, DSP_Polynom_tst Polynom1_st, DSP_Polynom_tst* PolynomMul_st)
{
	PolynomMul_st->degree = Polynom1_st.degree;
	for (int8_t i = 0; i < Polynom1_st.degree + 1 ; i++)
	{
		PolynomMul_st->coef[i] = (float)( Polynom1_st.coef[i] / Scalar);
	}
	return DSP_Ok_en;
}

DSP_Return_ten DSP_PowPolynom(DSP_Polynom_tst Polynom_st, uint8_t pow , DSP_Polynom_tst* PolynomResult_st)
{
	DSP_Return_ten Return = DSP_Ok_en;

	DSP_Polynom_tst PolynomZero;

	if (pow != 0)
	{

		PolynomResult_st->degree = 0;
		PolynomResult_st->coef[0] = 1.0;

		for (int8_t i = 0; i < pow ; i++)
		{
			DSP_PolynomInit(&PolynomZero);
			DSP_MulPolynom(*PolynomResult_st, Polynom_st, &PolynomZero);
			DSP_CpyPolynom(PolynomResult_st, PolynomZero);
		}
	}
	else
	{
		PolynomResult_st->degree = 0;
		PolynomResult_st->coef[0] = 1.0;
	}

	return Return;
}

DSP_Return_ten DSP_CpyPolynom(DSP_Polynom_tst* Polynom1_st , DSP_Polynom_tst Polynom2_st)
{
	Polynom1_st->degree = Polynom2_st.degree;
	for (int8_t i = 0; i < Polynom2_st.degree + 1 ; i++)
	{
		Polynom1_st->coef[i] = Polynom2_st.coef[i];
	}
	return DSP_Ok_en;
}





#endif /* SRC_DSP_POLYNOM_C_ */
