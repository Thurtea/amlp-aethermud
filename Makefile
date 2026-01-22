# Makefile for LPC MUD Driver
# Builds the driver with all components

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O2 -std=c99
LDFLAGS = -lm

# Source files
DRIVER_SRCS = driver.c lexer.c parser.c vm.c codegen.c object.c gc.c efun.c array.c mapping.c
DRIVER_OBJS = $(DRIVER_SRCS:.c=.o)

TEST_SRCS = test_lexer.c lexer.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

PARSER_TEST_SRCS = test_parser.c lexer.c parser.c
PARSER_TEST_OBJS = $(PARSER_TEST_SRCS:.c=.o)

VM_TEST_SRCS = test_vm.c vm.c object.c array.c mapping.c gc.c
VM_TEST_OBJS = $(VM_TEST_SRCS:.c=.o)

OBJECT_TEST_SRCS = test_object.c object.c vm.c array.c mapping.c gc.c
OBJECT_TEST_OBJS = $(OBJECT_TEST_SRCS:.c=.o)

GC_TEST_SRCS = test_gc.c gc.c
GC_TEST_OBJS = $(GC_TEST_SRCS:.c=.o)

EFUN_TEST_SRCS = test_efun.c efun.c vm.c object.c array.c mapping.c gc.c
EFUN_TEST_OBJS = $(EFUN_TEST_SRCS:.c=.o)

ARRAY_TEST_SRCS = test_array.c array.c mapping.c vm.c object.c gc.c
ARRAY_TEST_OBJS = $(ARRAY_TEST_SRCS:.c=.o)

MAPPING_TEST_SRCS = test_mapping.c mapping.c array.c vm.c object.c gc.c
MAPPING_TEST_OBJS = $(MAPPING_TEST_SRCS:.c=.o)

# Build targets
all: driver test_lexer test_parser test_vm test_object test_gc test_efun test_array test_mapping

driver: $(DRIVER_OBJS)
	@echo "[Linking] Building driver executable..."
	$(CC) $(CFLAGS) -o driver $(DRIVER_OBJS) $(LDFLAGS)
	@echo "[Success] Driver built successfully!"

test_lexer: $(TEST_OBJS)
	@echo "[Linking] Building lexer test..."
	$(CC) $(CFLAGS) -o test_lexer $(TEST_OBJS) $(LDFLAGS)
	@echo "[Success] Lexer test built successfully!"

test_parser: $(PARSER_TEST_OBJS)
	@echo "[Linking] Building parser test..."
	$(CC) $(CFLAGS) -o test_parser $(PARSER_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] Parser test built successfully!"

test_vm: $(VM_TEST_OBJS)
	@echo "[Linking] Building VM test..."
	$(CC) $(CFLAGS) -o test_vm $(VM_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] VM test built successfully!"

test_object: $(OBJECT_TEST_OBJS)
	@echo "[Linking] Building object test..."
	$(CC) $(CFLAGS) -o test_object $(OBJECT_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] Object test built successfully!"

test_gc: $(GC_TEST_OBJS)
	@echo "[Linking] Building GC test..."
	$(CC) $(CFLAGS) -o test_gc $(GC_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] GC test built successfully!"

test_efun: $(EFUN_TEST_OBJS)
	@echo "[Linking] Building efun test..."
	$(CC) $(CFLAGS) -o test_efun $(EFUN_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] Efun test built successfully!"

test_array: $(ARRAY_TEST_OBJS)
	@echo "[Linking] Building array test..."
	$(CC) $(CFLAGS) -o test_array $(ARRAY_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] Array test built successfully!"

test_mapping: $(MAPPING_TEST_OBJS)
	@echo "[Linking] Building mapping test..."
	$(CC) $(CFLAGS) -o test_mapping $(MAPPING_TEST_OBJS) $(LDFLAGS)
	@echo "[Success] Mapping test built successfully!"

# Object file compilation rules
driver.o: driver.c lexer.h parser.h vm.h
	@echo "[Compiling] driver.c"
	$(CC) $(CFLAGS) -c driver.c

lexer.o: lexer.c lexer.h
	@echo "[Compiling] lexer.c"
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h lexer.h
	@echo "[Compiling] parser.c"
	$(CC) $(CFLAGS) -c parser.c

vm.o: vm.c vm.h lexer.h parser.h object.h
	@echo "[Compiling] vm.c"
	$(CC) $(CFLAGS) -c vm.c

codegen.o: codegen.c codegen.h vm.h parser.h
	@echo "[Compiling] codegen.c"
	$(CC) $(CFLAGS) -c codegen.c

object.o: object.c object.h vm.h
	@echo "[Compiling] object.c"
	$(CC) $(CFLAGS) -c object.c

gc.o: gc.c gc.h
	@echo "[Compiling] gc.c"
	$(CC) $(CFLAGS) -c gc.c

efun.o: efun.c efun.h vm.h
	@echo "[Compiling] efun.c"
	$(CC) $(CFLAGS) -c efun.c

test_lexer.o: test_lexer.c lexer.h
	@echo "[Compiling] test_lexer.c"
	$(CC) $(CFLAGS) -c test_lexer.c

test_parser.o: test_parser.c parser.h lexer.h
	@echo "[Compiling] test_parser.c"
	$(CC) $(CFLAGS) -c test_parser.c

test_vm.o: test_vm.c vm.h object.h
	@echo "[Compiling] test_vm.c"
	$(CC) $(CFLAGS) -c test_vm.c

test_object.o: test_object.c object.h vm.h
	@echo "[Compiling] test_object.c"
	$(CC) $(CFLAGS) -c test_object.c

test_array.o: test_array.c array.h vm.h gc.h
	@echo "[Compiling] test_array.c"
	$(CC) $(CFLAGS) -c test_array.c

test_mapping.o: test_mapping.c mapping.h array.h vm.h gc.h
	@echo "[Compiling] test_mapping.c"
	$(CC) $(CFLAGS) -c test_mapping.c

# Test targets
test: test_lexer test_parser test_vm test_object test_gc test_efun test_array test_mapping
	@echo ""
	@echo "====== Running Lexer Tests ======"
	./test_lexer
	@echo ""
	@echo "====== Running Parser Tests ======"
	./test_parser
	@echo ""
	@echo "====== Running VM Tests ======"
	./test_vm
	@echo ""
	@echo "====== Running Object Tests ======"
	./test_object
	@echo ""
	@echo "====== Running GC Tests ======"
	./test_gc
	@echo ""
	@echo "====== Running Efun Tests ======"
	./test_efun
	@echo ""
	@echo "====== Running Array Tests ======"
	./test_array
	@echo ""
	@echo "====== Running Mapping Tests ======"
	./test_mapping

# Clean build artifacts
clean:
	@echo "[Cleaning] Removing build artifacts..."
	rm -f *.o driver test_lexer test_parser test_vm test_object test_gc test_efun test_array test_mapping
	@echo "[Success] Cleaned!"

# Clean everything including tests
distclean: clean
	@echo "[Cleaning] Removing all generated files..."

# Display help
help:
	@echo "LPC MUD Driver Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  all           - Build driver and tests (default)"
	@echo "  driver        - Build the main driver executable"
	@echo "  test_lexer    - Build lexer test program"
	@echo "  test_parser   - Build parser test program"
	@echo "  test_vm       - Build VM test program"
	@echo "  test_object   - Build object system test program"
	@echo "  test          - Run all tests"
	@echo "  clean         - Remove build artifacts"
	@echo "  distclean     - Remove all generated files"
	@echo "  help          - Display this help message"

.PHONY: all test clean distclean help
