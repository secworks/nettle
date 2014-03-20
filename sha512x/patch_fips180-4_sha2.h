46a47,52
> #define sha512_224_init   nettle_sha512_224_init
> #define sha512_224_digest nettle_sha512_224_digest
> #define sha512_256_init   nettle_sha512_256_init
> #define sha512_256_digest nettle_sha512_256_digest
> 
>   
128c134,135
< 
---
>   
>   
151a159,177
> 
> /* SHA512_224 and SHA512_256, two truncated versions of SHA512 
> with different initial states. */
> void
> sha512_224_init(struct sha512_ctx *ctx);
> 
> void
> sha512_224_digest(struct sha512_ctx *ctx,
>                   size_t length,
>                   uint8_t *digest);
> 
> void
> sha512_256_init(struct sha512_ctx *ctx);
> 
> void
> sha512_256_digest(struct sha512_ctx *ctx,
>                   size_t length,
>                   uint8_t *digest);
>   
