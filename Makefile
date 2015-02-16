BUILDTYPE ?= Release

all: uv_zip

config.gypi: configure
	./configure

build/Makefile:
	deps/run_gyp uv_zip.gyp -Iconfig.gypi --depth=. -Goutput_dir=. --generator-output=./build -f make

.PHONY: uv_zip
uv_zip: build/Makefile
	make -C build uv_zip

.PHONY: test
test: build/Makefile
	make -C build test
	build/$(BUILDTYPE)/test



.PHONY: xcode
xcode:
	deps/run_gyp uv_zip.gyp -Iconfig.gypi --depth=. -Goutput_dir=. --generator-output=./build -f xcode
	open build/uv_zip.xcodeproj

.PHONY: clean
clean:
	rm -rf build
