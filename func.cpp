#include <bits/stdc++.h>

using namespace std;

void oneOneMap(int n1, int n2, ofstream * satinput){
	// ofstream satinput;
	// satinput.open(test + ".satinput");

	//mij represented as i*n2 + j + 1 (where i and j starts from 0)
	//i in G is mapped to only one j in G'
	for(int i = 0; i<n1; i++){
		for(int j = 0; j < n2; j++){
			for(int k = j+1; k < n2; k++){
				*satinput << i*n2 + j + 1<< " " << i*n2 + k + 1 << " 0\n"; 
			}
		}

		for(int j = 0 ; j < n2; j++){
			*satinput << i*n2 + j + 1 << " "; 
		}
		*satinput << "0\n";
	}

	//j in G' is mapped to atmax one i in G
	for(int j = 0; j<n2; j++){
		for(int i = 0; i < n1; i++){
			for(int k = i+1; k < n1; k++){
				*satinput << i*n2 + j + 1 << " " << k*n2 + j + 1 << " 0\n"; 
			}
		}
	}

	//satinput.close();
}

void edgeCondition(vector<short> &e1, vector<short> & e2, ofstream * satinput){
	// ofstream satinput;
	// satinput.open(test + ".satinput");

	int n1 = e1.size(), n2 = e2.size();

	for(int i = 0; i < n1; i++){
		for(int j = 0; j < n1; j++){
			if(i == j) continue;
			for(int k = 0; k < n2; k++){
				for(int l = 0; l < n2; l++){
					//if(k == l) continue;
					if((k == l) || (e1[i, j] && e2[k, l]) || (!e1[i, j] && !e2[k, l])) continue;
					
					*satinput << i*n2+k + 1 << " " << j*n2 + l + 1 << " 0\n"; 
				}
			}
		}
	}

	(*satinput).close();
}

void readAns(string test, int n1, int n2){
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
		int i = (literal - 1)/n2, j = (literal - 1)%n2;
		mapping[i] = j;
	}

	for(int i = 0; i<n1; i++){
		mappingFile << (i+1) << " " << mapping[i] + 1 << "\n";
	}

	mappingFile.close();	
}

