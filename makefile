TARGET = main
LIBS = -lncurses
LDFLAGS = $(LIBS)

SRC_DIR = src
VPATH = $(SRC_DIR)

$(TARGET): main.o displayer.o file.o
	$(CC) -o $(TARGET) $(SRC_DIR)/main.o $(SRC_DIR)/displayer.o $(SRC_DIR)/file.o $(LDFLAGS)

main.o: main.c
	$(CC) -c -o $(SRC_DIR)/$@ $<

displayer.o: displayer.c
	$(CC) -c -o $(SRC_DIR)/$@ $<

file.o: file.c
	$(CC) -c -o $(SRC_DIR)/$@ $<


clean:
	$(RM) $(SRC_DIR)/*.o
	$(RM) $(TARGET)
