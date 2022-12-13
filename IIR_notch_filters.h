/*
 * IIR_notch_filters.h
 *
 *  Created on: Dec 10, 2022
 *      Author: lakij
 */

#ifndef IIR_NOTCH_FILTERS_H_
#define IIR_NOTCH_FILTERS_H_

Int16 IIR_notch_2kHz_2nd_order[6] = { 32767,  -31651,  32767,
													 32767, -30701, 30830};

Int16 IIR_notch_2kHz_4th_order[2][6] = { { 32767,  -31651,  32767,
														   32767, -30701, 30830},
										 { 32767,  -31651,   32767,
														   32767, -30701, 30830}};

Int16 IIR_notch_2kHz_6th_order[3][6] = { { 32767,  -31651,  32767,
		   	   	   	   	   	   	   	   	   	   	   	   	   32767, -30701, 30830},
										 { 32767,  -31651,   32767,
												 	 	   32767, -30701, 30830},
										 { 32767,  -31651,  32767,
														   32767, -30701, 30830}};

#endif /* IIR_NOTCH_FILTERS_H_ */
