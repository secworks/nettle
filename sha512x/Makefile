#=======================================================================
#
# Makefile
# --------
# Makefile for building the umac test program
#
#=======================================================================

SHA512X_TEST_SRC = sha512x_test.c
SHA2_SRC = sha512.c sha512-compress.c
NETTLE_INCS = nettle-types.h nettle-stdint.h
CC = clang
CLAGS = -Wall
TARGET = sha512x_test


all: $(TARGET)


$(TARGET):	$(SHA512X_TEST_SRC) $(SHA2_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SHA512X_TEST_SRC) $(SHA2_SRC)


#=======================================================================
# EOF Makefile
#=======================================================================
