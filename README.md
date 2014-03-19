# nettle #
This repo contains development contributions to the
[Nettle](http://git.lysator.liu.se/nettle/nettle) project. One subdir
for each contribution. The subdirs contains enough from Nettle to build,
test and integrate the feature.


## umactest ##
A simple programming for testing and benchmarking the implementation of
UMAC in Nettle for init, update of nonce, update of state and extraction
of digest.


## sha512x ##
Changes to the implementation of SHA-512 in Nettle to add support for
SHA-512/224 and SHA-512/256 as defined in the NIST document [FIPS 180-4](http://csrc.nist.gov/publications/fips/fips180-4/fips-180-4.pdf) (pdf).


## ChaCha ##
Implementation of the [ChaCha](http://cr.yp.to/chacha.html) stream
cipher by Daniel J. Bernstein. ChaCha is a fast, modern cipher that is
being proposed as a replacement to RC4 in TLS. See: 

 * http://tools.ietf.org/html/draft-agl-tls-chacha20poly1305-00
 * http://tools.ietf.org/html/draft-mavrogiannopoulos-chacha-tls-00


### Status ###
**2013-12-12:** Having received some go ahead from Niels Möller we are
moving the chacha implementation to subdir and creating a separate
branch for the patch completion to integrate ChaCha into nettle.


**2013-12-11:** First version of the ChaCha stream cipher. The code is
complete. There is a test program that verifies that the cipger works
with 128 and 256 bit keys and 8, 12, 20 rounds.


