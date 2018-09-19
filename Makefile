TARGET=multimatrix generate print compare
.PHONY: test report
.SILENT: all multiply test report clean
all: multiply

multiply:
	g++ -g multimatrix.cpp -o multimatrix

test:
	bash ./test.sh f 50 50 f 50 50
	bash ./test.sh d 100 100 d 100 100
	bash ./test.sh f 200 200 d 200 200
	bash ./test.sh d 300 300 f 300 300

report: 
	bash ./script.sh d 100 100 d 100 100
	#make arguments for different tests?

clean:
	rm -rf $(TARGET) *.o
	rm -rf *.txt 
	rm -r ./test
