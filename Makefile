CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -g -O0

TARGET = sh
OBJS = sh.o

$(TARGET): $(OBJS)
	$(CC) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: Oclean clean

Oclean:
	rm -f $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)