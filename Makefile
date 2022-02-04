CC = gcc
CFLAGS = `xml2-config --cflags`
LDFLAGS = `xml2-config --libs`

all : gladegen

gladegen : main.o
	$(CC) -o gladegen main.o $(LDFLAGS)

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

clean :
	rm gladegen *.o
