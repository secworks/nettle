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

  // TC1: All zero key and IV. 128 bit key and 8 rounds.
  uint8_t tc1_key[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t tc1_keylength = 16;

  uint8_t tc1_iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  uint8_t tc1_rounds = 8;

  uint8_t tc1_expected[64] = {0xe2, 0x8a, 0x5f, 0xa4, 0xa6, 0x7f, 0x8c, 0x5d,
                              0xef, 0xed, 0x3e, 0x6f, 0xb7, 0x30, 0x34, 0x86,
                              0xaa, 0x84, 0x27, 0xd3, 0x14, 0x19, 0xa7, 0x29,
                              0x57, 0x2d, 0x77, 0x79, 0x53, 0x49, 0x11, 0x20,
                              0xb6, 0x4a, 0xb8, 0xe7, 0x2b, 0x8d, 0xeb, 0x85,
                              0xcd, 0x6a, 0xea, 0x7c, 0xb6, 0x08, 0x9a, 0x10,
                              0x18, 0x24, 0xbe, 0xeb, 0x08, 0x81, 0x4a, 0x42,
                              0x8a, 0xab, 0x1f, 0xa2, 0xc8, 0x16, 0x08, 0x1b};

  test_chacha(&tc1_key[0], &tc1_iv[0], &tc1_expected[0], tc1_keylength, tc1_rounds); 

  
  // TC2: All zero key and IV. 128 bit key and 12 rounds.
  uint8_t tc2_key[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t tc2_keylength = 16;

  uint8_t tc2_iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  uint8_t tc2_rounds = 12;

  uint8_t tc2_expected[64] = {0xe1, 0x04, 0x7b, 0xa9, 0x47, 0x6b, 0xf8, 0xff,
                              0x31, 0x2c, 0x01, 0xb4, 0x34, 0x5a, 0x7d, 0x8c,
                              0xa5, 0x79, 0x2b, 0x0a, 0xd4, 0x67, 0x31, 0x3f,
                              0x1d, 0xc4, 0x12, 0xb5, 0xfd, 0xce, 0x32, 0x41,
                              0x0d, 0xea, 0x8b, 0x68, 0xbd, 0x77, 0x4c, 0x36,
                              0xa9, 0x20, 0xf0, 0x92, 0xa0, 0x4d, 0x3f, 0x95,
                              0x27, 0x4f, 0xbe, 0xff, 0x97, 0xbc, 0x84, 0x91,
                              0xfc, 0xef, 0x37, 0xf8, 0x59, 0x70, 0xb4, 0x50};

  test_chacha(&tc2_key[0], &tc2_iv[0], &tc2_expected[0], tc2_keylength, tc2_rounds); 

  
  // TC3: All zero key and IV. 128 bit key and 20 rounds.
  uint8_t tc3_key[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  uint8_t tc3_keylength = 16;

  uint8_t tc3_iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  uint8_t tc3_rounds = 20;

  uint8_t tc3_expected[64] = {0x89, 0x67, 0x09, 0x52, 0x60, 0x83, 0x64, 0xfd,
                              0x00, 0xb2, 0xf9, 0x09, 0x36, 0xf0, 0x31, 0xc8,
                              0xe7, 0x56, 0xe1, 0x5d, 0xba, 0x04, 0xb8, 0x49,
                              0x3d, 0x00, 0x42, 0x92, 0x59, 0xb2, 0x0f, 0x46,
                              0xcc, 0x04, 0xf1, 0x11, 0x24, 0x6b, 0x6c, 0x2c,
                              0xe0, 0x66, 0xbe, 0x3b, 0xfb, 0x32, 0xd9, 0xaa,
                              0x0f, 0xdd, 0xfb, 0xc1, 0x21, 0x23, 0xd4, 0xb9,
                              0xe4, 0x4f, 0x34, 0xdc, 0xa0, 0x5a, 0x10, 0x3f};

  test_chacha(&tc3_key[0], &tc3_iv[0], &tc3_expected[0], tc3_keylength, tc3_rounds); 

  
  // TC4: Sequence patterns in key and IV. 256 bit key and 8 rounds.
  uint8_t tc4_key[32] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                         0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
                         0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
                         0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
  uint8_t tc4_keylength = 32;

  uint8_t tc4_iv[8] = {0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x59, 0x68, 0x77};

  uint8_t tc4_rounds = 8;

  uint8_t tc4_expected[64] = {0x60, 0xfd, 0xed, 0xbd, 0x1a, 0x28, 0x0c, 0xb7,
                              0x41, 0xd0, 0x59, 0x3b, 0x6e, 0xa0, 0x30, 0x90,
                              0x10, 0xac, 0xf1, 0x8e, 0x14, 0x71, 0xf6, 0x89,
                              0x68, 0xf4, 0xc9, 0xe3, 0x11, 0xdc, 0xa1, 0x49,
                              0xb8, 0xe0, 0x27, 0xb4, 0x7c, 0x81, 0xe0, 0x35,
                              0x3d, 0xb0, 0x13, 0x89, 0x1a, 0xa5, 0xf6, 0x8e,
                              0xa3, 0xb1, 0x3d, 0xd2, 0xf3, 0xb8, 0xdd, 0x08,
                              0x73, 0xbf, 0x37, 0x46, 0xe7, 0xd6, 0xc5, 0x67};

  test_chacha(&tc4_key[0], &tc4_iv[0], &tc4_expected[0], tc4_keylength, tc4_rounds); 

  
  // TC5: Sequence patterns in key and IV. 256 bit key and 12 rounds.
  uint8_t tc5_key[32] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                         0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
                         0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
                         0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
  uint8_t tc5_keylength = 32;

  uint8_t tc5_iv[8] = {0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x59, 0x68, 0x77};

  uint8_t tc5_rounds = 12;

  uint8_t tc5_expected[64] = {0x6e, 0x93, 0xf2, 0x58, 0x16, 0xed, 0x81, 0x51,
                              0xdb, 0xab, 0x6c, 0x9a, 0x50, 0x0d, 0x56, 0x2e,
                              0xf3, 0xac, 0x3c, 0xfd, 0x18, 0x99, 0x70, 0x8c,
                              0x15, 0x74, 0xb9, 0x12, 0xf7, 0x1b, 0x13, 0x12,
                              0x11, 0x49, 0x85, 0x21, 0x70, 0xbd, 0x0f, 0x45,
                              0x43, 0xf0, 0xb7, 0x3f, 0x9f, 0x27, 0xc3, 0x63,
                              0x77, 0x36, 0x32, 0xe9, 0xe2, 0xaa, 0x63, 0x24,
                              0xf6, 0xbe, 0xd8, 0x7a, 0xb0, 0xd0, 0x30, 0x5e};
  
  test_chacha(&tc5_key[0], &tc5_iv[0], &tc5_expected[0], tc5_keylength, tc5_rounds); 

  
  // TC6: Sequence patterns in key and IV. 256 bit key and 20 rounds.
  uint8_t tc6_key[32] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                         0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
                         0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
                         0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00};
  uint8_t tc6_keylength = 32;

  uint8_t tc6_iv[8] = {0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x59, 0x68, 0x77};

  uint8_t tc6_rounds = 20;

  uint8_t tc6_expected[64] = {0x87, 0xfa, 0x92, 0x06, 0x10, 0x43, 0xca, 0x5e,
                              0x63, 0x1f, 0xed, 0xd8, 0x8e, 0x8b, 0xfb, 0x84,
                              0xad, 0x6b, 0x21, 0x3b, 0xde, 0xe4, 0xbc, 0x80,
                              0x6e, 0x27, 0x64, 0x93, 0x5f, 0xb8, 0x90, 0x97,
                              0x21, 0x8a, 0x89, 0x7b, 0x7a, 0xea, 0xd1, 0x0e,
                              0x1b, 0x17, 0xf6, 0x80, 0x2b, 0x2a, 0xbd, 0xd9,
                              0x55, 0x94, 0x90, 0x30, 0x83, 0x73, 0x56, 0x13,
                              0xd6, 0xb3, 0x53, 0x1b, 0x9e, 0x0d, 0x1b, 0x67};

  test_chacha(&tc6_key[0], &tc6_iv[0], &tc6_expected[0], tc6_keylength, tc6_rounds); 

  return 0;
}

