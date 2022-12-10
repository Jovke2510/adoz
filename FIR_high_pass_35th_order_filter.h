/*
 * FIR_high_pass_35th_order_filter.h
 *
 *  Created on: Dec 10, 2022
 *      Author: lakij
 */

#ifndef FIR_HIGH_PASS_35TH_ORDER_FILTER_H_
#define FIR_HIGH_PASS_35TH_ORDER_FILTER_H_

#include "tistdtypes.h"

#define HP_LENGTH 35

Int16 highpass_3kHz_35th_order[35] = {
				-231,
		            0,
		          262,
		          520,
		          732,
		          858,
		          865,
		          729,
		          438,
		            0,
		         -564,
		        -1216,
		        -1906,
		        -2580,
		        -3178,
		        -3649,
		        -3950,
		        28378,
		        -3950,
		        -3649,
		        -3178,
		        -2580,
		        -1906,
		        -1216,
		         -564,
		            0,
		          438,
		          729,
		          865,
		          858,
		          732,
		          520,
		          262,
		            0,
		         -231
};

#endif /* FIR_HIGH_PASS_35TH_ORDER_FILTER_H_ */
