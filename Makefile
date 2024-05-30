# COMPILER
CXX = clang++
CXXFLAGS = -std=c++20 -O2 -I../include
DEV_FLAGS = -g -fdiagnostics-color=always -Wextra -Wall -Wuninitialized -Winit-self -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wconversion -Wunreachable-code

# LIBS
LIBS = -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# DIRECTORIES
BUILD_DIR = lib
SRC_FILES = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp) # Only the files inside folders
OBJS = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES)) # Derive object file names from source files

# TARGET
TARGET = dynastinae
TARGET_LIB = lib$(TARGET).so
TARGET_STATIC = lib$(TARGET).a

# Quick tutorial:
# - MAKEFILE REFERENCE -
# TARGET: REQUIRES_THIS
# $@ - Target of the rule (Function name)
# $^ - Represents all the prerequisites of the rule (Each from `: HERE`)
# $< - Only the first prerequisite, if have multiples, this represents only the first one
# @cmd - Supress echo. e.g. "@mkdir ..." will not appear on terminal when this command is executed
#
#
# - FLAGS REFERENCE -
# -shared - Creates a shared library.
# -Wl,--no-as-needed - Prevents dropping of unneeded shared library dependencies
# -fPIC - Generates position-independent code
# -c - Compiles source files without linking
# -static - Static linking of libraries

$(TARGET_LIB): $(OBJS)
	$(CXX) -shared -o $(BUILD_DIR)/$@ $^ -Wl,--no-as-needed $(LIBS)

# Build object files of each .cpp
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D) # Make dir for each .cpp
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<


# - MAKE STATIC LIBRARY -
# $(AR) - used to create static libraries
# r - insert the files into the archive
# c - create the archive
# s - create an archive index
# ranlib - generates an index to speed up acess to the symbols in the static library
static: $(OBJS)
	ar rcs lib/$(TARGET_STATIC) $^
	ranlib lib/$(TARGET_STATIC)




install: $(TARGET_LIB)
	# Move to /usr/include
	cp -r include/ /usr/include/$(TARGET)

	# Move library to /usr/lib
	cp lib/$(TARGET_LIB) /usr/lib

uninstall:
	# Move to /usr/include
	rm -rf /usr/include/$(TARGET)

	# Move library to /usr/lib
	rm -f /usr/lib/$(TARGET_LIB)




clean:
	rm $(BUILD_DIR) $(TARGET_LIB)
	rm -f $(TARGET)
	# rm -rf build/*/*.o build/$(TARGET_LIB)

rebuild: clean $(TARGET_LIB)

exec:
	$(CXX) $(CXXFLAGS) $(DEV_FLAGS) $(LIBS) $(SRC_FILES) -o $(TARGET)


# This avoid conflicts if some directory has the same name
.PHONY: install uninstall static clean rebuild exec
