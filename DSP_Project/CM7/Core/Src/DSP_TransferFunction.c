/*
 * DSP_TransferFunction.c
 *
 *  Created on: Aug 17, 2022
 *      Author: LENOVO
 */

#include "DSP_TransferFunction.h"

DSP_Return_ten DSP_CreateTransferFunction(char* Numerator,char* denominator, DSP_TF_tst* Tf)
{
	DSP_Return_ten Return;

	Return = DSP_PolynomCreate(Numerator, &Tf->num);
	Return = DSP_PolynomCreate(denominator, &Tf->denom);

	return Return;
}

DSP_Return_ten DSP_C2D(DSP_TF_tst ContTF, DSP_TF_tst* DiscTF, DSP_ZAlgorithm_ten Algo)
{
	DSP_Return_ten Return = DSP_Ok_en;

	DSP_Polynom_tst TustinNum;
	DSP_Polynom_tst TustinDenom;

	TustinNum.degree = 1;
	TustinNum.coef[0] = 2 / Ts;
	TustinNum.coef[1] = -2/Ts;

	TustinDenom.degree = 1;
	TustinDenom.coef[0] = 1;
	TustinDenom.coef[1] = 1;

	DSP_Polynom_tst InterPolynom1;
	DSP_Polynom_tst InterPolynom2;
	DSP_Polynom_tst InterPolynom3;
	DSP_Polynom_tst InterPolynom4;

	DSP_Polynom_tst InterPolynom5;
	DSP_Polynom_tst InterPolynom6;




	switch (Algo)
	{
	case DSP_Tustin:
	{
		/* Numerator */
		DiscTF->num.degree = ContTF.num.degree;

		for (int8_t i = 0 ; i < ContTF.num.degree + 1 ; i++)
		{
			DSP_PolynomInit(&InterPolynom1);
			DSP_PolynomInit(&InterPolynom2);
			DSP_PolynomInit(&InterPolynom3);
			DSP_PolynomInit(&InterPolynom4);
			DSP_PowPolynom(TustinNum, ContTF.num.degree - i, &InterPolynom1);
			DSP_PowPolynom(TustinDenom, i, &InterPolynom2);
			DSP_MulPolynom(InterPolynom1, InterPolynom2, &InterPolynom3);
			DSP_MulScalarPolynom(ContTF.num.coef[ContTF.num.degree - i], InterPolynom3, &InterPolynom4);
			DSP_SumPolynom(InterPolynom4, DiscTF->num , &DiscTF->num);
		}

		/* Denominator */
		for (int8_t i = 0 ; i < ContTF.denom.degree + 1 ; i++)
		{
			DSP_PolynomInit(&InterPolynom1);
			DSP_PolynomInit(&InterPolynom2);
			DSP_PolynomInit(&InterPolynom3);
			DSP_PolynomInit(&InterPolynom4);
			DSP_PowPolynom(TustinNum, ContTF.denom.degree - i, &InterPolynom1);
			DSP_PowPolynom(TustinDenom, i, &InterPolynom2);
			DSP_MulPolynom(InterPolynom1, InterPolynom2, &InterPolynom3);
			DSP_MulScalarPolynom(ContTF.denom.coef[ContTF.denom.degree - i], InterPolynom3, &InterPolynom4);
			DSP_SumPolynom(InterPolynom4, DiscTF->denom , &DiscTF->denom);
		}

		DSP_PolynomInit(&InterPolynom5);
		DSP_PolynomInit(&InterPolynom6);


		if (ContTF.num.degree > ContTF.denom.degree)
		{
			DSP_PowPolynom(TustinDenom, ContTF.num.degree-ContTF.denom.degree, &InterPolynom5);
			DSP_MulPolynom(DiscTF->denom, InterPolynom5, &InterPolynom6);
			DSP_CpyPolynom(&DiscTF->denom, InterPolynom6);
		}
		else if (ContTF.num.degree < ContTF.denom.degree)
		{
			DSP_PowPolynom(TustinDenom, ContTF.denom.degree-ContTF.num.degree, &InterPolynom5);
			DSP_MulPolynom(DiscTF->num, InterPolynom5, &InterPolynom6);
			DSP_CpyPolynom(&DiscTF->num, InterPolynom6);
		}
		else
		{
			/* do nothing */
		}

		/* normalize the denominator */
		DSP_DevideScalarPolynom(DiscTF->denom.coef[0], DiscTF->num, &DiscTF->num);
		DSP_DevideScalarPolynom(DiscTF->denom.coef[0], DiscTF->denom, &DiscTF->denom);

	}break;
	case DSP_ZoH:
	{
		/* Under construction */
	}break;
	default:
	{

	}
	}
	return Return;

}



void DSP_vGenerateSignal(DSP_TF_tst* tf)
{
	if (tf->num.degree > tf->denom.degree)
	{
		tf->k = tf->num.degree;
	}
	else if (tf->num.degree < tf->denom.degree)
	{
		tf->k = tf->denom.degree;
	}
	else
	{
		tf->k = tf->denom.degree;
	}

	tf->U[tf->k] = 10;
	//HAL_TIM_Base_Start_IT(&htim6);
}

float DSP_fRecurringEquationRoutine(DSP_TF_tst* tf)
{
	float output = 0.0;

	tf->Y[tf->k] = tf->num.coef[0] * tf->U[tf->k];
	for (uint8_t i = 1; i < tf->k + 1  ; i++)
	{
		tf->Y[tf->k] += tf->num.coef[i] * tf->U[tf->k-i] - tf->denom.coef[i] * tf->Y[tf->k-i] ;
	}

	output = tf->Y[tf->k];

	for (int8_t j = tf->k-1 ; j >= 0 ; j--)
	{
		tf->Y[tf->k-j-1] = tf->Y[tf->k-j];
		tf->U[tf->k-1-j] = tf->U[tf->k-j];
	}

	return output;
}

