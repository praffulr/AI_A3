#include <bits/stdc++.h>
using namepsace std;

int main(int argc, char* argv[])
{
  fstream file;
  string input_file;
  int parse;
  //read input file name

  file.open(input_file);
  int n1, n2; //n1 -> G; n2 -> G1; n1 < n2
  //find n1 and n2
  
  short E1[n1][n1], E2[n2][n2];
  //initialize adjacency matrices
  for(int i=0; i<n1; i++)
  {
    for(int j=0; j<n1; j++)
      E1[i][j] = 0;
  }
  for(int i=0; i<n2; i++)
  {
    for(int j=0; j<n2; j++)
      E2[i][j] = 0;
  }

  while(file)
  {
    file >> parse;
    if(parse != 0)
    {
      int x = parse;
      file >> parse;
      E2[x][parse] = 1;
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
    if(parse != 0)
    {
      int x = parse;
      file >> parse;
      E1[x][parse] = 1;
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
        cout << "improper input file-E1" << endl;
      }
    }
  }



}
