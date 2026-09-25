.SUFFIXES:
.PHONY: all compile checkstyle test clean format
.PRECIOUS: src/%.o

CXX = clang++ -Wall -Wextra -O3 -g -Iinclude
BASENAME = GameOfLife


OBJS = src/$(BASENAME).o src/MockTerminalManager.o src/NcursesTerminalManager.o src/UserInput.o

LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread

all: compile format checkstyle test

compile: $(BASENAME)Main

checkstyle:
	clang-format-18 --dry-run -Werror include/*.h src/*.cpp

format:
	clang-format-18 -i include/*.h src/*.cpp

test: $(BASENAME)Test
	./$<

src/%.o: src/%.cpp include/*.h
	$(CXX) -c $< -o $@


%Main: src/%Main.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)


%Test: src/%Test.o $(OBJS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f src/*.o
