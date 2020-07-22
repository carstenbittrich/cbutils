CC=clang++
CFLAGS=-c -Wall -std=c++14
LDFLAGS=
INCLUDES=-I/usr/local/Software/spdlog/include
SOURCES=HelloWorld.cxx
OBJECTS=$(SOURCES:.cxx=.o)
EXECUTABLE=HelloWorld

all: $(SOURCES) $(EXECUTABLE)


libHelloWorld.so: $(OBJECTS)
	$(CC) --shared $(LDFLAGS) $(OBJECTS) -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cxx
	$(CC) $(INCLUDES) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	@rm $(OBJECTS) $(EXECUTABLE)
