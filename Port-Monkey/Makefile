CC = gcc
CXX = g++

CXXFLAGS = -D_GNU_SOURCE -I`ccgnu2-config --includes`
LDFLAGS = `ccgnu2-config --stdlibs`
OBJS = ftp.o main.o

all: ${OBJS}
	${CXX} -o port-monkey ${LDFLAGS} $^
clean:
	rm -rf *.o port-monkey test
