CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20 -static
TARGET = rootrunner
SOURCES = rootrunner.cpp nmaprunner.cpp executor.cpp
OBJS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

rootrunner.o: rootrunner.cpp nmaprunner.hpp
	$(CXX) $(CXXFLAGS) -c rootrunner.cpp -o rootrunner.o

nmaprunner.o: nmaprunner.cpp nmaprunner.hpp executor.hpp
	$(CXX) $(CXXFLAGS) -c nmaprunner.cpp -o nmaprunner.o

executor.o: executor.cpp executor.hpp
	$(CXX) $(CXXFLAGS) -c executor.cpp -o executor.o

clean:
	rm -f $(OBJS) $(TARGET)