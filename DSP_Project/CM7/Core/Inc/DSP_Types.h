/*
 * DSP_Types.h
 *
 *  Created on: Aug 17, 2022
 *      Author: LENOVO
 */

#ifndef INC_DSP_TYPES_H_
#define INC_DSP_TYPES_H_

#include "DSP_Cfg.h"
#include "stdint.h"

typedef struct
{
	uint8_t degree;
	double coef[DSP_MAX_POLYNOM_DEGREE+1];
}DSP_Polynom_tst;

typedef struct
{
	DSP_Polynom_tst num;
	DSP_Polynom_tst denom;
	uint8_t k;
	double Y[DSP_MAX_POLYNOM_DEGREE];
	double U[DSP_MAX_POLYNOM_DEGREE];
}DSP_TF_tst;

typedef enum
{
	DSP_Tustin,
	DSP_ZoH
}DSP_ZAlgorithm_ten;

typedef enum
{
	DSP_Ok_en,
	DSP_Error_en
}DSP_Return_ten;

#endif /* INC_DSP_TYPES_H_ */
