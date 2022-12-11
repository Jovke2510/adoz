//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// *
// * Description: Lab exercise 8
// * Course: ADOZ
// * Year: 2022
// *
// * Author: <TO DO - add student name and index>
// * Faculty of Technical Sciences, Novi Sad
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "WAVheader.h"
#include "iir.h"
#include "fir.h"
#include "FIR_highpass_filters.h"
#include "IIR_notch_filters.h"

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#define SAMPLE_RATE 48000L
#define GAIN 0
#define FIR_ORDER 77

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

/* TO DO: Define history buffers and Rd/Wr pointers*/
/* Your code here */
Int16 HistoryBufferL[FIR_ORDER];
Int16 HistoryBufferR[FIR_ORDER];
Int16 HistoryBufferX[2];
Int16 HistoryBufferY[2];
Int16 OutputBufferL_pom[AUDIO_IO_SIZE];
Int16 OutputBufferR_pom[AUDIO_IO_SIZE];
Int16 Dirak[AUDIO_IO_SIZE];
/*
 *
 *  main( )
 *
 */
void main( void )
{
	int i;
	Int32 j;
	Int32 number_of_blocks;

	/* Initialize BSL */
    EZDSP5535_init( );

	printf("\n ADOZ - Vezba 8 \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

	aic3204_set_input_filename("../16.wav");
	aic3204_set_output_filename("../out_signal1.wav");

    /* Initialise the AIC3204 codec */
	aic3204_init();

    aic3204_dma_init();

	aic3204_read_wav_header(&inputWAVhdr);

    // Set up output WAV header
    outputWAVhdr = inputWAVhdr;

    number_of_blocks = inputWAVhdr.data.SubChunk2Size/
    			(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

    aic3204_write_wav_header(&outputWAVhdr);

    /* TO DO: Initialize history buffers to 0 */
    /* Your code here */
    int k;
    	for(k = 0; k < FIR_ORDER; k++){
    		HistoryBufferL[i] = 0;
    		HistoryBufferR[i] = 0;
    		if(k<2){
    			HistoryBufferX[i] = 0;
    	 		HistoryBufferY[i] = 0;
    		}
    	}

    Dirak[0] = 32767;
    for(i = 1; i<AUDIO_IO_SIZE; i++){
    	Dirak[i] = 0;
    }

	for(i=0;i<number_of_blocks;i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/* TO DO: Invoke filtering routine */
		/* Your code here */

		for(j = 0; j < AUDIO_IO_SIZE; j++)
		{
			OutputBufferL_pom[j] = fir_basic(InputBufferL[j], highpass_3kHz_77th_order, HistoryBufferL, FIR_ORDER);
			OutputBufferR_pom[j] = fir_basic(InputBufferR[j], highpass_3kHz_77th_order, HistoryBufferR, FIR_ORDER);
			OutputBufferL[j] = second_order_IIR(OutputBufferL_pom[j], IIR_notch_pass_2kHz_2nd_order, HistoryBufferX, HistoryBufferY);
			OutputBufferR[j] = second_order_IIR(OutputBufferR_pom[j], IIR_notch_pass_2kHz_2nd_order, HistoryBufferX, HistoryBufferY);
		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

