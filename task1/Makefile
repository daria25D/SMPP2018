TARGET=multimatrix generate print compare
.PHONY: test report
.SILENT: all multimatrix generate test report clean print
all: multiply

print:
	g++ -g print.cpp -o print

multimatrix:
	g++ -g multimatrix.cpp -o multimatrix

generate: multimatrix
	g++ -g generate.cpp -o generate
	./generate.sh f 50 50 f 50 50 A1.dat B1.dat C01.dat 
	./generate.sh d 10 10 d 10 10 A2.dat B2.dat C02.dat
	./generate.sh f 20 20 f 20 20 A3.dat B3.dat C03.dat

test: multimatrix
	./test.sh ./test/A1.dat ./test/B1.dat ./test/C01.dat test1.txt
	./test.sh ./test/A2.dat ./test/B2.dat ./test/C02.dat test2.txt
	./test.sh ./test/A3.dat ./test/B3.dat ./test/C03.dat test3.txt

report: 
	> time_all.txt
	./script.sh d 300 300 d 300 300  time_all.txt   
	./script.sh d 300 300 d 300 300  time_all.txt  
	./script.sh d 300 300 d 300 300  time_all.txt  
	./script.sh d 300 300 d 300 300  time_all.txt  
	./script.sh d 300 300 d 300 300  time_all.txt  
	./average.sh  time_all.txt time_average.txt 
	./plot.sh plot300av.svg "test 300 average (double)"

	> time_all.txt
	./script.sh f 500 500 f 500 500  time_all.txt 
	./script.sh f 500 500 f 500 500  time_all.txt
	./script.sh f 500 500 f 500 500  time_all.txt
	./script.sh f 500 500 f 500 500  time_all.txt
	./script.sh f 500 500 f 500 500  time_all.txt
	./average.sh  time_all.txt time_average.txt 
	./plot.sh plot500av.svg "test 500 average (float)"
	
	> time_all.txt
	./script.sh d 1000 1000 d 1000 1000  time_all.txt  
	./script.sh d 1000 1000 d 1000 1000  time_all.txt    
	./script.sh d 1000 1000 d 1000 1000  time_all.txt    
	./script.sh d 1000 1000 d 1000 1000  time_all.txt    
	./script.sh d 1000 1000 d 1000 1000  time_all.txt      
	./average.sh  time_all.txt time_average.txt 
	./plot.sh plot1000av.svg "test 1000 average (double)"

clean:
	rm -rf $(TARGET) *.o
	rm -rf *.txt 
	rm -rf ./test/C?.dat
	rm -rf report || true
