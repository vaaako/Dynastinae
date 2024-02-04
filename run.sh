TARGET="knuppel"

if [ "$1" == "-c" ]; then
	cmake --build build
	./build/$TARGET
fi
