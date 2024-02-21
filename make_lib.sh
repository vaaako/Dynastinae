LIB_DIR="lib"
LIB_NAME="libknuppel.so"
FULL_PATH="${LIB_DIR}/${LIB_NAME}"

# Compile build
make clean
make

# Exit if lib doesn't exist
if [ ! -f "${FULL_PATH}" ]; then
	exit
fi


echo -e "\n ===== MOVING FILES ====="
# sudo rm -rf /usr/include/Knuppel
# sudo rm "/usr/lib/${LIB_NAME}"
sudo cp -r include/ /usr/include/Knupppel   # Move headers
sudo cp "${FULL_PATH}" /usr/lib # Move lib

