LIB_DIR="lib"
LIB_NAME="libknuppel"

# Make glad object file
clang -c libs/glad/glad.c -o

# Compile build
make

# Exit if lib don't exist
if [ -f "${LIB_DIR}/${LIB_NAME}.so" ]; then
	exit
fi

sudo cp -r include/ /usr/include/Knupppel     # Move headers
sudo cp -r "${LIB_DIR}${LIB_NAME}.so" /usr/lib # Move lib

