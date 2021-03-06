//======================================================================
//
// umactest.c
// ----------
// Program that tests the functionality of the UMAC authentication
// function and perform benchmarking.
//
//
// Author: Joachim Strombergson
// (c) 2014, Secworks Sweden AB
// All rights reserved.
//
//======================================================================

//------------------------------------------------------------------
// Includes.
//------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <umac.h>
#include "keygen.h"


//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------
#define VERBOSE 1
#define SHOW_OPERANDS 0
#define SHOW_DIGESTS 0
#define COMPARE_DIGESTS 1
#define NUM_MESSAGES 100000000
#define MESSAGE_SIZE 1024
#define UMAC_NONCE_SIZE 16


//------------------------------------------------------------------
// silent_mem_equal()
//
// Side channel silent memory comparison used to check
// digests.
//------------------------------------------------------------------
uint8_t silent_mem_equal(const uint8_t *op0, const uint8_t *op1, uint32_t len)
{
  volatile const uint8_t *a = op0;
  volatile const uint8_t *b = op1;
  volatile uint8_t match = 0;

  for (uint32_t i = 0 ; i < len ; i++)
    {
      match |= a[i] ^ b[i];
    }
  return match == 0;
}


//------------------------------------------------------------------
// test_umac()
//
// perform num_messages of umac digest updates and digest
// extractions using the same key and initial nonce.
//------------------------------------------------------------------
void test_umac(uint32_t num_messages)
{
  if (VERBOSE)
    {
      printf("Running test_umac with %010d messages, each %04d Bytes.\n",
             num_messages, MESSAGE_SIZE);
    }

  // We generate key, nonce and message using Yarrow.
  // TODO: Add functions to display the key, nonce, message.
  uint8_t *my_key = NULL;
  my_key = (uint8_t *)calloc(UMAC_KEY_SIZE, sizeof(uint8_t));
  if (NULL == my_key)
    {
      fprintf(stderr, "Failed to allocate memory for key.\n");
      exit(EXIT_FAILURE);
    }
  gen_key_bytes(UMAC_KEY_SIZE, my_key);
  
  uint8_t *my_nonce = NULL;
  my_nonce = (uint8_t *)calloc(UMAC_NONCE_SIZE, sizeof(uint8_t));
  if (NULL == my_nonce)
    {
      fprintf(stderr, "Failed to allocate memory for nonce.\n");
      exit(EXIT_FAILURE);
    }
  gen_key_bytes(UMAC_NONCE_SIZE, my_nonce);
  
  uint8_t *my_data = NULL;
  my_data = (uint8_t *)calloc(MESSAGE_SIZE, sizeof(uint8_t));
  if (NULL == my_data)
    {
      fprintf(stderr, "Failed to allocate memory for data.\n");
      exit(EXIT_FAILURE);
    }
  gen_key_bytes(MESSAGE_SIZE, my_data);

  if (SHOW_OPERANDS)
    {
      printf("The generated key:\n");
      print_data(UMAC_KEY_SIZE, my_key);

      printf("The generated nonce:\n");
      print_data(UMAC_NONCE_SIZE, my_nonce);

      printf("The generated message:\n");
      print_data(MESSAGE_SIZE, my_data);
    }
  
  
  // Now we do the actual test.
  struct umac128_ctx my_tx_ctx;
  struct umac128_ctx my_rx_ctx;
  uint8_t my_tx_digest[UMAC128_DIGEST_SIZE];
  uint8_t my_rx_digest[UMAC128_DIGEST_SIZE];
  uint32_t i, j;
    
  umac128_set_key(&my_tx_ctx, &my_key[0]);
  umac128_set_nonce (&my_tx_ctx, UMAC_NONCE_SIZE, &my_nonce[0]);

  umac128_set_key(&my_rx_ctx, &my_key[0]);
  umac128_set_nonce (&my_rx_ctx, UMAC_NONCE_SIZE, &my_nonce[0]);
  
  for (i = 0 ; i < num_messages ; i++)
    {
      // Run UMAC on transmit side.
      umac128_update (&my_tx_ctx, MESSAGE_SIZE, &my_data[0]);
      umac128_digest (&my_tx_ctx, UMAC128_DIGEST_SIZE, &my_tx_digest[0]);

      // Run UMAC on receive side and check with given digest.
      umac128_update (&my_rx_ctx, MESSAGE_SIZE, &my_data[0]);
      umac128_digest (&my_rx_ctx, UMAC128_DIGEST_SIZE, &my_rx_digest[0]);
      
      if (SHOW_DIGESTS)
        {
          printf("tx_digest: ");
          for (j = 0 ; j < UMAC128_DIGEST_SIZE ; j++)
            {
              printf("0x%02x ", my_tx_digest[j]);
            }
          printf("\n");

          printf("rx_digest: ");
          for (j = 0 ; j < UMAC128_DIGEST_SIZE ; j++)
            {
              printf("0x%02x ", my_rx_digest[j]);
            }
          printf("\n\n");
        }

      if (COMPARE_DIGESTS)
        {
          if (silent_mem_equal(&my_tx_digest[0], &my_rx_digest[0], UMAC128_DIGEST_SIZE) != 0)
            {
              printf("Error: Digests does not match!\n");
            }
        }
    }
}


//------------------------------------------------------------------
// main()
//------------------------------------------------------------------
int main(void)
{
  printf("Test of umac in nettle.\n");
  printf("-----------------------\n");

  test_umac(NUM_MESSAGES);

  printf("Test done.\n");
  
  return 0;
}

//======================================================================
// EOF umactest.c
//======================================================================
