//======================================================================
//
// yarrowtest.c
// ----------
// Program that tests the functionality of the Yarrow algorithm an
// random number generation in Nettle.
// function and perform benchmarking.
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

//------------------------------------------------------------------
// Includes.
//------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "yarrow.h"


//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------
#define MAX_SEED_BYTES 16384
#define VERBOSE 1


//------------------------------------------------------------------
// test_yarrow()
//
// Perform a simple test of the yarrow PRNG in nettle.
//------------------------------------------------------------------
void test_yarrow(uint32_t seed_size, uint8_t *seed_data)
{
  uint32_t i;
  uint8_t rngdata;
  
  struct yarrow256_ctx yarrow;
  yarrow256_init(&yarrow, 0, NULL);
  yarrow256_seed (&yarrow, 1024, &seed_data[0]);

  for (i = 0 ; i < 1024 ; i++)
    {
      yarrow256_random (&yarrow, 1, &rngdata);
      printf("random number 0x%02x = 0x%02x\n", i, rngdata);
    }
}


//------------------------------------------------------------------
// get_seed_data()
//
// Returns a pointer to an array with num_seed_bytes. The
// random numbers are extracted from /dev/random.
//
// Note: We don't check that we do get the specified number
// of values from the device.
//
// Note: It is the callers responsibility to ensure that
// the specified value in num_seed_bytes is less than
// MAX_SEED_BYTES.
//------------------------------------------------------------------
uint8_t* get_seed_data(uint32_t num_seed_bytes)
{
  FILE *randomfp;
  uint32_t i;
  uint32_t tmp;

  uint8_t *seed_data;
  seed_data = malloc(num_seed_bytes);

  randomfp = fopen("/dev/random", "r");
  for (i = 0 ; i < num_seed_bytes ; i++)
    {
      tmp = fgetc(randomfp);
      seed_data[i] = (uint8_t)tmp;
    }

  if (VERBOSE)
    {
      printf("Seed data extracted:\n");
      for (i = 0 ; i < num_seed_bytes ; i++)
        {
          printf("seed 0x%04x = 0x%02x\n", i, seed_data[i]);
        }
    }

  return &seed_data[0];
}


//------------------------------------------------------------------
// main()
//
// Gets some seed value and feeds the yarrow test function.
//------------------------------------------------------------------

int main(void)
{
  uint8_t *seedptr;

  seedptr = get_seed_data(MAX_SEED_BYTES);
  test_yarrow(MAX_SEED_BYTES, seedptr);

  return 0;
}


//======================================================================
// EOF yarrowtest.c
//======================================================================
