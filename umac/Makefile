#=======================================================================
#
# Makefile
# --------
# Makefile for building the umac test program
#
#
# Author: Joachim Strombergson
# (c) 2014, Secworks Sweden AB
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or 
# without modification, are permitted provided that the following 
# conditions are met: 
# 
# 1. Redistributions of source code must retain the above copyright 
#    notice, this list of conditions and the following disclaimer. 
# 
# 2. Redistributions in binary form must reproduce the above copyright 
#    notice, this list of conditions and the following disclaimer in 
#    the documentation and/or other materials provided with the 
#    distribution. 
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#=======================================================================

KEYGEN_SRC = keygen.c keygen.h
UMACTEST_SRC = umactest.c 

NETTLE_INC_PATH = /usr/local/include/nettle
NETTLE_LIB_PATH = /usr/local/lib
NETTLE_LIB = nettle

CC = clang
CFLAGS = -Wall -pedantic -O0

OBJS = umactest.o keygen.o
TARGET = umactest


all: $(TARGET)


$(TARGET):	$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -L$(NETTLE_LIB_PATH) -l$(NETTLE_LIB)


$(OBJS):	$(UMACTEST_SRC) $(KEYGEN_SRC)
	$(CC) $(CFLAGS) -c $(UMACTEST_SRC) -I$(NETTLE_INC_PATH)
	$(CC) $(CFLAGS) -c $(KEYGEN_SRC) -I$(NETTLE_INC_PATH)


.PHONY: timetest
timetest:	$(TARGET)
	time ./$(TARGET)


.PHONY: clean
clean:
	rm $(TARGET)
	rm $(OBJS)


.PHONY: help
help:
	@echo "Supported targets:"
	@echo "------------------"
	@echo "all:      Build all simulation targets."
	@echo "timetest: Run timed execution of the targets."
	@echo "clean:    Delete all built files."

#=======================================================================
# EOF Makefile
#=======================================================================
