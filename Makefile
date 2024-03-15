# COMPILER
CXX = clang++
CXXFLAGS = -std=c++20 -O2

# LIBS
LIBS = -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# DIRECTORIES
BUILD_DIR = lib
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*/*.cpp) # Only the files inside folders
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES)) # Derive object file names from source files

# TARGET
TARGET = knuppel
TARGET_LIB = libknuppel.so
# $@ - Func name


# FUNCTIONS
#
# Build shared library
$(TARGET_LIB): $(OBJS)
	# $(CXX) -shared -o $(BUILD_DIR)/$@ $^ $(LIBS)
	$(CXX) -shared -o $(BUILD_DIR)/$@ $^ -Wl,--no-as-needed $(LIBS)

# Build object files of each .cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D) # Make dir for each .cpp
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)/*/*.o $(BUILD_DIR)/$(TARGET_LIB)

# Remove target and run function $(TARGET_LIB)
rebuild: clean $(TARGET_LIB)

# PHONY (make clean and make rebuild)
.PHONY: clean rebuild
