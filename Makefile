# COMPILER
CXX = clang++
CXXFLAGS = -std=c++20 -O2 -I./include
DEV_FLAGS = -g -fdiagnostics-color=always -Wextra -Wall -Wuninitialized -Winit-self -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wconversion -Wunreachable-code
LIBS = -lGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# DIRECTORIES
BUILD_DIR = build
OBJS_DIR = $(BUILD_DIR)/MakeFiles
STATICLIB_DIR = $(BUILD_DIR)/lib
LIB_FILES = $(wildcard libs/*.a) # TODO -- To be able to use the static libraries, i need to compile the libraries using -fPIC flag (./configure CFLAGS="-fPIC")

# FILES
SRC_FILES = $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp) # Only the files inside folders
OBJS = $(patsubst src/%.cpp, $(OBJS_DIR)/%.o, $(SRC_FILES)) # Derive object file names from source files

# TARGET
TARGET = Dynastinae
TARGET_LIB = lib$(TARGET).so
TARGET_STATIC = lib$(TARGET).a

$(TARGET_LIB): $(OBJS)
	# Making shared lib
	$(CXX) -shared -o $(BUILD_DIR)/$@ $^ -Wl,--no-as-needed $(LIBS)
	
	# Making static lib
	@mkdir -p $(STATICLIB_DIR)
	ar rcs $(STATICLIB_DIR)/$(TARGET_STATIC) $^
	ranlib $(STATICLIB_DIR)/$(TARGET_STATIC)

# Build all object files from .cpp files
$(OBJS_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

# Build static only
static: $(OBJS)
	@mkdir -p $(STATICLIB_DIR)
	ar rcs $(STATICLIB_DIR)/$(TARGET_STATIC) $^
	ranlib $(STATICLIB_DIR)/$(TARGET_STATIC)




install:
	cp -r include/$(TARGET) /usr/include/
	cp $(BUILD_DIR)/$(TARGET_LIB) /usr/lib

uninstall:
	rm -f /usr/include/$(TARGET)
	rm -f /usr/lib/$(TARGET_LIB)


clean:
	rm $(BUILD_DIR)/$(TARGET_LIB)
	rm -f $(OBJS_DIR) $(STATICLIB_DIR)

rebuild: clean $(TARGET_LIB)




# Make executable
exec:
	$(CXX) $(CXXFLAGS) $(DEV_FLAGS) $(LIBS) $(SRC_FILES) -o $(TARGET)


# This avoid conflicts if some directory has the same name
.PHONY: install uninstall static clean rebuild exec






# - MAKEFILE REFERENCE -
# TARGET: REQUIRES_THIS
# $@ - Target of the rule (Function name)
# $^ - Represents all the prerequisites of the rule (Each from `: HERE`)
# $< - Only the first prerequisite, if have multiples, this represents only the first one
# @cmd - Supress echo - e.g. "@mkdir ..." will not appear on terminal when this command is executed
# $(@D) - path in target
#
# "$(OBJS_DIR)/%.o" in "OBJS" is what triggers the second function
#
#
#
# - FLAGS REFERENCE -
# -shared - Creates a shared library.
# -Wl,--no-as-needed - Prevents dropping of unneeded shared library dependencies
# -Wl,--whole-archive - Ensure that all objects from the static libraries are included in the final shared library
# -ldl -lpthread -lm - Explicitly links the dynamic loader library, threads library and math library
#
# -fPIC - Generates position-independent code
# -c - Compiles source files without linking
# -static - Static linking of libraries
#
#
#
# - MAKE STATIC LIBRARY -
# $(AR) - used to create static libraries
# r - insert the files into the archive
# c - create the archive
# s - create an archive index
# ranlib - generates an index to speed up acess to the symbols in the static library
