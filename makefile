CC = g++
CFLAGS =
EXEC_NAME = PathOpening
INCLUDES = 
OBJ_FILES = Pixel.o Image.o PO.o main.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<