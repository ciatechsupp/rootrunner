CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20

rootrunner: main.o
	$(CXX) $^ -o $@

main.o: main.cpp
	$(CXX) -c $< -o $@

clean:
	rm -f rootrunner main.o