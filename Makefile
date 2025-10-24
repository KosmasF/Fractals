CC = gcc
CXX = g++
CASM = as

CFLAGS = -g -Wall -Wextra -D_REENTRANT -MMD -MP
CPPFLAGS = -g -Wall -Wextra -D_REENTRANT -MMD -MP
ASMFLAGS = -g

CPP_SOURCES = $(wildcard *.cpp)
CPP_OBJECTS = $(patsubst %.cpp,%_cpp.o,$(CPP_SOURCES))

C_SOURCES = $(wildcard *.c)
C_OBJECTS = $(patsubst %.c,%_c.o,$(C_SOURCES))

ASM_SOURCES = $(wildcard *.asm)
ASM_OBJECTS = $(patsubst %.asm,%_asm.o,$(ASM_SOURCES))

DEP_FILES = $(patsubst %.o,%.d,$(CPP_OBJECTS)) $(patsubst %.o,%.d,$(C_OBJECTS))

LDFLAGS = -L. -L/usr/lib -no-pie
LDLIBS = -lm -lSDL2 -lSDL2_ttf -lOpenCL
INC = -I. -I/usr/include/SDL2

EXECUTABLE = main

$(EXECUTABLE) : $(CPP_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS)
	$(CXX) $(LDFLAGS) $(LDLIBS) -o $(EXECUTABLE) $(CPP_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS)

$(CPP_OBJECTS): %_cpp.o : %.cpp 
	$(CXX) $(INC) $(CPPFLAGS) -c $< -o $@

-include $(DEP_FILES)

$(C_OBJECTS): %_c.o : %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

-include $(DEP_FILES)

$(ASM_OBJECTS): %_asm.o : %.asm
	$(CASM) $(ASMFLAGS) -c $^ -o $@

clean:
	rm -f *o *d $(EXECUTABLE)
