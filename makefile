
# --------------------------------------------------- #
# julia drahozal 2441134
# eecs 665
# assignment 1: nfa2dfa
#
# makefile
# compile main executable
# --------------------------------------------------- #

# variables

INPUT = txt/input.txt

OUTPUT = txt/output.txt
PROG_CORRECT = nfa2dfa.exe
OUTPUT_CORRECT = txt/output_expected.txt

PROG = main
OBJS = main.o nfa.o dfa.o

CXX = g++
VERS = -std=c++11
DEBUG = -g
WARN = -Wall
LDFLAGS = $(WARN) $(DEBUG)
CXXFLAGS = -c $(VERS) $(WARN) $(DEBUG)

# --------------------------------------------------- #

# executable

$(PROG) : $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(PROG)

# object files

main.o : src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp

nfa.o : src/nfa.cpp
	$(CXX) $(CXXFLAGS) src/nfa.cpp

dfa.o : src/dfa.cpp
	$(CXX) $(CXXFLAGS) src/dfa.cpp

# --------------------------------------------------- #

# test

test: $(PROG)
	./$(PROG) < $(INPUT)

# diff

diff : $(PROG) $(INPUT)
	./$(PROG) < $(INPUT) > $(OUTPUT)
	./$(PROG_CORRECT) < $(INPUT) > $(OUTPUT_CORRECT)
	diff $(OUTPUT) $(OUTPUT_CORRECT)

# clean

clean :
	rm -f $(PROG) $(OBJS)
	rm -f $(OUTPUT)
	clear
