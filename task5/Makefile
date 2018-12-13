TARGET=print generate matrix
all: $(TARGET)

matrix: matrix.cpp
	mpicxx -O3 -std=c++11 matrix.cpp -o matrix
print: print.cpp
	g++ -O3 -g print.cpp -o print
generate: generate.cpp
	g++ -O3 -g generate.cpp -o generate
clean:
	rm -rf $(TARGET) *.o