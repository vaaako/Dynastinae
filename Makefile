CXX = clang++
CXXFLAGS = -std=c++20 -O3
DEVFLAGS = -g -fdiagnostics-color=always -Wextra -Wall -Wuninitialized -Winit-self -Wfloat-equal -Wundef -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Wcast-qual -Wswitch-default -Wconversion -Wunreachable-code

GLAD = $(wildcard libs/glad/glad.c)
LIBS = $(GLAD) -lSDL2

LIB_DIR = lib
BUILD_DIR = $(LIB_DIR)/build
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

# Derive object file names from source files
# OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS)) $(BUILD_DIR)/glad.o


TARGET = knuppel
LIBRARY = $(LIB_DIR)/lib$(TARGET).so


# $@ - Func name

all: $(LIBRARY)

# BUild shared library
$(LIBRARY): $(OBJS)
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	$(CXX) -shared -lSDL2 -o $@ $^

# BUild object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

# $(BUILD_DIR)/glad.o: $(GLAD)
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) -fPIC -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)

# Additional dependencies
# Add dependencies if needed, e.g., header files
$(OBJS): | $(BUILD_DIR)

.PHONY: all clean

