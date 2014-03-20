--- /Users/js/Sandbox/external/nettle/sha2.h	2014-01-03 19:29:24.000000000 +0100
+++ sha2.h	2014-03-20 19:52:06.000000000 +0100
@@ -44,6 +44,12 @@
 #define sha512_update nettle_sha512_update
 #define sha512_digest nettle_sha512_digest
 
+#define sha512_224_init   nettle_sha512_224_init
+#define sha512_224_digest nettle_sha512_224_digest
+#define sha512_256_init   nettle_sha512_256_init
+#define sha512_256_digest nettle_sha512_256_digest
+
+  
 /* SHA256 */
 
 #define SHA256_DIGEST_SIZE 32
@@ -125,7 +131,8 @@
 sha512_digest(struct sha512_ctx *ctx,
 	      size_t length,
 	      uint8_t *digest);
-
+  
+  
 /* Internal compression function. STATE points to 8 uint64_t words,
    DATA points to 128 bytes of input data, possibly unaligned, and K
    points to the table of constants. */
@@ -149,6 +156,29 @@
 	      size_t length,
 	      uint8_t *digest);
 
+
+/* SHA512_224 and SHA512_256, two truncated versions of SHA512 
+with different initial states. */
+void
+sha512_224_init(struct sha512_ctx *ctx);
+
+#define sha512_224_update nettle_sha512_update
+
+void
+sha512_224_digest(struct sha512_ctx *ctx,
+                  size_t length,
+                  uint8_t *digest);
+
+void
+sha512_256_init(struct sha512_ctx *ctx);
+
+#define sha512_256_update nettle_sha512_update
+
+void
+sha512_256_digest(struct sha512_ctx *ctx,
+                  size_t length,
+                  uint8_t *digest);
+  
 #ifdef __cplusplus
 }
 #endif
