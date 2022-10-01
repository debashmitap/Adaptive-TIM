#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <stdio.h>
// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

//for cusomer
#include <unistd.h>  //close open
#include <vector>
#include "sfmt/SFMT.h"
#include <fstream>
#include <unistd.h>
#include <string>
#include <time.h>
#include <cstdlib>


//typedef unsigned long long int;

#define ASSERT(v) {if (!(v)) {cerr<<"ASSERT FAIL @ "<<__FILE__<<":"<<__LINE__<<endl; exit(1);}}

using namespace std;

void handle_error(const char* msg) {
	perror(msg);
	exit(255);
}


void readNM(string attribute_path, int &n, int& m)
{
	ifstream cin(attribute_path);
	ASSERT(!cin == false);
	string s;
	while (cin >> s)
	{
		if (s.substr(0, 2) == "n=")
		{
			n = atoi(s.substr(2).c_str());
			continue;
		}
		if (s.substr(0, 2) == "m=")
		{
			m = atoi(s.substr(2).c_str());
			continue;
		}
		ASSERT(false);
	}	
	cin.close();
}

vector<vector<int> > readFile(string graph_file, int n, int m) {
	vector<vector<int> > in_edge(n, vector<int>());

	fstream fin;
	fin.open((graph_file).c_str(), ios::in);
	int readCnt=0;
	string tp;
	while (getline(fin, tp)) {
		stringstream s(tp);
		readCnt ++;
		int a, b;
		double p;
		s >> a >> b >> p;
		
		ASSERT( a<n );
		ASSERT( b<n );
		in_edge[b].push_back(a);
	}
	if(readCnt != m) {
		cout << "m not equal to the number of edges in file " << graph_file << endl;
		exit(1);
	}
	fin.close();

	return in_edge;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cout << "Usage: ./realization path number" << endl;
		exit(0);
	}	

	int n, m;
	

	string folder = argv[1];
	int num = atoi(argv[2]);
	// string lt_ic = argv[3];

	sfmt_t sfmtSeed;
	srand(95082);
	sfmt_init_gen_rand(&sfmtSeed, 95082);
	sfmt_genrand_uint32(&sfmtSeed)%n;

	readNM(folder+"/attribute.txt", n, m);
	// vector<vector<int> > weights(n, vector<int>(n));

	size_t length;
	string graph_file = folder+"/graph_ic.inf";
	int fd = open((graph_file).c_str(), O_RDWR);
	if (fd == -1)
		handle_error("open");
	struct stat sb;
	int rc = fstat(fd, &sb);
	if (rc == -1)
		handle_error("fstat");

	// length = sb.st_size;
	// auto ptr = static_cast<char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));  //byte by byte
	// auto f = ptr;
	

	int gap = 2 * sizeof(int)+sizeof(double);
	//ASSERT(fin != false);
	
	cout << n << endl;
	
	vector<vector<int> > in_edge = readFile(graph_file, n, m);


	//IC
	// for (int k = 0; k < num; k++)
	// {
	// 	string index = to_string(k);
	// 	string outfile = folder+"/realization_" + index;
	// 	ofstream output(outfile);

	// 	for (int i = 0; i < n; i++)
	// 	{
	// 		for (int j = 0; j < in_edge[i].size(); j++)
	// 		{
	// 			//if ((double)rand() / RAND_MAX < 1.0 / in_edge[i].size())output << in_edge[i][j] << " " << i << endl;
	// 			if (sfmt_genrand_real1(&sfmtSeed) < 1.0 / in_edge[i].size()) 
	// 			{
	// 				output << in_edge[i][j] << " " << i << endl;
	// 			}
	// 			//if ((double)rand() / RAND_MAX < probT[i][j])output << in_edge[i][j] << " " << i << endl;
	// 			//if ((double)rand() / RAND_MAX < probT[i][j])output << in_edge[i][j] << " " << i << endl;				
	// 		}
	// 	}
				
	// 	output.close();				
	// }
	
	// LT
	for (int k = 0; k < num; k++)
	{
		string index = to_string(k);
		string outfile = folder + "/realization_" + index; // + "_lt";
		ofstream output(outfile);

		for (int i = 0; i < n; i++)
		{
			// If i has no neighbors, skip it.
			if (in_edge[i].size() == 0) continue;
			// Generate random number, 0 <= index < in_edge[i].size()
			int index = sfmt_genrand_uint32(&sfmtSeed) % in_edge[i].size();
			// Select neighbor number "index" of i
			int v = in_edge[i][index];
			// Store edge from v to i
			output << v << " " << i << endl;			
		}

		output.close();
	}

	return 0;

}