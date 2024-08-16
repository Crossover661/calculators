CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: factorize listPrimes modExp quadraticResidue

factorize: factorize.cpp
	$(CXX) $(CXXFLAGS) -o factorize factorize.cpp

listPrimes: listPrimes.cpp lib/mathfuncs.cpp
	$(CXX) $(CXXFLAGS) -o listPrimes listPrimes.cpp lib/mathfuncs.cpp

modExp: modExp.cpp lib/mathfuncs.cpp
	$(CXX) $(CXXFLAGS) -o modExp modExp.cpp lib/mathfuncs.cpp

quadraticResidue: quadraticResidue.cpp lib/mathfuncs.cpp
	$(CXX) $(CXXFLAGS) -o quadraticResidue quadraticResidue.cpp lib/mathfuncs.cpp

clean:
	rm -f factorize listPrimes modExp quadraticResidue