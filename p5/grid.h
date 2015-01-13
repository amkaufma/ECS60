// Author: Frank Chung and Andrew Kaufman
#ifndef gridH
#define gridH

#include <iostream>
#include "PowerMain.h"
using namespace std;

struct BlockList{
   bool known;
   int totalLoss;
};

class Grid
{

public:

  Grid(int gridSize, const Block *blocks, int previous[]);
     int falseCount;
     int currentBlock;
     BlockList *blockList;
     int firstTen;
  
  int findMin(int gridSize, const Block *blocks, int previous[]);
    int findMinValueTmp;
    int findMinIndexTmp;
    int trueCount;
    int tmpCheck;
    int listofKnownObj;
    int adjCounter;
  
  void updateBlockList(const Block *blocks, int previous[]);
     int previousIndex;
     int updateBlockListCount;
     int adjacentBlock;
     
  void initializeblockList(int gridSize); 
  void doMain(int gridSize, const Block *blocks, int previous[]);  
  
}; // class Grid



#endif
