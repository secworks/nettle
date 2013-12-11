/* chacha-test.c
 *
 * Test of the ChaCha stream cipher implementation.
 */

/* nettle, low-level cryptographics library
 *
 * Copyright (C) 2013 Joachim Strömbergson
 * Copyright (C) 2012 Niels Möller
 *  
 * The nettle library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 * 
 * The nettle library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with the nettle library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02111-1301, USA.
 */

#include <stdio.h>
#include "chacha.h"

#define DEBUG 0

void print_block(uint8_t block[64])
{
  uint8_t i;

  for (i = 0 ; i < 64 ; i++) {
    printf("0x%02x ", block[i]);
    if (((i + 1) % 8) == 0) {
      printf("\n");
    }
  }
  printf("\n");
}


void test_chacha(const uint8_t *key, const uint8_t *iv, uint8_t *expected, 
                uint8_t keylength, uint8_t rounds) {
    uint8_t cipher_data[64] =  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t cipher_result[64] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    struct chacha_ctx cipher_ctx;

    uint8_t errors;
    
    chacha_set_key(&cipher_ctx, keylength, key);
    chacha_set_iv(&cipher_ctx, iv);
    chacha_set_rounds(&cipher_ctx, rounds);
    chacha_crypt(&cipher_ctx, 64, &cipher_result[0], &cipher_data[0]);

    if (DEBUG) {
        printf("Result after encryption:\n");
        print_block(cipher_result);
      }

    errors = 0;
    for (uint8_t i = 0 ; i < 64 ; i++) {
      if (cipher_result[i] != expected[i]) {
        errors++;
      }
    }
    
    if (errors > 0) {
      printf("Error, expected:\n");
      print_block(&expected[0]);
      printf("Got:\n");
      print_block(cipher_result);
    }
    else {
      printf("Success, result matched expected.\n");
    }
}


int main(void)
{
  printf("Test of chacha nettle implementation\n");
  printf("------------------------------------\n");

  /* Test vectors from draft-strombergson-chacha-test-vectors */
  
  uint8_t tc1_key[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  uint8_t tc1_iv[8]   = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  uint8_t tc1_expected[64] = {0xe2, 0x8a, 0x5f, 0xa4, 0xa6, 0x7f, 0x8c, 0x5d,
                              0xef, 0xed, 0x3e, 0x6f, 0xb7, 0x30, 0x34, 0x86,
                              0xaa, 0x84, 0x27, 0xd3, 0x14, 0x19, 0xa7, 0x29,
                              0x57, 0x2d, 0x77, 0x79, 0x53, 0x49, 0x11, 0x20,
                              0xb6, 0x4a, 0xb8, 0xe7, 0x2b, 0x8d, 0xeb, 0x85,
                              0xcd, 0x6a, 0xea, 0x7c, 0xb6, 0x08, 0x9a, 0x10,
                              0x18, 0x24, 0xbe, 0xeb, 0x08, 0x81, 0x4a, 0x42,
                              0x8a, 0xab, 0x1f, 0xa2, 0xc8, 0x16, 0x08, 0x1b};

  uint8_t tc1_keylength = 16;
  uint8_t tc1_rounds = 8;
  test_chacha(&tc1_key[0], &tc1_iv[0], &tc1_expected[0], tc1_keylength, tc1_rounds); 


  return 0;
}

