rtspTest : ./rtspTest.cpp
	g++  -g  -std=c++2a rtspTest.cpp  -o  $@.o

StrSplitTest : StrSplitTest.cpp
	g++ -std=c++2a $@.cpp  -o  $@.out
StrStructTest: StrStructTest.cpp
	g++ -std=c++2a $@.cpp -o $@.out

ParserTest : ParserTest.cpp
	g++ -g -std=c++2a $@.cpp -o $@.out

.PHONY: clean

clean :
	rm ./*.o ./*.out