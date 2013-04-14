# Copyright (c) 2013 Lars Vierbergen
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
# 
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
all: program/app

HEADERS = $(wildcard *.h)
CFLAGS = -g -Wall
CDEF= -DEMUL
CC = gcc

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(CDEF)

program/app: $(patsubst %.c,%.o,$(wildcard program/*.c)) lib/emulator.o  lib/platform.o lib/timers.o lib/util.o
	$(CC) $+ -Wall -o $@

clean:
	rm -f program/*.o
	rm -f program/app
