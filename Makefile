cc = gcc
compile:	
	$(cc) proj1.cpp -o prb1 && $(cc) proj12.cpp -o prb12 && $(cc) pr2pj1.c -o prb2 && $(cc) pr3pj1.c -o prb3 && pr2apj1.c -o prb2a
all:
	compile
input2file:
	./prb1 input_1.txt input_2.txt output.txt
inputmanyfile:
	./pr12 input_1.txt input_2.txt input_1.txt output.txt
tracing:
	strace -c ./prb1 ./prb1 input_1.txt input_2.txt input_2.txt output.txt
problem2multiprocess:
	./prb2 myfile.out
problem2singleprocess:
	./pr2a myfile.out
tree:
	./prb3
	
