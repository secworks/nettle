//======================================================================
//
// keygen.h
// --------
// Header file for the key generator module.
// Declares both a function to get the key data as well as a
// function to test the yarrow based generator.
//
//
// Author: Joachim Strombergson
// (c) 2014, Secworks Sweden AB
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or 
// without modification, are permitted provided that the following 
// conditions are met: 
// 
// 1. Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer. 
// 
// 2. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the 
//    distribution. 
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//======================================================================

#ifndef _KEYGEN_H_
#define _KEYGEN_H_

//------------------------------------------------------------------
// Includes.
//------------------------------------------------------------------
#include <stdint.h>


//------------------------------------------------------------------
// test_yarrow()
//
// Uses the Yarrow based generator to generate a block of random
// data. The seed as well as the generated data is printed to
// std out.
//------------------------------------------------------------------
void test_yarrow();


//------------------------------------------------------------------
// gen_key_bytes()
//
// Generates num_bytes key data bytes. The bytes is stored
// pointed to by the given pointer.
//------------------------------------------------------------------
void gen_key_bytes(uint32_t num_bytes, uint8_t *key_data);


#endif // _KEYGEN_H_

//======================================================================
// EOF keygen.h
//======================================================================
