TARGET=multimatrix generate print compare
.PHONY: test report
.SILENT: all multiply generate test report clean
all: multiply

print:
	g++ -g print.cpp -o print

multiply:
	g++ -g multimatrix.cpp -o multimatrix

generate: multiply
	g++ -g generate.cpp -o generate
	./generate.sh f 50 50 f 50 50 A1.dat B1.dat C01.dat 
	./generate.sh d 10 10 d 10 10 A2.dat B2.dat C02.dat
	./generate.sh f 20 20 f 20 20 A3.dat B3.dat C03.dat

test: generate
	./test.sh ./test/A1.dat ./test/B1.dat ./test/C01.dat test1.txt
	./test.sh ./test/A2.dat ./test/B2.dat ./test/C02.dat test2.txt
	./test.sh ./test/A3.dat ./test/B3.dat ./test/C03.dat test3.txt

report: 
	./script.sh d 300 300 d 300 300 plot300.svg
	./script.sh f 500 500 f 500 500 plot500.svg
	./script.sh d 1000 1000 f 1000 1000 plot1000.svg

clean:
	rm -rf $(TARGET) *.o
	rm -rf *.txt 
	rm -rf ./test/C?.dat
	rm -rf report || true
