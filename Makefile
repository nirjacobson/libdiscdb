MODULES=discdb	\
				disc		\
				track
OBJECTS=$(foreach MODULE, ${MODULES}, build/${MODULE}.o)
LIBS		= jsoncpp
CFLAGS  = -std=c++17 -O2 -Wall `pkg-config --cflags ${LIBS}` `curlpp-config --cflags` -g
LDFLAGS = `pkg-config --libs ${LIBS}` `curlpp-config --libs`
LIB			= discdb
LIB_FILE = lib${LIB}.so

all: ${LIB_FILE}

${LIB_FILE}: ${OBJECTS}
	g++ -shared $^ -o ${LIB_FILE} ${LDFLAGS}

format:
	astyle -rnCS *.{h,cc}

build/%.o : builddir src/%.cc
	g++ -c $(word 2, $^) -fpic -o $@ ${CFLAGS}

builddir:
	mkdir -p build

clean:
	rm -rf build
	rm -rf ${LIB_FILE}
	rm -rf test*

