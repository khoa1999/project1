compile:	
	gcc proj1.cpp -o prb1 && gcc proj12.cpp -o prb12 && gcc pr2pj1.c -o prb2 && gcc pr3pj1.c -o prb3
input2file:
	./prb1 proj1.cpp pr2pj1.c
inputmanyfile:
	./pr12 proj1.cpp proj12.cpp pr2pj1.c output.txt
