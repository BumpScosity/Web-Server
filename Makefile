CC = gcc
FLAGS = -pthread

SRC = src
OBJ = obj

program: $(OBJS)
	$(CC) $(FLAGS) -c $(SRC)/Config.c -o $(OBJ)/Config.o
	$(CC) $(FLAGS) -c $(SRC)/Errors.c -o $(OBJ)/Errors.o
	$(CC) $(FLAGS) -c $(SRC)/Connections.c -o $(OBJ)/Connections.o
	$(CC) $(FLAGS) -c $(SRC)/Server.c -o $(OBJ)/Server.o
	$(CC) $(FALGS) -c Main.c -o $(OBJ)/Main.o
	$(CC) $(FLAGS) -o Main $(OBJ)/Main.o $(OBJ)/Config.o $(OBJ)/Errors.o $(OBJ)/Connections.o $(OBJ)/Server.o

clean:
	rm -f Main $(OBJ)/Main.o $(OBJ)/Config.o $(OBJ)/Errors.o $(OBJ)/Connections.o $(OBJ)/Server.o
