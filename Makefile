CC       = clang
CXX      = clang++
CXXFLAGS = -std=c++11 -Weverything -Wno-c++98-compat -Wno-missing-prototypes -Wno-padded -Wno-shadow
CFLAGS   =
CPPFLAGS = -O3

MASON_DIR = .mason

INCLUDE += -Iinclude
INCLUDE += $(shell ./configure cflags)
LDFLAGS  += $(shell ./configure ldflags)

BIN      = test/test

SRCS    += src/uv_zip.c
SRCS    += $(shell find ./test -name "*.cpp")

OBJS     = $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRCS)))

$(BIN): $(OBJS) Makefile
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDE) -c -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDE) -c -o $@ $^

.PHONY: test
test: $(BIN)
	@$(BIN)

.PHONY: clean
clean:
	rm -rf $(BIN)
	rm -rf src/*.o
	rm -rf test/*.o
