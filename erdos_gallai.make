ERDOS_GALLAI_C_FLAGS=-c -O2 -Wall -Wextra -Waggregate-return -Wcast-align -Wcast-qual -Wconversion -Wformat=2 -Winline -Wlong-long -Wmissing-prototypes -Wmissing-declarations -Wnested-externs -Wno-import -Wpointer-arith -Wredundant-decls -Wshadow -Wstrict-prototypes -Wwrite-strings

erdos_gallai: erdos_gallai.o
	gcc -o erdos_gallai erdos_gallai.o

erdos_gallai.o: erdos_gallai.c erdos_gallai.make
	gcc ${ERDOS_GALLAI_C_FLAGS} -o erdos_gallai.o erdos_gallai.c

clean:
	rm -f erdos_gallai erdos_gallai.o
