TARGET=multimatrix generate print compare
CMPLFLAGS=g++ -g -O2
REPORT00=./report/l1_32_ijk.txt ./report/l2_32_ijk.txt ./report/l3_32_ijk.txt ./report/tlbim_32_ijk.txt ./report/tlbdm_32_ijk.txt ./report/cyc_32_ijk.txt ./report/ins_32_ijk.txt 
REPORT10=./report/l1_32_ikj.txt ./report/l2_32_ikj.txt ./report/l3_32_ikj.txt ./report/tlbim_32_ikj.txt ./report/tlbdm_32_ikj.txt ./report/cyc_32_ikj.txt ./report/ins_32_ikj.txt 
REPORT01=./report/l1_opt_ijk.txt ./report/l2_opt_ijk.txt ./report/l3_opt_ijk.txt ./report/tlbim_opt_ijk.txt ./report/tlbdm_opt_ijk.txt ./report/cyc_opt_ijk.txt ./report/ins_opt_ijk.txt 
REPORT11=./report/l1_opt_ikj.txt ./report/l2_opt_ikj.txt ./report/l3_opt_ikj.txt ./report/tlbim_opt_ikj.txt ./report/tlbdm_opt_ikj.txt ./report/cyc_opt_ikj.txt ./report/ins_opt_ikj.txt 
.PHONY: test report
.SILENT: all blocks generate test report1000 report2000 report3000 clean print
all: blocks compare print generate

print:
	$(CMPLFLAGS) print.cpp -o print

compare:
	$(CMPLFLAGS) compare.cpp -o compare 

blocks:
	g++ -I/usr/local/include -O0 blocks.cpp /usr/local/lib/libpapi.a -o blocks

generate: blocks
	$(CMPLFLAGS) generate.cpp -o generate
	./generate.sh 500 500 500 500 A1.dat B1.dat C01.dat 500
	./generate.sh 1000 1000 1000 1000 A2.dat B2.dat C02.dat 1000
	./generate.sh 200 200 200 200 A3.dat B3.dat C03.dat 200

test: compare blocks print
#change data in test.sh, add size of bloks 
	./test.sh ./test/A1.dat ./test/B1.dat ./test/C01.dat test1.txt
	./test.sh ./test/A2.dat ./test/B2.dat ./test/C02.dat test2.txt
	./test.sh ./test/A3.dat ./test/B3.dat ./test/C03.dat test3.txt

report1000: blocks
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
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 32 ./report/report_32_ijk.txt ./report/report_32_ikj.txt $(REPORT00) $(REPORT10)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./report.sh 1000 1000 1000 1000 0 ./report/report_opt_ijk.txt ./report/report_opt_ikj.txt $(REPORT01) $(REPORT11)
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ijk.txt ./report/l1_opt_ikj.txt ./report/l100.txt ./report/l110.txt ./report/l101.txt ./report/l111.txt 5 
	./plot.sh ./report/l100.txt ./report/l110.txt ./report/l101.txt ./report/l111.txt 1000_L1.svg "L1 32 ijk" "L1 32 ikj" "L1 opt ijk" "L1 opt ikj" 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ijk.txt ./report/l2_opt_ikj.txt ./report/l200.txt ./report/l210.txt ./report/l201.txt ./report/l211.txt 5 
	./plot.sh ./report/l200.txt ./report/l210.txt ./report/l201.txt ./report/l211.txt 1000_L2.svg "L2 32 ijk" "L2 32 ikj" "L2 opt ijk" "L2 opt ikj"
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ijk.txt ./report/l3_opt_ikj.txt ./report/l300.txt ./report/l310.txt ./report/l301.txt ./report/l311.txt 5 
	./plot.sh ./report/l300.txt ./report/l310.txt ./report/l301.txt ./report/l311.txt 1000_L3.svg "L3 32 ijk" "L3 32 ikj" "L3 opt ijk" "L3 opt ikj"
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ijk.txt ./report/tlbim_opt_ikj.txt ./report/tlbim00.txt ./report/tlbim10.txt ./report/tlbim01.txt ./report/tlbim11.txt 6 
	./plot.sh ./report/tlbim00.txt ./report/tlbim10.txt ./report/tlbim01.txt ./report/tlbim11.txt 1000_TLBIM.svg "TLBIM 32 ijk" "TLBIM 32 ikj" "TLBIM opt ijk" "TLBIM opt ikj"
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ijk.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm00.txt ./report/tlbdm10.txt ./report/tlbdm01.txt ./report/tlbdm11.txt 6 
	./plot.sh ./report/tlbdm00.txt ./report/tlbdm10.txt ./report/tlbdm01.txt ./report/tlbdm11.txt 1000_TLBDM.svg "TLBDM 32 ijk" "TLBDM 32 ikj" "TLBDM opt ijk" "TLBDM opt ikj"
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ijk.txt ./report/cyc_opt_ikj.txt ./report/cyc00.txt ./report/cyc10.txt ./report/cyc01.txt ./report/cyc11.txt 3
	./plot.sh ./report/cyc00.txt ./report/cyc10.txt ./report/cyc01.txt ./report/cyc11.txt 1000_CYC.svg "CYC 32 ijk" "CYC 32 ikj" "CYC opt ijk" "CYC opt ikj"
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ijk.txt ./report/ins_opt_ikj.txt ./report/ins00.txt ./report/ins10.txt ./report/ins01.txt ./report/ins11.txt 3 
	./plot.sh ./report/ins00.txt ./report/ins10.txt ./report/ins01.txt ./report/ins11.txt 1000_INS.svg "INS 32 ijk" "INS 32 ikj" "INS opt ijk" "INS opt ikj" 


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
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ijk.txt ./report/l1_opt_ikj.txt ./report/l100.txt ./report/l110.txt ./report/l101.txt ./report/l111.txt 5 
	./plot.sh ./report/l100.txt ./report/l110.txt ./report/l101.txt ./report/l111.txt 2000_L1.svg "L1 32 ijk" "L1 32 ikj" "L1 opt ijk" "L1 opt ikj" 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ijk.txt ./report/l2_opt_ikj.txt ./report/l200.txt ./report/l210.txt ./report/l201.txt ./report/l211.txt 5 
	./plot.sh ./report/l200.txt ./report/l210.txt ./report/l201.txt ./report/l211.txt 2000_L2.svg "L2 32 ijk" "L2 32 ikj" "L2 opt ijk" "L2 opt ikj"
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ijk.txt ./report/l3_opt_ikj.txt ./report/l300.txt ./report/l310.txt ./report/l301.txt ./report/l311.txt 5 
	./plot.sh ./report/l300.txt ./report/l310.txt ./report/l301.txt ./report/l311.txt 2000_L3.svg "L3 32 ijk" "L3 32 ikj" "L3 opt ijk" "L3 opt ikj"
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ijk.txt ./report/tlbim_opt_ikj.txt ./report/tlbim00.txt ./report/tlbim10.txt ./report/tlbim01.txt ./report/tlbim11.txt 6
	./plot.sh ./report/tlbim00.txt ./report/tlbim10.txt ./report/tlbim01.txt ./report/tlbim11.txt 2000_TLBIM.svg "TLBIM 32 ijk" "TLBIM 32 ikj" "TLBIM opt ijk" "TLBIM opt ikj"
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ijk.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm00.txt ./report/tlbdm10.txt ./report/tlbdm01.txt ./report/tlbdm11.txt 6 
	./plot.sh ./report/tlbdm00.txt ./report/tlbdm10.txt ./report/tlbdm01.txt ./report/tlbdm11.txt 2000_TLBDM.svg "TLBDM 32 ijk" "TLBDM 32 ikj" "TLBDM opt ijk" "TLBDM opt ikj"
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ijk.txt ./report/cyc_opt_ikj.txt ./report/cyc00.txt ./report/cyc10.txt ./report/cyc01.txt ./report/cyc11.txt 3
	./plot.sh ./report/cyc00.txt ./report/cyc10.txt ./report/cyc01.txt ./report/cyc11.txt 2000_CYC.svg "CYC 32 ijk" "CYC 32 ikj" "CYC opt ijk" "CYC opt ikj"
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ijk.txt ./report/ins_opt_ikj.txt ./report/ins00.txt ./report/ins10.txt ./report/ins01.txt ./report/ins11.txt 3 
	./plot.sh ./report/ins00.txt ./report/ins10.txt ./report/ins01.txt ./report/ins11.txt 2000_INS.svg "INS 32 ijk" "INS 32 ikj" "INS opt ijk" "INS opt ikj" 

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
	./processdat.sh ./report/l1_32_ijk.txt ./report/l1_32_ikj.txt ./report/l1_opt_ijk.txt ./report/l1_opt_ikj.txt ./report/l100.txt ./report/l110.txt ./report/l101.txt ./report/l111.txt 5 
	./plot.sh ./report/l100.txt ./report/l110.txt ./report/l101.txt ./report/l111.txt 3000_L1.svg "L1 32 ijk" "L1 32 ikj" "L1 opt ijk" "L1 opt ikj" 
	./processdat.sh ./report/l2_32_ijk.txt ./report/l2_32_ikj.txt ./report/l2_opt_ijk.txt ./report/l2_opt_ikj.txt ./report/l200.txt ./report/l210.txt ./report/l201.txt ./report/l211.txt 5 
	./plot.sh ./report/l200.txt ./report/l210.txt ./report/l201.txt ./report/l211.txt 3000_L2.svg "L2 32 ijk" "L2 32 ikj" "L2 opt ijk" "L2 opt ikj"
	./processdat.sh ./report/l3_32_ijk.txt ./report/l3_32_ikj.txt ./report/l3_opt_ijk.txt ./report/l3_opt_ikj.txt ./report/l300.txt ./report/l310.txt ./report/l301.txt ./report/l311.txt 5 
	./plot.sh ./report/l300.txt ./report/l310.txt ./report/l301.txt ./report/l311.txt 3000_L3.svg "L3 32 ijk" "L3 32 ikj" "L3 opt ijk" "L3 opt ikj"
	./processdat.sh ./report/tlbim_32_ijk.txt ./report/tlbim_32_ikj.txt ./report/tlbim_opt_ijk.txt ./report/tlbim_opt_ikj.txt ./report/tlbim00.txt ./report/tlbim10.txt ./report/tlbim01.txt ./report/tlbim11.txt 6
	./plot.sh ./report/tlbim00.txt ./report/tlbim10.txt ./report/tlbim01.txt ./report/tlbim11.txt 3000_TLBIM.svg "TLBIM 32 ijk" "TLBIM 32 ikj" "TLBIM opt ijk" "TLBIM opt ikj"
	./processdat.sh ./report/tlbdm_32_ijk.txt ./report/tlbdm_32_ikj.txt ./report/tlbdm_opt_ijk.txt ./report/tlbdm_opt_ikj.txt ./report/tlbdm00.txt ./report/tlbdm10.txt ./report/tlbdm01.txt ./report/tlbdm11.txt 6 
	./plot.sh ./report/tlbdm00.txt ./report/tlbdm10.txt ./report/tlbdm01.txt ./report/tlbdm11.txt 3000_TLBDM.svg "TLBDM 32 ijk" "TLBDM 32 ikj" "TLBDM opt ijk" "TLBDM opt ikj"
	./processdat.sh ./report/cyc_32_ijk.txt ./report/cyc_32_ikj.txt ./report/cyc_opt_ijk.txt ./report/cyc_opt_ikj.txt ./report/cyc00.txt ./report/cyc10.txt ./report/cyc01.txt ./report/cyc11.txt 3
	./plot.sh ./report/cyc00.txt ./report/cyc10.txt ./report/cyc01.txt ./report/cyc11.txt 3000_CYC.svg "CYC 32 ijk" "CYC 32 ikj" "CYC opt ijk" "CYC opt ikj"
	./processdat.sh ./report/ins_32_ijk.txt ./report/ins_32_ikj.txt ./report/ins_opt_ijk.txt ./report/ins_opt_ikj.txt ./report/ins00.txt ./report/ins10.txt ./report/ins01.txt ./report/ins11.txt 3 
	./plot.sh ./report/ins00.txt ./report/ins10.txt ./report/ins01.txt ./report/ins11.txt 3000_INS.svg "INS 32 ijk" "INS 32 ikj" "INS opt ijk" "INS opt ikj" 


clean:
	rm -rf $(TARGET) *.o
	rm -rf *.txt 
	rm -rf ./test/C?.dat
	rm -rf report || true
