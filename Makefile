CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp blowfish.cpp storage.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=storage

TEMPLATE_FILE=template.html
TEMPLATE_COMPILER=set_template.py

all: generate_template $(SOURCES) $(EXECUTABLE)

generate_template:
	python $(TEMPLATE_COMPILER) $(TEMPLATE_FILE) page_template.h

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
