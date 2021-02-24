CC = g++

TARGET = a1_part1

all:
	$(CC) $(TARGET).cpp -o $(TARGET) `pkg-config --cflags --libs opencv`

run:
	./$(TARGET)
clean:
	$(RM) $(TARGET)
.PHONY: clean
