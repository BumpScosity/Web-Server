CC = gcc
FLAGS = -g -pthread

SRC = src
OBJ = obj

program: $(OBJS)
	$(CC) $(FLAGS) -c $(SRC)/Input.c -o $(OBJ)/Input.o
	$(CC) $(FLAGS) -c $(SRC)/Server.c -o $(OBJ)/Server.o
	$(CC) $(FALGS) -c Main.c -o $(OBJ)/Main.o
	$(CC) $(FLAGS) -o Main $(OBJ)/Main.o $(OBJ)/Input.o $(OBJ)/Server.o

clean:
	rm -f Main $(OBJ)/Main.o $(OBJ)/Input.o $(OBJ)/Server.o
