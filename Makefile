all: code

code: solution.cpp
	g++ -o code solution.cpp -std=c++17 -O2

clean:
	rm -f code
