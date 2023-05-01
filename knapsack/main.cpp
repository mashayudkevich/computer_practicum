#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(int capacity,char**value) {
 char*file=value[1];
 ifstream fin(file);
 ofstream data;
 data.open("data.dzn");
 long long n,W,p0,w0,i,j;
 fin>>n>>W;
 data <<"n = " <<n<< ';' <<endl;
 data <<"W = " <<W<< ';' <<endl;
 vector <long long> p(n);
 vector <long long> w(n);
 for (i=0;i<n;i++){
  fin>>p0>>w0;
  p[i]=p0;w[i]=w0;}
 data << "profit = [";
 for (i=0;i<n;i++){
  data <<p[i]<< ", ";}
 data << "];";
 data << endl;
 data << "size = [";
 for (i =0;i<n;i++){
  data <<w[i]<< ", ";}
 data << "];";
 data << endl;
 data.close();
 fin.close();
 system("minizinc --solver Gecode minizinc.mzn data.dzn");
 return 0;}
