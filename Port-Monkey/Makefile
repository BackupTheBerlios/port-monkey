#  Copyright (C) 2004 Giuliano Montecarlo
#
#  This file is part of Pub-Monkey
#
#  Pub-Monkey is free software, you can redistribute it and/or
#  modify it under the terms of the Affero General Public License as
#  published by Affero, Inc., either version 1 of the License, or
#  (at your option) any later version.
#
#  Pub-Monkey is distributed in the hope that it will be
#  useful, but WITHOUT ANY WARRANTY, without even the implied warranty
#  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  Affero General Public License for more details.
#
#  You should have received a copy of the Affero General Public
#  License in the COPYING file that comes with YaCE3. If
#  not, write to Affero, Inc., 510 Third Street, Suite 225, San
#  Francisco, CA 94107 USA.

CC = gcc
CXX = g++

CXXFLAGS = -D_GNU_SOURCE -I`ccgnu2-config --includes`
LDFLAGS =  `ccgnu2-config --stdlibs`
OBJS = ftp.o main.o

all: ${OBJS}
	${CXX} -o pub-monkey ${LDFLAGS} $^
clean:
	rm -rf *.o pub-monkey test .*.sw* pubs
