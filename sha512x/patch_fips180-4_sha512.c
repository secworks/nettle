--- /Users/js/Sandbox/external/nettle/sha512.c	2014-01-03 19:29:24.000000000 +0100
+++ sha512.c	2014-03-20 18:03:50.000000000 +0100
@@ -71,13 +71,13 @@
   0x72BE5D74F27B896FULL,0x80DEB1FE3B1696B1ULL,
   0x9BDC06A725C71235ULL,0xC19BF174CF692694ULL,
   0xE49B69C19EF14AD2ULL,0xEFBE4786384F25E3ULL,
-  0xFC19DC68B8CD5B5ULL,0x240CA1CC77AC9C65ULL,
+  0x0FC19DC68B8CD5B5ULL,0x240CA1CC77AC9C65ULL,
   0x2DE92C6F592B0275ULL,0x4A7484AA6EA6E483ULL,
   0x5CB0A9DCBD41FBD4ULL,0x76F988DA831153B5ULL,
   0x983E5152EE66DFABULL,0xA831C66D2DB43210ULL,
   0xB00327C898FB213FULL,0xBF597FC7BEEF0EE4ULL,
   0xC6E00BF33DA88FC2ULL,0xD5A79147930AA725ULL,
-  0x6CA6351E003826FULL,0x142929670A0E6E70ULL,
+  0x06CA6351E003826FULL,0x142929670A0E6E70ULL,
   0x27B70A8546D22FFCULL,0x2E1B21385C26C926ULL,
   0x4D2C6DFC5AC42AEDULL,0x53380D139D95B3DFULL,
   0x650A73548BAF63DEULL,0x766A0ABB3C77B2A8ULL,
@@ -96,7 +96,7 @@
   0xBEF9A3F7B2C67915ULL,0xC67178F2E372532BULL,
   0xCA273ECEEA26619CULL,0xD186B8C721C0C207ULL,
   0xEADA7DD6CDE0EB1EULL,0xF57D4F7FEE6ED178ULL,
-  0x6F067AA72176FBAULL,0xA637DC5A2C898A6ULL,
+  0x06F067AA72176FBAULL,0x0A637DC5A2C898A6ULL,
   0x113F9804BEF90DAEULL,0x1B710B35131C471BULL,
   0x28DB77F523047D84ULL,0x32CAAB7B40C72493ULL,
   0x3C9EBE0A15C9BEBCULL,0x431D67C49C100D4CULL,
@@ -237,3 +237,69 @@
   sha512_write_digest(ctx, length, digest);
   sha384_init(ctx);
 }
+
+
+/* sha-512/224 variant. */
+void
+sha512_224_init(struct sha512_ctx *ctx)
+{
+  static const uint64_t H0[_SHA512_DIGEST_LENGTH] =
+  {
+    0x8c3d37c819544da2ULL, 0x73e1996689dcd4d6ULL,
+    0x1dfab7ae32ff9c82ULL, 0x679dd514582f9fcfULL,
+    0x0f6d2b697bd44da8ULL, 0x77e36f7304c48942ULL,
+    0x3f9d85a86a1d36c8ULL, 0x1112e6ad91d692a1ULL,
+  };
+
+  memcpy(ctx->state, H0, sizeof(H0));
+
+  /* Initialize bit count */
+  ctx->count_low = ctx->count_high = 0;
+  
+  /* Initialize buffer */
+  ctx->index = 0;
+}
+
+void
+sha512_224_digest(struct sha512_ctx *ctx,
+	      size_t length,
+	      uint8_t *digest)
+{
+  assert(length <= SHA224_DIGEST_SIZE);
+
+  sha512_write_digest(ctx, length, digest);
+  sha512_224_init(ctx);
+}
+
+
+/* sha-512/256 variant. */
+void
+sha512_256_init(struct sha512_ctx *ctx)
+{
+  static const uint64_t H0[_SHA512_DIGEST_LENGTH] =
+    {
+      0x22312194fc2bf72cULL, 0x9f555fa3c84c64c2ULL, 
+      0x2393b86b6f53b151ULL, 0x963877195940eabdULL, 
+      0x96283ee2a88effe3ULL, 0xbe5e1e2553863992ULL, 
+      0x2b0199fc2c85b8aaULL, 0x0eb72ddc81c52ca2ULL,
+    };
+
+  memcpy(ctx->state, H0, sizeof(H0));
+
+  /* Initialize bit count */
+  ctx->count_low = ctx->count_high = 0;
+  
+  /* Initialize buffer */
+  ctx->index = 0;
+}
+
+void
+sha512_256_digest(struct sha512_ctx *ctx,
+	      size_t length,
+	      uint8_t *digest)
+{
+  assert(length <= SHA256_DIGEST_SIZE);
+
+  sha512_write_digest(ctx, length, digest);
+  sha512_224_init(ctx);
+}
