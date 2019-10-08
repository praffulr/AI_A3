#include <bits/stdc++.h>
using namespace std;
void edgeCondition(vector<vector<short>> &e1, vector<vector<short>> & e2, fstream * satinput);
void oneOneMap(int n1, int n2, fstream * satinput);

int main(int argc, char* argv[])
{
  fstream file;
  string input_file;
  string test(argv[1]);
  int parse;
  //read input file name
  string temp_string = ".graphs";
  input_file = argv[1]+temp_string;
  file.open(input_file);
  int n1=0, n2=0, e1=0, e2=0; //n1 -> G; n2 -> G1; n1 < n2
  //find n1 and n2
  while(file)
  {
	file>>parse;
	if(parse != 0)
	{
	  e2++;
	  if(parse>n2) n2 = parse;
	}
	else
	{
	  file>>parse;
	  if(parse == 0) break;
	}
  }
  e2 /= 2;
  while(file)
  {
	file>>parse;
	if(parse != 0)
	{
	  e1++;
	  if(parse>n1) n1 = parse;
	}
  }
  e1 /= 2;
  file.close();
  //cout << n1 << " " << n2 << " " << e1 << " " << e2 << endl;
  vector<vector<short>> E1(n1, vector<short>(n1)), E2(n2, vector<short>(n2));
  file.open(input_file);
  while(file)
  {
	file >> parse;
	if(parse != 0)
	{
	  int x = parse;
	  file >> parse;
	  E2[x-1][parse-1] = 1;
	}
	else
	{
	  file >> parse;
	  if (parse == 0)
	  {
		break;
	  }
	  else
	  {
		cout << "improper input file-E2" << endl;
	  }
	}
  }
  while(file)
  {
	file >> parse;
	int x = parse;
	if(!file) break;
	file >> parse;
	if(parse != 0)
	{
	  E1[x-1][parse-1] = 1;
	}
  }
  file.close();

	fstream data;
	data.open(test+".data");
	data << n1 << " " << n2;
	data.close();

// //checking
//   for(int i=0; i<n2; i++)
//   {
//     for(int j=0; j<n2; j++)
//       if(E2[i][j] ==1) cout <<i+1<<" "<<j+1<<endl;
//   }
//   cout <<"0 0" <<endl;
//   for(int i=0; i<n1; i++)
//   {
//     for(int j=0; j<n1; j++)
//       if(E1[i][j] ==1) cout << i+1<< " "<<j+1<<endl;
//   }

  bool M[n1][n2];
  int num_var = n1*n2;
  int num_clauses = (n1*n2*(n1+n2-2))/2 + e1*n2*(n2-1)/2 - e2*n1*(n1-1)/2 - 2*e1*e2;

  temp_string = ".satinput";
  string output_file = argv[1]+temp_string;
  file.open(output_file);
  file << "p cnf " << num_var << " " << num_clauses << endl;
  //write constraints to satinput file
  oneOneMap(n1, n2, &file);
  edgeCondition(E1, E2, &file);
  return 0;
}

void oneOneMap(int n1, int n2, fstream * satinput){
	// ofstream satinput;
	// satinput.open(test + ".satinput");

	//mij represented as i*n2 + j + 1 (where i and j starts from 0)
	//i in G is mapped to only one j in G'
	for(int i = 0; i<n1; i++){
		for(int j = 0; j < n2; j++){
			for(int k = j+1; k < n2; k++){
				*satinput << -(i*n2 + j + 1)<< " " << -(i*n2 + k + 1) << " 0\n"; 
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
				*satinput << -(i*n2 + j + 1) << " " << -(k*n2 + j + 1) << " 0\n"; 
			}
		}
	}

	//satinput.close();
}

void edgeCondition(vector<vector<short>> &e1, vector<vector<short>> & e2, fstream * satinput){
	// ofstream satinput;
	// satinput.open(test + ".satinput");

	int n1 = e1.size(), n2 = e2.size();

	for(int i = 0; i < n1; i++){
		for(int j = 0; j < n1; j++){
			if(i == j) continue;
			for(int k = 0; k < n2; k++){
				for(int l = 0; l < n2; l++){
					//if(k == l) continue;
					if((k == l) || (e1[i][j] && e2[k][l]) || (!e1[i][j] && !e2[k][l])) continue;
					
					*satinput << -(i*n2+k + 1) << " " << -(j*n2 + l + 1) << " 0\n"; 
				}
			}
		}
	}

	(*satinput).close();
}