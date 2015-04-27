#####################################################################
# psnprintf Test & Benchmark Makefile

# Platform
include Makefile.config
PLATFORM_CONFIG = config/platform.$(PLATFORM)
include $(PLATFORM_CONFIG)
CC = g++

# Config
INCLUDEDIR = ../

TEST_EXE = $(EXEPRE)test$(EXEEXT)
BENCH_EXE = $(EXEPRE)bench$(EXEEXT)

INC += -I$(INCLUDEDIR)
LIBS += -lstdc++ -lm
    
#####################################################################
   
TEST_OBJECTS = main.o \
                test.o \
                ../psnprintf.o

TEST_INCLUDES = ../psnprintf.h \
                 test.h \
                 psnprintf.test
                
BENCH_OBJECTS = bench.o \
                 ../psnprintf.o
                 
BENCH_INCLUDES = ../psnprintf.h

#####################################################################
# Rules

# Default Target
all:        testprog benchprog
clean:
	$(RM) $(TEST_OBJECTS) $(TEST_EXE) $(BENCH_OBJECTS) $(BENCH_EXE)

# Test suite
testprog: $(TEST_EXE)
	
$(TEST_EXE): $(TEST_OBJECTS)
	$(CC) -g -o $@ $(TEST_OBJECTS) $(LIBS)
	
# Benchmark
benchprog: $(BENCH_EXE)
	
$(BENCH_EXE): $(BENCH_OBJECTS)
	$(CC) -o $@ $(BENCH_OBJECTS) $(LIBS)

#####################################################################
# Dependencies

$(TEST_OBJECTS) : $(TEST_INCLUDES)

$(BENCH_OBJECTS) : $(BENCH_INCLUDES)

bench.o : bench.cpp
	$(CC) -O3 $(CFLAGS) $(INC) -c bench.cpp -o $@

test.o : test.cpp
	$(CC) -g $(CFLAGS) $(INC) -c test.cpp -o $@

main.o : main.cpp
	$(CC) -g $(CFLAGS) $(INC) -c main.cpp -o $@

../psnprintf.o : ../psnprintf.c
	gcc $(CFLAGS) -ansi -Wall -pedantic $(INC) -c ../psnprintf.c -o ../psnprintf.o
