#include "boggleutil.h"
#include "boggleutil.cpp"     
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[]) {
    std::string word1="a";
    std::string word2="b";
    std::string word3="c";
    std::string word4="b";
    TSTree test;
    test.insert(word1);
    test.insert(word2);
    test.insert(word3);  // string line;
    if(!test.insert(word4)) cout<<"yes"<<endl;
    if(test.find(word1)) cout<<"word1 found"<<endl;
    if(test.find(word4)) cout<<"word4 found"<<endl;
  // std::ifstream fword("boglex.txt",ios::binary);
  // while(fword.good()){
  //   std::getline(fword,line);
  //   if(!test.insert(line)){
  //   	cout<<"fail to insert "<<line<<endl;
  //   }
  // }
  // fword.close();
  // std::ifstream fword1("boglex.txt",ios::binary);
  // while(fword1.good()){
  //   std::getline(fword1,line);
  //   if(!test.isPrefix(line)){
  //   	cout<<"fail to find "<<line<<endl;
  //   }
  // }
  // fword1.close();
  return 0;
}