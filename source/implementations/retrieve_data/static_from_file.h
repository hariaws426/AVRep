#pragma once

#include <string.h>
#include "../debug_print/debug_print.h"


// Static retrieval of data from file.
// Static in this context means that the data is statically compiled into the executable and therefore fixed after compilation time.
// Data must be copied as c-style array buf[] into get_shellcode.h by the build script.
//
// arg1 specifies which array the data is read from.
// data_size receives the size of the data in bytes.
unsigned char *static_from_file(char *arg1, int *data_size) {
    // Deliver address and size of array buf[]
    // If shellcode is retrieved statically, the define is set by the build script to notify this function that array buf[] is declared and known to the compiler.
    #ifdef STATIC_SHELLCODE
    if(strcmp(arg1, "static_shellcode") == 0) {
        DEBUG_PRINT("Statically retrieving data from array buf[] in included file...\n");
        *data_size = sizeof(buf) - 1;	
        return buf;
    }
    #endif
    // Deliver address and size of array key[] if key is requested
    // If the key is retrieved statically, the define is set by the build script to notify this function that array key[] is declared and known to the compiler.
    #ifdef STATIC_KEY     
    if(strcmp(arg1, "static_key") == 0) {
        DEBUG_PRINT("Statically retrieving data from array key[] in included file...\n");
        *data_size = sizeof(key) - 1;	
        return key;
    }
    #endif

    // Return NULL if arg1 is unrecognized string or defines are not set correctly
    DEBUG_PRINT("Static retrieval from file failed; argument arg1 of function static_from_file not recognized and/or defines not correctly set in included headers?\n");
    return NULL;
}
