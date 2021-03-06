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
#define VERBOSE 1


//------------------------------------------------------------------
// print_data()
//
// Prints a given array of bytes to std out i nice columns.
//------------------------------------------------------------------
void print_data(uint32_t num_bytes, uint8_t *data)
{  
  uint32_t i;
  uint8_t columns;
  uint8_t maxcolumns = 15;
  
  columns = 0;
  for (i = 0 ; i < num_bytes ; i++)
    {
      if ((i > 0) && (columns == maxcolumns))
        {
          printf("0x%02x\n", data[i]);
          columns = 0;
        }
      else
        {
          printf("0x%02x  ", data[i]);
          columns++;
        }
    }
  printf("\n");
}


//------------------------------------------------------------------
// run_yarrow()
//
// Init Yarrow with the given seed and extract num bytes of
// random data.
//
// Note: Assumes that random_data points to an allocated array
// with at least num_bytes of space.
//------------------------------------------------------------------
int run_yarrow(uint32_t seed_size, uint8_t *seed_data, uint32_t num_bytes, uint8_t *random_data)
{
  uint32_t i;
  uint8_t rngdata;
  
  struct yarrow256_ctx yarrow;
  yarrow256_init(&yarrow, 0, NULL);
  yarrow256_seed (&yarrow, 1024, &seed_data[0]);

  for (i = 0 ; i < num_bytes ; i++)
    {
      yarrow256_random (&yarrow, 1, &rngdata);
      random_data[i] = rngdata;
    }

  // All went well.
  return 0;
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

  seed_data = (uint8_t *)calloc(num_seed_bytes, sizeof(uint8_t));
  if (NULL == seed_data)
    {
      fprintf(stderr, "Failed to allocate memory.\n");
      exit(EXIT_FAILURE);
    }

  randomfp = fopen("/dev/random", "r");
  if (NULL == randomfp)
    {
      fprintf(stderr, "Failed to open random number device.\n");
      exit(EXIT_FAILURE);
    }

  for (i = 0 ; i < num_seed_bytes ; i++)
    {
      tmp = fgetc(randomfp);
      seed_data[i] = (uint8_t)tmp;
    }

  if (VERBOSE)
    {
      printf("Seed data extracted from the system:\n");
      printf("------------------------------------\n");
      print_data(num_seed_bytes, &seed_data[0]);
      printf("\n");
    }

  return &seed_data[0];
}


//------------------------------------------------------------------
// test_yarrow()
//
// Grabs entropy from the system, feeds it to yarrow and
// extracts random data which is then displayed.
//------------------------------------------------------------------
void test_yarrow()
{  
  uint32_t max_seed_bytes = 16384;
  uint32_t max_rng_bytes = 2048;
  uint8_t *seed_data;
  uint8_t *rng_data;
  
  seed_data = get_seed_data(max_seed_bytes);

  rng_data = (uint8_t *)calloc(max_rng_bytes, sizeof(uint8_t));
  if (NULL == rng_data)
    {
      fprintf(stderr, "Failed to allocate memory.\n");
      exit(EXIT_FAILURE);
    }

  run_yarrow(max_seed_bytes, &seed_data[0], max_rng_bytes, &rng_data[0]);

  printf("Random data generated by Yarrow:\n");
  printf("--------------------------------\n");
  print_data(max_rng_bytes, &rng_data[0]);
  printf("\n");

  free(seed_data);
  seed_data = NULL;
  free(rng_data);
  rng_data = NULL;
}


//------------------------------------------------------------------
// main()
//
// Gets some seed value and feeds the yarrow test function.
//------------------------------------------------------------------

int main(void)
{
  printf("Test of the Yarrow RNG in Nettle:\n");
  printf("=================================\n");
  
  test_yarrow();

  return 0;
}

//======================================================================
// EOF yarrowtest.c
//======================================================================
