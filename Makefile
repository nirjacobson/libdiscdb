MODULES=discdb	\
				disc		\
				track
OBJECTS=$(foreach MODULE, ${MODULES}, build/${MODULE}.o)
LIBS		= jsoncpp
CFLAGS  = -std=c++17 -O2 -Wall `pkg-config --cflags ${LIBS}` `curlpp-config --cflags` -g
LDFLAGS = `pkg-config --libs ${LIBS}` `curlpp-config --libs`
LIB			= discdb

all: build ${LIB}

test: build ${LIB}
	g++ ${CFLAGS} ${LDFLAGS} test.cc -L. -l${LIB} -o test

${LIB}: ${OBJECTS}
	g++ -shared $^ -o lib$@.so ${LDFLAGS}

build/%.o : src/%.cc
	g++ -c $< -fpic -o $@ ${CFLAGS}

build:
	mkdir -p build

clean:
	rm -rf build
	rm -rf lib${LIB}.so
	rm -rf test*

