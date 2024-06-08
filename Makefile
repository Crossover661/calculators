CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: factorize listPrimes

factorize: factorize.cpp
	$(CXX) $(CXXFLAGS) -o factorize factorize.cpp

listPrimes: listPrimes.cpp
	$(CXX) $(CXXFLAGS) -o listPrimes listPrimes.cpp

clean:
	rm -f factorize listPrimes