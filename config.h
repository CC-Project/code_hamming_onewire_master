#ifndef CONFIG_HAMMING_AVR_M_H
    #define CONFIG_HAMMING_AVR_M_H
    #pragma once

	// The following preprocessor code selects the architecture
	#ifdef __AVR__
        #ifndef AVR_WARNING
            #define AVR_WARNING
            #warning AVR plateform selected
        #endif // AVR_WARNING
        #define BAUD_RATE 0x19      //38400
		#define F_CPU	16000000UL  //CPU clock frequency
		#include <avr/io.h>
		#define EXIT_FAILURE -1
		#define EXIT_SUCCESS 1

        #include <inttypes.h>
        #include <stdio.h>
        #include <stdlib.h>
	#endif
	// Project configuration
    #ifndef DEBUG
        #define DEBUG
    #endif // DEBUG
#endif // CONFIG_H
