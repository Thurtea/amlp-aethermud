# Makefile for LPC MUD Driver
# Standard C project structure with src/, tests/, build/ directories

CC = gcc
# Allow users to override CFLAGS, but keep include dirs in CPPFLAGS so
# they are not lost when CFLAGS is overridden on the make command line.
# Default CFLAGS (can be overridden by target-specific assignments)
CFLAGS ?= -Wall -Wextra -D_DEFAULT_SOURCE -g -O2 -std=c99
CPPFLAGS += -Isrc
LDFLAGS = -lm

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Common sources needed for all tests (MUST BE BEFORE RULES!)
TEST_COMMON_SOURCES = $(SRC_DIR)/vm.c \
                      $(SRC_DIR)/object.c \
					  tools/vm_trace.c \
                      $(SRC_DIR)/array.c \
                      $(SRC_DIR)/mapping.c \
                      $(SRC_DIR)/gc.c \
					  $(SRC_DIR)/efun.c \
					  $(TEST_DIR)/test_driver_stub.c \
					  $(SRC_DIR)/test_stubs.c \
                      $(SRC_DIR)/compiler.c \
                      $(SRC_DIR)/program_loader.c \
                      $(SRC_DIR)/program.c \
                      $(SRC_DIR)/master_object.c \
                      $(SRC_DIR)/session.c \
                      $(SRC_DIR)/lexer.c \
                      $(SRC_DIR)/parser.c \
                      $(SRC_DIR)/codegen.c \
                      $(SRC_DIR)/preprocessor.c

# Driver source files
DRIVER_SRCS = $(SRC_DIR)/driver.c $(SRC_DIR)/server.c $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c \
              $(SRC_DIR)/vm.c $(SRC_DIR)/codegen.c $(SRC_DIR)/object.c \
			  tools/vm_trace.c \
			  $(SRC_DIR)/gc.c $(SRC_DIR)/efun.c $(SRC_DIR)/array.c \
              $(SRC_DIR)/mapping.c $(SRC_DIR)/compiler.c $(SRC_DIR)/program.c \
              $(SRC_DIR)/simul_efun.c $(SRC_DIR)/program_loader.c \
              $(SRC_DIR)/preprocessor.c \
              $(SRC_DIR)/master_object.c $(SRC_DIR)/terminal_ui.c \
              $(SRC_DIR)/websocket.c $(SRC_DIR)/session.c \
              $(SRC_DIR)/room.c $(SRC_DIR)/chargen.c $(SRC_DIR)/skills.c \
			  $(SRC_DIR)/combat.c $(SRC_DIR)/item.c $(SRC_DIR)/psionics.c \
			  $(SRC_DIR)/magic.c $(SRC_DIR)/wiz_tools.c $(SRC_DIR)/race_loader.c \
			  $(SRC_DIR)/ui_frames.c $(SRC_DIR)/death.c $(SRC_DIR)/npc.c

# Count source files
TOTAL_FILES = $(words $(DRIVER_SRCS))

# Default target - just build the driver
.PHONY: all driver tests clean distclean help test debug release asan asan_tests

# Target-specific builds
# Usage: `make debug` or `make release` or `make asan` (builds driver)
# `make asan_tests` builds all tests with ASan/UBSan instrumentation and runs them.
debug: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -g -O0 -std=c99
debug: $(BUILD_DIR)/driver

release: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -O2 -std=c99 -DNDEBUG
release: $(BUILD_DIR)/driver

asan: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -g -O1 -std=c99 -fsanitize=address,undefined -fno-omit-frame-pointer
asan: $(BUILD_DIR)/driver

# Build and run tests under ASan
asan_tests: CFLAGS := -Wall -Wextra -D_DEFAULT_SOURCE -g -O1 -std=c99 -fsanitize=address,undefined -fno-omit-frame-pointer
asan_tests: tests


driver: $(BUILD_DIR)/driver


# Build driver
$(BUILD_DIR)/driver: $(DRIVER_SRCS)
	@mkdir -p $(BUILD_DIR)
	@echo
	@echo "AMLP MUD DRIVER - BUILD IN PROGRESS"
	@count=0; for src in $(DRIVER_SRCS); do \
		count=$$((count + 1)); \
		name=$$(basename $$src); \
		printf " [*] [%2d/$(TOTAL_FILES)] Compiling %s\\n" $$count "$$name"; \
	done
	@echo
	@echo "[LINK] Creating driver executable..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ $(LDFLAGS) 2>$(BUILD_DIR)/.warnings.txt; \
	status=$$?; \
	warns=$$(grep -c "warning:" $(BUILD_DIR)/.warnings.txt 2>/dev/null | head -1 || echo 0); \
	warns=$${warns:-0}; \
	if [ "$$status" -eq 0 ]; then \
		echo "BUILD SUCCESSFUL"; \
		echo "Files compiled: $(TOTAL_FILES)"; \
		echo "Warnings:       $$warns"; \
		echo "Errors:         0"; \
		if [ "$$warns" -gt 0 ]; then \
			echo "Warning details: diagnostics/README.md"; \
			echo "Quick reference: diagnostics/quick-reference.md"; \
		fi; \
	else \
		echo "X BUILD FAILED"; \
		echo "See diagnostics/undeclared-identifier.md for common compilation errors"; \
		cat $(BUILD_DIR)/.warnings.txt; \
		exit 1; \
	fi
	@echo

# Build all tests
tests: $(BUILD_DIR)/test_lexer $(BUILD_DIR)/test_parser $(BUILD_DIR)/test_vm \
       $(BUILD_DIR)/test_object $(BUILD_DIR)/test_gc $(BUILD_DIR)/test_efun \
       $(BUILD_DIR)/test_array $(BUILD_DIR)/test_mapping $(BUILD_DIR)/test_compiler \
       $(BUILD_DIR)/test_program $(BUILD_DIR)/test_simul_efun $(BUILD_DIR)/test_vm_execution \
       $(BUILD_DIR)/test_parser_stability $(BUILD_DIR)/test_lpc_execution
	@echo "All test binaries built"

# Build everything
all: driver tests


# Pattern rule for all test targets
$(BUILD_DIR)/test_%: $(TEST_DIR)/test_%.c $(TEST_COMMON_SOURCES)
	@mkdir -p $(BUILD_DIR)
	@echo "[*] Building test: $@"
	@echo "[*] Compiling test sources..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -I$(SRC_DIR) -I$(TEST_DIR) $(LDFLAGS)
	@status=$$?; \
	       if [ "$$status" -eq 0 ]; then \
		       echo "[OK] Test build successful: $@"; \
	else \
		echo "[FAIL] Test build failed: $@"; \
		exit 1; \
	fi

# Specific override for test_simul_efun (needs simul_efun.c)
$(BUILD_DIR)/test_simul_efun: $(TEST_DIR)/test_simul_efun.c $(TEST_COMMON_SOURCES) $(SRC_DIR)/simul_efun.c
	@mkdir -p $(BUILD_DIR)
	@echo "[*] Building test: $@"
	@echo "[*] Compiling test sources..."
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -I$(SRC_DIR) -I$(TEST_DIR) $(LDFLAGS)
	@status=$$?; \
	       if [ "$$status" -eq 0 ]; then \
		       echo "[OK] Test build successful: $@"; \
	else \
		echo "[FAIL] Test build failed: $@"; \
		exit 1; \
	fi

# Run all tests
test: tests
	@echo ""
	@echo "=== RUNNING TESTS ==="
	@for t in lexer parser vm object gc efun array mapping compiler program simul_efun vm_execution lpc_execution; do \
		echo "[*] Running $$t tests..."; \
		$(BUILD_DIR)/test_$$t 2>&1 | sed 's/^/  /'; \
		echo ""; \
	done
	@echo "=== DONE ==="

# Clean build artifacts
clean:
	@echo "[*] Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete"

# Clean everything
distclean: clean
	@echo "[*] Removing all generated files..."
	@echo "Distclean complete"

# Display help
help:
	@echo ""
	@echo "AMLP MUD Driver Build System"
	@echo ""
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  driver    - Build the main driver executable (default)"
	@echo "  tests     - Build all test executables"
	@echo "  all       - Build driver and tests"
	@echo "  test      - Build and run all tests"
	@echo "  clean     - Remove build artifacts"
	@echo "  distclean - Remove all generated files"
	@echo "  help      - Display this help message"
	@echo ""
