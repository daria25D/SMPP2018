CMPL=mpic++
.PHONY eratosthenes check
.SILENT check eratosthenes
all: eratosthenes

eratosthenes:
	$(CMPL) eratosthenes.cpp -o eratosthenes
check:
	g++ -g check.cpp -o check
test: eratosthenes check
	./reratosthenes 1 100000000 file.txt
	./check file.txt