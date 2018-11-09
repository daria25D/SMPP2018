CMPL=mpic++ -std=c++11
TARGET=eratosthenes check
.PHONY: eratosthenes check
.SILENT: check eratosthenes

all: eratosthenes

eratosthenes: eratosthenes.cpp
	$(CMPL) eratosthenes.cpp -o eratosthenes
check: check.cpp
	g++ -g check.cpp -o check
test: eratosthenes check
	mkdir -p test
	./eratosthenes 1 1000 ./test/test1.txt > ./test/info.txt
	./check ./test/test1.txt
	./eratosthenes 5 1000 ./test/test2.txt >> ./test/info.txt
	./check ./test/test2.txt
	./eratosthenes 100 500 ./test/test3.txt >> ./test/info.txt
	./check ./test/test3.txt

clean:
	rm -rf $(TARGET) *.o
	rm -rf ./test/
