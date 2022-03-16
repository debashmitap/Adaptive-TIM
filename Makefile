all: tim realization bfs

tim:
	g++ src/tim.cpp -Wall -std=c++11 -O3 src/sfmt/SFMT.c  -o tim

realization:
	g++ src/realization.cpp -Wall -std=c++11 -O3 src/sfmt/SFMT.c -o realization

bfs:
	g++ src/bfs.cpp -Wall -std=c++11 -O3 -o bfs

clean:
	rm tim realization bfs