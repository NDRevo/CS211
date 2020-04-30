TARGET = mexp
CC     = clang
CFLAGS = -g -std=c99 -Wall -Wvla -Werror

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(TARGET) *.o *.a *.dylib *.dSYM
