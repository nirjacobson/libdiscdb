MODULES  = discdb	\
				   disc		\
				   track
OBJECTS  = $(foreach MODULE, ${MODULES}, build/${MODULE}.o)
LIBS		 = jsoncpp
CFLAGS   = -std=c++17 -O2 -Wall `pkg-config --cflags ${LIBS}` `curlpp-config --cflags` -g
LDFLAGS  = `pkg-config --libs ${LIBS}` `curlpp-config --libs`
LIB			 = discdb
LIB_FILE = lib${LIB}.so
INCLUDE_DIR  = /usr/include/${LIB}

all: build/ ${LIB_FILE}

install: ${LIB_FILE}
	sudo cp $< /usr/lib
	sudo mkdir -p ${INCLUDE_DIR}
	sudo cp src/*.h ${INCLUDE_DIR}


${LIB_FILE}: ${OBJECTS}
	g++ -shared $^ -o ${LIB_FILE} ${LDFLAGS}

format:
	astyle -rnNCS *.{h,cc}

build/%.o : src/%.cc
	g++ -c $< -fpic -o $@ ${CFLAGS}

build/:
	mkdir -p build

clean:
	rm -rf build
	rm -f ${LIB_FILE}
	rm -f test*

distclean:
	sudo rm -f /usr/lib/${LIB_FILE}
	sudo rm -rf ${INCLUDE_DIR}
