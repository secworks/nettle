//======================================================================
//
// sha512x_test.c
// --------------
// Program that tests the SHA-512/224 and SHA-512/256 functionality
// for Nettle.
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
#include <stdio.h>
#include <stdint.h>
#include "sha2.h"


int main(void)
{
  struct sha512_ctx my_sha512_ctx;

  sha512_init(&my_sha512_ctx);

  printf("Testelitest!\n");
  
  return 0;
}


//======================================================================
// EOF sha512x_test.c
//======================================================================

