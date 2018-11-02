TARGET=blocks generate print compare
CMPLFLAGS=g++ -g -O2
REPORT00=./report/l1_32_ijk.txt ./report/l2_32_ijk.txt ./report/l3_32_ijk.txt ./report/tlbim_32_ijk.txt ./report/tlbdm_32_ijk.txt ./report/cyc_32_ijk.txt ./report/ins_32_ijk.txt 
REPORT10=./report/l1_32_ikj.txt ./report/l2_32_ikj.txt ./report/l3_32_ikj.txt ./report/tlbim_32_ikj.txt ./report/tlbdm_32_ikj.txt ./report/cyc_32_ikj.txt ./report/ins_32_ikj.txt 
REPORT01=./report/l1_opt_ijk.txt ./report/l2_opt_ijk.txt ./report/l3_opt_ijk.txt ./report/tlbim_opt_ijk.txt ./report/tlbdm_opt_ijk.txt ./report/cyc_opt_ijk.txt ./report/ins_opt_ijk.txt 
REPORT11=./report/l1_opt_ikj.txt ./report/l2_opt_ikj.txt ./report/l3_opt_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/cyc_opt_ikj.txt ./report/ins_opt_ikj.txt 
NAMES="32x32 ijk" "32x32 ikj" "opt ikj"
.PHONY: test report generate
.SILENT: all blocks generate test report1000 report2000 report3000 report4000 report5000 report clean print
all: blocks compare print generate

print:
	$(CMPLFLAGS) print.cpp -o print

compare:
	$(CMPLFLAGS) compare.cpp -o compare 

blocks:
	g++ -I/usr/local/include -O0 blocks.cpp /usr/local/lib/libpapi.a -o blocks

generate: blocks 
	mkdir -p test
	$(CMPLFLAGS) generate.cpp -o generate
	./generate.sh 500 500 500 500 A1.dat B1.dat C01.dat 500
	./generate.sh 1000 1000 1000 1000 A2.dat B2.dat C02.dat 1000
	./generate.sh 200 200 200 200 A3.dat B3.dat C03.dat 200

test: compare blocks print
#change data in test.sh, add size of bloks 
	mkdir -p test
	./test.sh ./test/A1.dat ./test/B1.dat ./test/C01.dat test1.txt
	./test.sh ./test/A2.dat ./test/B2.dat ./test/C02.dat test2.txt
	./test.sh ./test/A3.dat ./test/B3.dat ./test/C03.dat test3.txt

report1000: blocks
	$(CMPLFLAGS) generate.cpp -o generate 
	mkdir -p report
	#nulling files
	> ./report/report_32_ijk.txt && > ./report/report_opt_ijk.txt && > ./report/report_32_ikj.txt && > ./report/report_opt_ikj.txt
	> ./report/l1_32_ijk.txt && > ./report/l1_opt_ijk.txt && > ./report/l1_32_ikj.txt && > ./report/l1_opt_ikj.txt 
	> ./report/l2_32_ijk.txt && > ./report/l2_opt_ijk.txt && > ./report/l2_32_ikj.txt && > ./report/l2_opt_ikj.txt
	> ./report/l3_32_ijk.txt && > ./report/l3_opt_ijk.txt && > ./report/l3_32_ikj.txt && > ./report/l3_opt_ikj.txt
	> ./report/tlbim_32_ijk.txt && > ./report/tlbim_opt_ijk.txt && > ./report/tlbim_32_ikj.txt && > ./report/tlbim_opt_ikj.txt
	> ./report/tlbdm_32_ijk.txt && > ./report/tlbdm_opt_ijk.txt && > ./report/tlbdm_32_ikj.txt && > ./report/tlbdm_opt_ikj.txt
	> ./report/cyc_32_ijk.txt && > ./report/cyc_opt_ijk.txt && > ./report/cyc_32_ikj.txt && > ./report/cyc_opt_ikj.txt
	> ./report/ins_32_ijk.txt && > ./report/ins_opt_ijk.txt && > ./report/ins_32_ikj.txt && > ./report/ins_opt_ikj.txt
	#multiplying matrixes with blocks 32x32 with orders ijk and ikj
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	#multiplying matrices with blocks of optimal sizes with orders ijk and ikj
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	#formatting data (counters and time)
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ikj.txt ./report/l1_a1.txt ./report/l1_a2.txt ./report/l1_a3.txt 5 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ikj.txt ./report/l2_a1.txt ./report/l2_a2.txt ./report/l3_a3.txt 5 
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ikj.txt ./report/l3_a1.txt ./report/l3_a2.txt ./report/l3_a3.txt 5
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbim_a1.txt ./report/tlbim_a2.txt ./report/tlbim_a3.txt 6 
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm_a1.txt ./report/tlbdm_a2.txt ./report/tlbdm_a3.txt 6 
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ikj.txt ./report/cyc_a1.txt ./report/cyc_a2.txt ./report/cyc_a3.txt 3
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ikj.txt ./report/ins_a1.txt ./report/ins_a2.txt ./report/cyc_a3.txt 3 
	./processdat.sh ./report/report_32_ijk.txt ./report/report_32_ikj.txt ./report/report_opt_ikj.txt ./report/report_a1.txt ./report/report_a2.txt ./report/report_a3.txt 2


report2000: blocks
	$(CMPLFLAGS) generate.cpp -o generate 
	mkdir -p report
	> ./report/report_32_ijk.txt && > ./report/report_opt_ijk.txt && > ./report/report_32_ikj.txt && > ./report/report_opt_ikj.txt
	> ./report/l1_32_ijk.txt && > ./report/l1_opt_ijk.txt && > ./report/l1_32_ikj.txt && > ./report/l1_opt_ikj.txt 
	> ./report/l2_32_ijk.txt && > ./report/l2_opt_ijk.txt && > ./report/l2_32_ikj.txt && > ./report/l2_opt_ikj.txt
	> ./report/l3_32_ijk.txt && > ./report/l3_opt_ijk.txt && > ./report/l3_32_ikj.txt && > ./report/l3_opt_ikj.txt
	> ./report/tlbim_32_ijk.txt && > ./report/tlbim_opt_ijk.txt && > ./report/tlbim_32_ikj.txt && > ./report/tlbim_opt_ikj.txt
	> ./report/tlbdm_32_ijk.txt && > ./report/tlbdm_opt_ijk.txt && > ./report/tlbdm_32_ikj.txt && > ./report/tlbdm_opt_ikj.txt
	> ./report/cyc_32_ijk.txt && > ./report/cyc_opt_ijk.txt && > ./report/cyc_32_ikj.txt && > ./report/cyc_opt_ikj.txt
	> ./report/ins_32_ijk.txt && > ./report/ins_opt_ijk.txt && > ./report/ins_32_ikj.txt && > ./report/ins_opt_ikj.txt
	./report.sh 2000 2000 2000 2000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 2000 2000 2000 2000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 2000 2000 2000 2000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 2000 2000 2000 2000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 2000 2000 2000 2000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 2000 2000 2000 2000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 2000 2000 2000 2000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 2000 2000 2000 2000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 2000 2000 2000 2000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 2000 2000 2000 2000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ikj.txt ./report/l1_a1.txt ./report/l1_a2.txt ./report/l1_a3.txt 5 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ikj.txt ./report/l2_a1.txt ./report/l2_a2.txt ./report/l3_a3.txt 5 
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ikj.txt ./report/l3_a1.txt ./report/l3_a2.txt ./report/l3_a3.txt 5
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbim_a1.txt ./report/tlbim_a2.txt ./report/tlbim_a3.txt 6 
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm_a1.txt ./report/tlbdm_a2.txt ./report/tlbdm_a3.txt 6 
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ikj.txt ./report/cyc_a1.txt ./report/cyc_a2.txt ./report/cyc_a3.txt 3
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ikj.txt ./report/ins_a1.txt ./report/ins_a2.txt ./report/cyc_a3.txt 3 
	./processdat.sh ./report/report_32_ijk.txt ./report/report_32_ikj.txt ./report/report_opt_ikj.txt ./report/report_a1.txt ./report/report_a2.txt ./report/report_a3.txt 2


report3000: blocks
	$(CMPLFLAGS) generate.cpp -o generate 
	mkdir -p report
	> ./report/report_32_ijk.txt && > ./report/report_opt_ijk.txt && > ./report/report_32_ikj.txt && > ./report/report_opt_ikj.txt
	> ./report/l1_32_ijk.txt && > ./report/l1_opt_ijk.txt && > ./report/l1_32_ikj.txt && > ./report/l1_opt_ikj.txt 
	> ./report/l2_32_ijk.txt && > ./report/l2_opt_ijk.txt && > ./report/l2_32_ikj.txt && > ./report/l2_opt_ikj.txt
	> ./report/l3_32_ijk.txt && > ./report/l3_opt_ijk.txt && > ./report/l3_32_ikj.txt && > ./report/l3_opt_ikj.txt
	> ./report/tlbim_32_ijk.txt && > ./report/tlbim_opt_ijk.txt && > ./report/tlbim_32_ikj.txt && > ./report/tlbim_opt_ikj.txt
	> ./report/tlbdm_32_ijk.txt && > ./report/tlbdm_opt_ijk.txt && > ./report/tlbdm_32_ikj.txt && > ./report/tlbdm_opt_ikj.txt
	> ./report/cyc_32_ijk.txt && > ./report/cyc_opt_ijk.txt && > ./report/cyc_32_ikj.txt && > ./report/cyc_opt_ikj.txt
	> ./report/ins_32_ijk.txt && > ./report/ins_opt_ijk.txt && > ./report/ins_32_ikj.txt && > ./report/ins_opt_ikj.txt
	./report.sh 3000 3000 3000 3000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 3000 3000 3000 3000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 3000 3000 3000 3000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 3000 3000 3000 3000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 3000 3000 3000 3000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 3000 3000 3000 3000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 3000 3000 3000 3000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 3000 3000 3000 3000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 3000 3000 3000 3000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 3000 3000 3000 3000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ikj.txt ./report/l1_a1.txt ./report/l1_a2.txt ./report/l1_a3.txt 5 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ikj.txt ./report/l2_a1.txt ./report/l2_a2.txt ./report/l3_a3.txt 5 
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ikj.txt ./report/l3_a1.txt ./report/l3_a2.txt ./report/l3_a3.txt 5
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbim_a1.txt ./report/tlbim_a2.txt ./report/tlbim_a3.txt 6 
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm_a1.txt ./report/tlbdm_a2.txt ./report/tlbdm_a3.txt 6 
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ikj.txt ./report/cyc_a1.txt ./report/cyc_a2.txt ./report/cyc_a3.txt 3
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ikj.txt ./report/ins_a1.txt ./report/ins_a2.txt ./report/cyc_a3.txt 3 
	./processdat.sh ./report/report_32_ijk.txt ./report/report_32_ikj.txt ./report/report_opt_ikj.txt ./report/report_a1.txt ./report/report_a2.txt ./report/report_a3.txt 2

report4000: blocks
	$(CMPLFLAGS) generate.cpp -o generate 
	mkdir -p report
	> ./report/report_32_ijk.txt && > ./report/report_opt_ijk.txt && > ./report/report_32_ikj.txt && > ./report/report_opt_ikj.txt
	> ./report/l1_32_ijk.txt && > ./report/l1_opt_ijk.txt && > ./report/l1_32_ikj.txt && > ./report/l1_opt_ikj.txt 
	> ./report/l2_32_ijk.txt && > ./report/l2_opt_ijk.txt && > ./report/l2_32_ikj.txt && > ./report/l2_opt_ikj.txt
	> ./report/l3_32_ijk.txt && > ./report/l3_opt_ijk.txt && > ./report/l3_32_ikj.txt && > ./report/l3_opt_ikj.txt
	> ./report/tlbim_32_ijk.txt && > ./report/tlbim_opt_ijk.txt && > ./report/tlbim_32_ikj.txt && > ./report/tlbim_opt_ikj.txt
	> ./report/tlbdm_32_ijk.txt && > ./report/tlbdm_opt_ijk.txt && > ./report/tlbdm_32_ikj.txt && > ./report/tlbdm_opt_ikj.txt
	> ./report/cyc_32_ijk.txt && > ./report/cyc_opt_ijk.txt && > ./report/cyc_32_ikj.txt && > ./report/cyc_opt_ikj.txt
	> ./report/ins_32_ijk.txt && > ./report/ins_opt_ijk.txt && > ./report/ins_32_ikj.txt && > ./report/ins_opt_ikj.txt
	./report.sh 4000 4000 4000 4000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 4000 4000 4000 4000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 4000 4000 4000 4000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 4000 4000 4000 4000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 4000 4000 4000 4000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 4000 4000 4000 4000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 4000 4000 4000 4000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 4000 4000 4000 4000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 4000 4000 4000 4000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 4000 4000 4000 4000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ikj.txt ./report/l1_a1.txt ./report/l1_a2.txt ./report/l1_a3.txt 5 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ikj.txt ./report/l2_a1.txt ./report/l2_a2.txt ./report/l3_a3.txt 5 
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ikj.txt ./report/l3_a1.txt ./report/l3_a2.txt ./report/l3_a3.txt 5
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbim_a1.txt ./report/tlbim_a2.txt ./report/tlbim_a3.txt 6 
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm_a1.txt ./report/tlbdm_a2.txt ./report/tlbdm_a3.txt 6 
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ikj.txt ./report/cyc_a1.txt ./report/cyc_a2.txt ./report/cyc_a3.txt 3
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ikj.txt ./report/ins_a1.txt ./report/ins_a2.txt ./report/cyc_a3.txt 3 
	./processdat.sh ./report/report_32_ijk.txt ./report/report_32_ikj.txt ./report/report_opt_ikj.txt ./report/report_a1.txt ./report/report_a2.txt ./report/report_a3.txt 2

report5000: blocks
	$(CMPLFLAGS) generate.cpp -o generate 
	mkdir -p report
	> ./report/report_32_ijk.txt && > ./report/report_opt_ijk.txt && > ./report/report_32_ikj.txt && > ./report/report_opt_ikj.txt
	> ./report/l1_32_ijk.txt && > ./report/l1_opt_ijk.txt && > ./report/l1_32_ikj.txt && > ./report/l1_opt_ikj.txt 
	> ./report/l2_32_ijk.txt && > ./report/l2_opt_ijk.txt && > ./report/l2_32_ikj.txt && > ./report/l2_opt_ikj.txt
	> ./report/l3_32_ijk.txt && > ./report/l3_opt_ijk.txt && > ./report/l3_32_ikj.txt && > ./report/l3_opt_ikj.txt
	> ./report/tlbim_32_ijk.txt && > ./report/tlbim_opt_ijk.txt && > ./report/tlbim_32_ikj.txt && > ./report/tlbim_opt_ikj.txt
	> ./report/tlbdm_32_ijk.txt && > ./report/tlbdm_opt_ijk.txt && > ./report/tlbdm_32_ikj.txt && > ./report/tlbdm_opt_ikj.txt
	> ./report/cyc_32_ijk.txt && > ./report/cyc_opt_ijk.txt && > ./report/cyc_32_ikj.txt && > ./report/cyc_opt_ikj.txt
	> ./report/ins_32_ijk.txt && > ./report/ins_opt_ijk.txt && > ./report/ins_32_ikj.txt && > ./report/ins_opt_ikj.txt
	./report.sh 5000 5000 5000 5000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 5000 5000 5000 5000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 5000 5000 5000 5000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 5000 5000 5000 5000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 5000 5000 5000 5000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 5000 5000 5000 5000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 5000 5000 5000 5000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 5000 5000 5000 5000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 5000 5000 5000 5000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 5000 5000 5000 5000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ikj.txt ./report/l1_a1.txt ./report/l1_a2.txt ./report/l1_a3.txt 5 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ikj.txt ./report/l2_a1.txt ./report/l2_a2.txt ./report/l3_a3.txt 5 
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ikj.txt ./report/l3_a1.txt ./report/l3_a2.txt ./report/l3_a3.txt 5
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbim_a1.txt ./report/tlbim_a2.txt ./report/tlbim_a3.txt 6 
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm_a1.txt ./report/tlbdm_a2.txt ./report/tlbdm_a3.txt 6 
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ikj.txt ./report/cyc_a1.txt ./report/cyc_a2.txt ./report/cyc_a3.txt 3
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ikj.txt ./report/ins_a1.txt ./report/ins_a2.txt ./report/cyc_a3.txt 3 
	./processdat.sh ./report/report_32_ijk.txt ./report/report_32_ikj.txt ./report/report_opt_ikj.txt ./report/report_a1.txt ./report/report_a2.txt ./report/report_a3.txt 2

report: report1000 report2000 report3000 report4000 report5000
	./plot.sh ./report/l1_a1.txt ./report/l1_a2.txt ./report/l1_a3.txt L1.svg $(NAMES)
	./plot.sh ./report/l2_a1.txt ./report/l2_a2.txt ./report/l2_a3.txt L2.svg $(NAMES)
	./plot.sh ./report/l3_a1.txt ./report/l3_a2.txt ./report/l3_a3.txt L3.svg $(NAMES)
	./plot.sh ./report/tlbdm_a1.txt ./report/tlbdm_a2.txt ./report/tlbdm_a3.txt TLBDM.svg $(NAMES)
	./plot.sh ./report/tlbim_a1.txt ./report/tlbim_a2.txt ./report/tlbim_a3.txt TLBIM.svg $(NAMES)
	./plot.sh ./report/cyc_a1.txt ./report/cyc_a2.txt ./report/cyc_a3.txt CYC.svg $(NAMES)
	./plot.sh ./report/ins_a1.txt ./report/ins_a2.txt ./report/ins_a3.txt INS.svg $(NAMES)
	> ./report/l1_a1.txt && > ./report/l1_a2.txt && > ./report/l1_a3.txt && > ./report/l2_a1.txt && > ./report/l2_a2.txt && > ./report/l2_a3.txt && > ./report/l3_a1.txt && > ./report/l3_a2.txt && > ./report/l3_a3.txt 
	> ./report/tlbdm_a1.txt && > ./report/tlbdm_a2.txt && > ./report/tlbdm_a3.tx && > ./report/tlbim_a1.txt && > ./report/tlbim_a2.txt && > ./report/tlbim_a3.txt
	> ./report/cyc_a1.txt && > ./report/cyc_a2.txt && > ./report/cyc_a3.txt && > ./report/ins_a1.txt && > ./report/ins_a2.txt && > ./report/ins_a3.txt 

clean:
	rm -rf $(TARGET) *.o
	rm -rf *.txt 
	rm -rf ./test/C?.dat
	#rm -rf report || true
