#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2){
		cout << "invalid command to step 2\n";
		return 0;
	}

	string test(argv[1]);

	fstream data;
	data.open(test+".data");
	int n1, n2;
	data >> n1 >> n2;
	data.close();

	ifstream satoutput;
	satoutput.open(test + ".satoutput");
	ofstream mappingFile;
	mappingFile.open(test + ".mapping");

	string sat;
	satoutput >> sat;
	if(sat != "SAT"){
		mappingFile << "0";
		mappingFile.close();
	}

	int mapping[n1];
	int literal;
	while(satoutput)
	{
		satoutput >> literal;
		if(literal == 0) break;
		if(literal < 0) continue;
		int i = (literal - 1)/n2, j = (literal - 1)%n2;
		mapping[i] = j;
	}

	for(int i = 0; i<n1; i++){
		mappingFile << (i+1) << " " << mapping[i] + 1 << "\n";
	}

	mappingFile.close();
	return 0;
}
