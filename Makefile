# COMPILER
CC = clang
CCFLAGS = -O3
CXX = clang++
CXXFLAGS = -std=c++20 -O3

# LIBS
LIBS = -lSDL2
GLAD_OBJ = glad.o
GLAD_SRC = libs/glad

# DIRECTORIES
BUILD_DIR = lib
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*/*.cpp) # Only the files inside folders
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES)) # Derive object file names from source files

# TARGET
TARGET = knuppel
TARGET_LIB = knuppel.so
# $@ - Func name


# FUNCTIONS
#
# Build shared library
$(TARGET_LIB): $(OBJS) $(BUILD_DIR)/$(GLAD_OBJ)
	$(CXX) -shared -o $(BUILD_DIR)/$@ $^ $(LIBS)

# Build object files of each .cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D) # Make dir for each .cpp
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

# Build and copy glad object
$(BUILD_DIR)/$(GLAD_OBJ): $(GLAD_SRC)/$(GLAD_OBJ)
	@mkdir -p $(BUILD_DIR) # Make build dir
	$(CC) $(CCFLAGS) -fPIC -c $(GLAD_SRC)/glad.c -o $(BUILD_DIR)/$(GLAD_OBJ) # Compile glad
	# cp $< $(BUILD_DIR)/$(GLAD_OBJ)

clean:
	rm -rf $(BUILD_DIR)/*/*.o $(BUILD_DIR)/$(TARGET_LIB)

# Remove target and run function $(TARGET_LIB)
rebuild: clean $(TARGET_LIB)

# PHONY (make clean and make rebuild)
.PHONY: clean rebuild
