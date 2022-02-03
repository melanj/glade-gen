all : gladegen

gladegen : main.o
	gcc -o gladegen main.o `xml2-config --libs` 

main.o : main.c
	gcc -c main.c `xml2-config --cflags`

clean :
	rm gladegen *.o
