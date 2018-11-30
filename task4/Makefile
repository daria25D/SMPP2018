TARGET=print generate new_mv
all: $(TARGET)

new_mv: new_mv.cpp
	mpicxx -O3 -std=c++11 new_mv.cpp -o new_mv
print: print.cpp
	g++ -O3 -g print.cpp -o print
generate: generate.cpp
	g++ -O3 -g generate.cpp -o generate
clean:
	rm -rf $(TARGET) *.o