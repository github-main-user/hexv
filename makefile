TARGET = main
LIBS = -lncurses
LDFLAGS = $(LIBS)

SRC_DIR = src
VPATH = $(SRC_DIR)

$(TARGET): main.o display.o file.o
	$(CC) -o $(TARGET) $(SRC_DIR)/main.o $(SRC_DIR)/display.o $(SRC_DIR)/file.o $(LDFLAGS)

main.o: main.c
	$(CC) -c -o $(SRC_DIR)/$@ $<

display.o: display.c
	$(CC) -c -o $(SRC_DIR)/$@ $<

file.o: file.c
	$(CC) -c -o $(SRC_DIR)/$@ $<


clean:
	$(RM) $(SRC_DIR)/*.o
	$(RM) $(TARGET)
