# Compiler and Flags
CXX = g++
CFLAGS = -O3 -w -fPIC -I./include -I./external/nauty2_8_9 -c
INCLUDES = -I./include -I./external/nauty2_8_9

# Directories
BIN_DIR = bin
SRC_DIR = src
LIB_DIR = external/nauty2_8_9

# Nauty object files needed (excluding our wrapper)
NAUTY_OBJECTS = nauty.o nautil.o naugraph.o schreier.o naurng.o nausparse.o

# Default Target
all: setup nauty_objects copy_objects compile_wrapper test_exe

# Create necessary directories and prepare nauty
setup:
	@mkdir -p $(BIN_DIR)
	@echo "Setting up build environment..."
	@if [ ! -f $(LIB_DIR)/config.h ]; then \
		cd $(LIB_DIR) && ./configure CFLAGS="-fPIC -O3"; \
	fi

# Build nauty object files
nauty_objects:
	@echo "Building nauty objects..."
	@cd $(LIB_DIR) && make $(NAUTY_OBJECTS)

# Copy nauty object files to bin directory
copy_objects: nauty_objects
	@echo "Copying nauty object files to bin directory..."
	@for obj in $(NAUTY_OBJECTS); do \
		cp $(LIB_DIR)/$$obj $(BIN_DIR)/; \
	done

# Compile our wrapper
compile_wrapper: $(SRC_DIR)/nautyClassify.cpp include/nautyClassify.h
	@echo "Compiling nautyClassify.cpp..."
	$(CXX) $(CFLAGS) $< -o $(BIN_DIR)/nautyClassify.o

# Build test executable
test_exe: $(SRC_DIR)/test_nautyClassify.cpp
	@echo "Building test executable..."
	$(CXX) $(INCLUDES) -o $(BIN_DIR)/nauty_test $< \
		$(BIN_DIR)/nautyClassify.o \
		$(addprefix $(BIN_DIR)/,$(NAUTY_OBJECTS))

# Run the test
test: all
	@echo "Running tests..."
	./$(BIN_DIR)/nauty_test

# Verify objects
verify_objects:
	@echo "Checking object files in bin directory:"
	@ls -l $(BIN_DIR)/*.o

# Clean Build Artifacts
clean:
	@echo "Removing objects and executables..."
	rm -rf $(BIN_DIR)
	cd $(LIB_DIR) && make clean

.PHONY: clean setup all test verify_objects nauty_objects copy_objects compile_wrapper test_exe