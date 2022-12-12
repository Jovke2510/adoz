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

Int16 IIR_notch_2kHz_4th_order[2][6] = { { 6282,  -4240,  6281,
														   32767, -26001, 28298},
														 { 4415,  -131,   4379,
														   32767, -23752, 18722}};

Int16 IIR_notch_2kHz_6th_order[3][6] = { { 1135,  635,    1004,
														   32767, -23337, 17315 },
		                                                 { 15188, -10526, 15185,
		                                                   32767, -26383, 29713 },
														 { 7405,  -3857,  7319,
														   32767, -24596, 23177 } };

#endif /* IIR_NOTCH_FILTERS_H_ */
