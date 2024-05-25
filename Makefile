# COMPILER
CXX = clang++
CXXFLAGS = -std=c++20 -O2
DEV_FLAGS = -g -fdiagnostics-color=always -Wextra -Wall -Wuninitialized -Winit-self -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wconversion -Wunreachable-code

# LIBS
LIBS = -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# DIRECTORIES
SRC_FILES = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp) # Only the files inside folders
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES)) # Derive object file names from source files

# TARGET
TARGET = dynastinae
TARGET_LIB = libdynastinae.so

# Quick tutorial:
# - MAKEFILE REFERENCE -
# TARGET: REQUIRES_THIS
# $@ - Target of the rule (Function name)
# $^ - Represents all the prerequisites of the rule (Each from `: HERE`)
# $< - Only the first prerequisite, if have multiples, this represents only the first one
#
# - FLAGS REFERENCE -
# -shared - Creates a shared library.
# -Wl,--no-as-needed - Prevents dropping of unneeded shared library dependencies
# -fPIC - Generates position-independent code
# -c - Compiles source files without linking
# -static - Static linking of libraries


$(TARGET_LIB): $(OBJS)
	$(CXX) -shared -o src/$@ $^ -Wl,--no-as-needed $(LIBS)

# Build object files of each .cpp
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D) # Make dir for each .cpp
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

static: $(TARGET_LIB) $(OBJS)
	$(CXX) -shared -o src/$@ $^ -Wl,--no-as-needed $(LIBS) -static

clean:
	rm $(TARGET)
	rm -rf build/*/*.o build/$(TARGET_LIB)

rebuild: clean $(TARGET_LIB)

exec:
	$(CXX) $(CXXFLAGS) $(DEV_FLAGS) $(LIBS) $(SRC_FILES) -o $(TARGET)


# This avoid conflicts if some directory has the same name
.PHONY: static clean rebuild exec
