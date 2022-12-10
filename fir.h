/*
 * fir.h
 *
 *  Created on: Dec 10, 2022
 *      Author: lakij
 */

#ifndef FIR_H_
#define FIR_H_

Int16 fir_basic(Int16 input, Int16* coeffs, Int16 *history, Uint16 n_coeff);
Int16 fir_circular(Int16 input, Int16 *coeffs, Int16 *history, Uint16 n_coeff, Uint16 *p_state);

#endif /* FIR_H_ */
