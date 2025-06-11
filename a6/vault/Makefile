CXX = g++
CXXFLAGS = -Wall -std=c++11

all: vaultCode vaultInt vaultPainting vaultString

vaultCode: vaultCode.cpp
	$(CXX) $(CXXFLAGS) vaultCode.cpp -o vaultCode

vaultInt: vaultInt.cpp
	$(CXX) $(CXXFLAGS) vaultInt.cpp -o vaultInt

vaultPainting: vaultPainting.cpp
	$(CXX) $(CXXFLAGS) vaultPainting.cpp -o vaultPainting

vaultString: vaultString.cpp
	$(CXX) $(CXXFLAGS) vaultString.cpp -o vaultString

clean:
	rm -f vaultCode vaultInt vaultPainting vaultString
