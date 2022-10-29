.PHONY: run build clean

run: build
	build/LinearCodes

build:
	mkdir build && cd build && cmake .. && cmake --build .

clean:
	rm -rf build/
