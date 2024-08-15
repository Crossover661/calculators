CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: factorize listPrimes modExp quadraticResidue

factorize: factorize.cpp
	$(CXX) $(CXXFLAGS) -o factorize factorize.cpp

listPrimes: listPrimes.cpp lib/modfuncs.cpp
	$(CXX) $(CXXFLAGS) -o listPrimes listPrimes.cpp lib/modfuncs.cpp

modExp: modExp.cpp lib/modfuncs.cpp
	$(CXX) $(CXXFLAGS) -o modExp modExp.cpp lib/modfuncs.cpp

quadraticResidue: quadraticResidue.cpp lib/modfuncs.cpp
	$(CXX) $(CXXFLAGS) -o quadraticResidue quadraticResidue.cpp lib/modfuncs.cpp

clean:
	rm -f factorize listPrimes modExp