CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: factorize

factorize: factorize.cpp
	$(CXX) $(CXXFLAGS) -o factorize factorize.cpp

clean:
	rm -f factorize.exe