TARGET = main
LDFLAGS = -lncurses
VPATH = src

OBJECTS = main.o display.o file.o

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	$(RM) *.o $(TARGET)
