# Compiler and Flags
CXX = g++
CFLAGS = -O3 -w -fPIC -I./include -I./external/nauty2_8_9 -c
LDFLAGS = -L./external/nauty2_8_9 -Wl,-rpath,$(PWD)/external/nauty2_8_9 -lnauty

# Directories
BIN_DIR = bin
SRC_DIR = src
LIB_DIR = external/nauty2_8_9

# Targets
OBJECTS = $(BIN_DIR)/nautyClassify.o
EXECUTABLE = $(BIN_DIR)/nauty_test

# Default Target
all: set_library_path $(OBJECTS) $(EXECUTABLE)

# Set LD_LIBRARY_PATH dynamically
set_library_path:
	@export LD_LIBRARY_PATH=$(PWD)/$(LIB_DIR):$$LD_LIBRARY_PATH
	@echo "LD_LIBRARY_PATH set to: $(PWD)/$(LIB_DIR)"

# Create bin directory if it doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Build nauty library
$(LIB_DIR)/libnauty.so:
	cd $(LIB_DIR) && ./configure CFLAGS=-fPIC && make

# Compile nautyClassify.cpp into an object file for Chapel
$(BIN_DIR)/nautyClassify.o: $(SRC_DIR)/nautyClassify.cpp include/nautyClassify.h | $(BIN_DIR)
	$(CXX) $(CFLAGS) $< -o $@

# Compile test executable
$(EXECUTABLE): $(SRC_DIR)/test_nautyClassify.cpp $(OBJECTS) $(LIB_DIR)/libnauty.so
	$(CXX) -o $@ $(OBJECTS) $< $(LDFLAGS)

# Run the executable with correct LD_LIBRARY_PATH
run: all
	@LD_LIBRARY_PATH=$(PWD)/$(LIB_DIR) ./$(EXECUTABLE)

# Clean Build Artifacts
clean:
	@echo "Removing objects and executables..."
	rm -rf $(BIN_DIR)
	cd $(LIB_DIR) && make clean

.PHONY: clean set_library_path all run