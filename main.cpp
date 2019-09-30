#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[])
{
  fstream file;
  string input_file;
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

  return 0;
}
