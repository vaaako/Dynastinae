TARGET="dynastinae"

if [ "$1" == "-c" ]; then
	# If cmake directory don't exist
	if [ ! -d build/ ]; then
		cmake -S . -B build
	fi

	# Do a backup
	if [ -f build/$TARGET ]; then
		cp build/$TARGET build/$TARGET.bak
	fi

	# Compile
	cmake --build build

	# Error on compiling
	if [ ! -f build/$TARGET ]; then
		echo "ERROR NOT RUNNING"
		exit
	fi

	# Run
	./build/$TARGET
fi

if [ "$1" == "-d" ]; then
	gdb build/$TARGET
fi
