/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include "boggleplayer.cpp"
#include "boggleutil.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main (int argc, char* argv[]) {

  BogglePlayer * p = new BogglePlayer();
  set<string> lex;

  string line;
  std::ifstream fword("lex.txt",ios::binary);
  while(fword.good()){
    std::getline(fword,line);
    lex.insert(line);
  }
  fword.close();

std::ifstream f("brd.txt",ios::binary);
  int row=0;
  int col=0;
  std::getline(f,line);
  row=std::stoi(line);
  std::getline(f,line);
  col=std::stoi(line);

string brd[20][23];
  for(int i=0;i<20;i++){
    for(int j=0;j<23;j++){
      std::getline(f,line);
      brd[i][j]=line;
    }
  }
  f.close();
  string* bd[20];
  for(int i=0;i<20;i++){
    bd[i]=brd[i];
  }


  p->setBoard(20,23,bd);



  //string row0[] = {"Were"};
  // string row1[] = {"E"};
  // string row2[] = {"R"};
  //string row3[] = {"E"};
 // string* board[] = {row0};
   set<string> words;
   //set<string> words1;
   vector<int> locations;
  // p->isInLexicon("word");
  // p->isOnBoard("word");
  // p->getAllValidWords(3,&words);

  p->buildLexicon(lex);
  
 // p->setBoard(1 ,1,board);


  // if(p->isInLexicon(wordX)) {
  //   std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
  //   return -1;
  // }
  // if(!p->isInLexicon(wordA)) {
  //   std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
  //   return -1;
  // }

  // if(p->isOnBoard(wordX).size() > 0) {
  //   std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
  //   return -1;
  // }

  // locations.clear();
  // locations = p->isOnBoard(wordA);
  // if(locations.size() != 1 || locations[0] != 3) {
  //   std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
  //   return -1;
  // }

  p->getAllValidWords(2,&words);

  // p->getAllValidWords(2,&words);
  // p->getAllValidWords(2,&words);
  // if(!p->getAllValidWords(0,&words)) {
  //   std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
  //   return -1;
  // };
  // if(words.size() != 1 || words.count(wordA) != 1) {
  //   std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
  //   return -1;
  // }
  int j=0;
  
  for (std::set<string>::iterator it = words.begin() ; it != words.end(); ++it){
             j++;
            cout<<j<<" valid words "<<*it<<endl;
           }
  cout<<"total number"<<words.size()<<endl;

  int k=0;
  std::vector<int> v;
  for (std::set<string>::iterator it=lex.begin(); it!=lex.end(); ++it){
   
      v=p->isOnBoard(*it);
      if(v.size()>=2){ 
        k++;
         cout<<"find "<<k<<endl;
       }
  
}

  cout<<k<<endl;


  delete p;
  return 0;

}
