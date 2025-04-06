# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Build rule
dashboard: DB.c DB_impl.c dashboard.c
	$(CC) $(CFLAGS) -o dashboard DB.c DB_impl.c dashboard.c

# Clean rule
clean:
	rm -f dashboard Tests/outputPicnicTableSmall.csv


testing: dashboard
	./dashboard < Tests/test_input.txt
	diff Tests/outputPicnicTableSmall.csv Tests/PicnicTableSmall.csv
	valgrind --leak-check=full ./dashboard < Tests/test_input.txt
	./dashboard < Tests/test_input_full.txt

