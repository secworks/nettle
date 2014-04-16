#=======================================================================
#
# Makefile
# --------
# Makefile for building the umac test program
#
#=======================================================================


UMACTEST_SRC = umactest.c
NETTLE_INC_PATH = /usr/local/include/nettle
NETTLE_LIB_PATH = /usr/local/lib
NETTLE_LIB = nettle
CC = clang
CFLAGS = -Wall -O2
TARGET = umactest


all: $(TARGET)


$(TARGET):	$(UMACTEST_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(UMACTEST_SRC) -I$(NETTLE_INC_PATH) -L$(NETTLE_LIB_PATH) -l$(NETTLE_LIB)


#=======================================================================
# EOF Makefile
#=======================================================================
