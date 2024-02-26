# goodsuff
OBJ=bf.o cl.o ft1.o ft2.o ft3.o
all: goodsuff

goodsuff: $(OBJ) goodsuff.h goodsuff.c
	gcc -O3 -o goodsuff $(OBJ) goodsuff.c

bf.o: bf.c
	gcc -O3 -c bf.c

cl.o: cl.c
	gcc -O3 -c cl.c

ft1.o: ft1.c
	gcc -O3 -c ft1.c

ft2.o: ft2.c
	gcc -O3 -c ft2.c

ft3.o: ft3.c
	gcc -O3 -c ft3.c


