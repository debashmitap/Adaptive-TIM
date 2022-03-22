all: tim realization bfs

tim:
	g++ src/tim.cpp -Wall -std=c++11 -O3 src/sfmt/SFMT.c  -o tim  -arch x86_64

realization:
	g++ src/realization.cpp -Wall -std=c++11 -O3 src/sfmt/SFMT.c -o realization  -arch x86_64

bfs:
	g++ src/bfs.cpp -Wall -std=c++11 -O3 -o bfs  -arch x86_64

clean:
	rm tim realization bfs