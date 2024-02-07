TARGET="knuppel"

if [ "$1" == "-c" ]; then
	cmake --build build
	./build/$TARGET
fi

if [ "$1" == "-d" ]; then
	gdb build/$TARGET
fi
