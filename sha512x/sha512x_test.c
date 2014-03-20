//======================================================================
//
// sha512x_test.c
// --------------
// Program that tests the SHA-512/224 and SHA-512/256 functionality
// as specified in NIST FIPS 180-4 for Nettle.
//
// Test cases taken from:
// http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA_All.pdf
//
//
// Author: Joachim Strombergson
// Copyright (c) 2014 Secworks Sweden AB
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
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "sha2.h"


//------------------------------------------------------------------
// print_digest()
//------------------------------------------------------------------
void print_digest(uint8_t length, uint8_t *digest)
{
  uint32_t i;
  
  printf("Digest for message:\n");
  for (i = 0 ; i < length ; i++)
    {                                           \
      printf("%02x ", digest[i]);
      if (15 == i%16)
        {
          printf("\n");
        }
    }
}


//------------------------------------------------------------------
// main()
//------------------------------------------------------------------
int main(void)
{
  uint8_t my_msg[] = "abc";
  uint8_t my_digest[64];
  struct sha512_ctx my_sha512_ctx;

  uint8_t sha512_224_expected[28] = {0x46, 0x34, 0x27, 0x0F, 0x70, 0x7B, 0x6A, 0x54,
                                     0xDA, 0xAE, 0x75, 0x30, 0x46, 0x08, 0x42, 0xE2,
                                     0x0E, 0x37, 0xED, 0x26, 0x5C, 0xEE, 0xE9, 0xA4,
                                     0x3E, 0x89, 0x24, 0xAA};

  uint8_t sha512_256_expected[32] = {0x53, 0x04, 0x8E, 0x26, 0x81, 0x94, 0x1E, 0xF9,
                                     0x9B, 0x2E, 0x29, 0xB7, 0x6B, 0x4C, 0x7D, 0xAB,
                                     0xE4, 0xC2, 0xD0, 0xC6, 0x34, 0xFC, 0x6D, 0x46,
                                     0xE0, 0xE2, 0xF1, 0x31, 0x07, 0xE7, 0xAF, 0x23};

  uint8_t sha512_expected[64] = {0xDD, 0xAF, 0x35, 0xA1, 0x93, 0x61, 0x7A, 0xBA,
                                 0xCC, 0x41, 0x73, 0x49, 0xAE, 0x20, 0x41, 0x31,
                                 0x12, 0xE6, 0xFA, 0x4E, 0x89, 0xA9, 0x7E, 0xA2, 
                                 0x0A, 0x9E, 0xEE, 0xE6, 0x4B, 0x55, 0xD3, 0x9A, 
                                 0x21, 0x92, 0x99, 0x2A, 0x27, 0x4F, 0xC1, 0xA8, 
                                 0x36, 0xBA, 0x3C, 0x23, 0xA3, 0xFE, 0xEB, 0xBD, 
                                 0x45, 0x4D, 0x44, 0x23, 0x64, 0x3C, 0xE8, 0x0E, 
                                 0x2A, 0x9A, 0xC9, 0x4F, 0xA5, 0x4C, 0xA4, 0x9F};
  
  
  printf("Test of single block message of SHA-512.\n");
  sha512_init(&my_sha512_ctx);
  sha512_update(&my_sha512_ctx, 3, &my_msg[0]);
  sha512_digest(&my_sha512_ctx, SHA512_DIGEST_SIZE, &my_digest[0]);
  print_digest(SHA512_DIGEST_SIZE, &my_digest[0]);
  printf("\n");
  
  printf("Test of single block message of SHA-512/224.\n");
  sha512_224_init(&my_sha512_ctx);
  sha512_update(&my_sha512_ctx, 3, &my_msg[0]);
  sha512_224_digest(&my_sha512_ctx, SHA224_DIGEST_SIZE, &my_digest[0]);
  print_digest(SHA224_DIGEST_SIZE, &my_digest[0]);
  printf("\n\n");
  
  printf("Test of single block message of SHA-512/256.\n");
  sha512_256_init(&my_sha512_ctx);
  sha512_update(&my_sha512_ctx, 3, &my_msg[0]);
  sha512_256_digest(&my_sha512_ctx, SHA256_DIGEST_SIZE, &my_digest[0]);
  print_digest(SHA256_DIGEST_SIZE, &my_digest[0]);
  
  return 0;
}

//======================================================================
// EOF sha512x_test.c
//======================================================================

