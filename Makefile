CC = gcc
CFLAGS = -Wall -g -v
TARGET = lpm
# Object files
OBJ =  RouteLookup.o RouteLookupMain.o RouteTrie.o RouteCommon.o

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

clean:
	rm -f $(TARGET) $(OBJ)
