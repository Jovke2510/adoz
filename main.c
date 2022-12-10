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
#include "FIR_high_pass_35th_order_filter.h"

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#define SAMPLE_RATE 48000L
#define GAIN 0

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
Int16 HistoryBufferL[35];
Int16 HistoryBufferR[35];
Uint16 index;
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
    	for(k = 0; k< 121; k++){
    		HistoryBufferL[i] = 0;
    		HistoryBufferR[i] = 0;
    	}
    index = 0;

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
			OutputBufferL[j] = fir_basic(InputBufferL[j], highpass_3kHz_35th_order, HistoryBufferL, 35);
			OutputBufferR[j] = fir_basic(InputBufferR[j], highpass_3kHz_35th_order, HistoryBufferR, 35);
		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

