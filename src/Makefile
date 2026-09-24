.SUFFIXES:
.PHONY: all compile checkstyle test clean format
.PRECIOUS: %.o

CXX = clang++ -Wall -Wextra -O3 -g -Iinclude
BASENAME = GameOfLife
OBJS = $(BASENAME).o MockTerminalManager.o NcursesTerminalManager.o UserInput.o
LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread

all: compile format checkstyle test

compile: $(BASENAME)Main

checkstyle:
	clang-format-18 --dry-run -Werror include/*.h *.cpp

format:
	clang-format-18 -i include/*.h *.cpp

test: $(BASENAME)Test
	./$<

%.o: %.cpp include/*.h
	$(CXX) -c $<

%Main: %Main.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o
