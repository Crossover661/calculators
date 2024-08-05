CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: factorize listPrimes modExp

factorize: factorize.cpp
	$(CXX) $(CXXFLAGS) -o factorize factorize.cpp

listPrimes: listPrimes.cpp
	$(CXX) $(CXXFLAGS) -o listPrimes listPrimes.cpp

modExp: modExp.cpp
	$(CXX) $(CXXFLAGS) -o modExp modExp.cpp

clean:
	rm -f factorize listPrimes modExp