74c74
<   0xFC19DC68B8CD5B5ULL,0x240CA1CC77AC9C65ULL,
---
>   0x0FC19DC68B8CD5B5ULL,0x240CA1CC77AC9C65ULL,
80c80
<   0x6CA6351E003826FULL,0x142929670A0E6E70ULL,
---
>   0x06CA6351E003826FULL,0x142929670A0E6E70ULL,
99c99
<   0x6F067AA72176FBAULL,0xA637DC5A2C898A6ULL,
---
>   0x06F067AA72176FBAULL,0x0A637DC5A2C898A6ULL,
239a240,305
> 
> 
> /* sha-512/224 variant. */
> void
> sha512_224_init(struct sha512_ctx *ctx)
> {
>   static const uint64_t H0[_SHA512_DIGEST_LENGTH] =
>   {
>     0x8c3d37c819544da2ULL, 0x73e1996689dcd4d6ULL,
>     0x1dfab7ae32ff9c82ULL, 0x679dd514582f9fcfULL,
>     0x0f6d2b697bd44da8ULL, 0x77e36f7304c48942ULL,
>     0x3f9d85a86a1d36c8ULL, 0x1112e6ad91d692a1ULL,
>   };
> 
>   memcpy(ctx->state, H0, sizeof(H0));
> 
>   /* Initialize bit count */
>   ctx->count_low = ctx->count_high = 0;
>   
>   /* Initialize buffer */
>   ctx->index = 0;
> }
> 
> void
> sha512_224_digest(struct sha512_ctx *ctx,
> 	      size_t length,
> 	      uint8_t *digest)
> {
>   assert(length <= SHA224_DIGEST_SIZE);
> 
>   sha512_write_digest(ctx, length, digest);
>   sha512_224_init(ctx);
> }
> 
> 
> /* sha-512/256 variant. */
> void
> sha512_256_init(struct sha512_ctx *ctx)
> {
>   static const uint64_t H0[_SHA512_DIGEST_LENGTH] =
>     {
>       0x22312194fc2bf72cULL, 0x9f555fa3c84c64c2ULL, 
>       0x2393b86b6f53b151ULL, 0x963877195940eabdULL, 
>       0x96283ee2a88effe3ULL, 0xbe5e1e2553863992ULL, 
>       0x2b0199fc2c85b8aaULL, 0x0eb72ddc81c52ca2ULL,
>     };
> 
>   memcpy(ctx->state, H0, sizeof(H0));
> 
>   /* Initialize bit count */
>   ctx->count_low = ctx->count_high = 0;
>   
>   /* Initialize buffer */
>   ctx->index = 0;
> }
> 
> void
> sha512_256_digest(struct sha512_ctx *ctx,
> 	      size_t length,
> 	      uint8_t *digest)
> {
>   assert(length <= SHA256_DIGEST_SIZE);
> 
>   sha512_write_digest(ctx, length, digest);
>   sha512_224_init(ctx);
> }
