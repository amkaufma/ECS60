// Author: Frank Chung and Andrew Kaufman

#include "grid.h"
#include <iostream>
#include "BinaryHeap.h"
#include <cstring>

static BinaryHeap *heap;
static CostIndexObj updateListTmp;
static CostIndexObj findMinTmp;

using namespace std;

Grid::Grid(int gridSize, const Block *blocks, int previous[]){
    
    heap = new BinaryHeap(gridSize);
    falseCount = gridSize;
    blockList = new BlockList[gridSize];
	  
    initializeblockList(gridSize);
    firstTen = 0;
    while(firstTen < 10){
        
        blockList[firstTen].totalLoss = 0;
        previous[firstTen] = firstTen;
        
        updateListTmp.index = firstTen;
        updateListTmp.cost = blockList[firstTen].totalLoss;
        heap->insert(updateListTmp);
        
        currentBlock = updateListTmp.index;
        updateBlockList(blocks,previous);
        firstTen++;
    }
    
    doMain(gridSize,blocks,previous);
    
} // Grid()

void Grid::doMain(int gridSize, const Block *blocks, int previous[]){
    
    while(falseCount){
        currentBlock = findMin(gridSize,blocks,previous);
        updateBlockList(blocks, previous);
        
    }//while()
}//doMain()

int Grid::findMin(int gridSize, const Block *blocks, int previous[]){
    
    findMinTmp = heap->deleteMin();
    return findMinTmp.index;
    
}//findMin()

void Grid::updateBlockList(const Block *blocks, int previous[]){
    
    if(blockList[currentBlock].known == true){
       return;
    }
    
    blockList[currentBlock].known = true;
    falseCount--;
    
    for(updateBlockListCount = 0;
        updateBlockListCount < blocks[currentBlock].edgeCount;
        updateBlockListCount++){    
        
        adjacentBlock = blocks[currentBlock].adjBlocks[updateBlockListCount];
        if(blockList[adjacentBlock].known == false){
            
            //if I found a shorter path
            if( (blockList[currentBlock].totalLoss + blocks[currentBlock].losses[updateBlockListCount]) <
               blockList[adjacentBlock].totalLoss){
                
                previous[adjacentBlock] = currentBlock;
                blockList[adjacentBlock].totalLoss = blockList[currentBlock].totalLoss + blocks[currentBlock].losses[updateBlockListCount];
                
                updateListTmp.index = adjacentBlock;
                updateListTmp.cost = blockList[adjacentBlock].totalLoss;
                heap->insert(updateListTmp);
                
                //how do we get rid of the old entry? do we actually need to?
                
                
            } //if less loss
            
        } // if known
        
    } //for loop UpdateBlocklistCount
    
} //UpdateBlockList()

void Grid::initializeblockList(int gridSize){
    
    for(int count = 0; count < gridSize; count++){
        blockList[count].totalLoss = 999999;
        blockList[count].known = false;
        
    }
      //memset(blockList, 0, gridSize * 8);
 //   memset(blockList.known, false, gridSize);
}//initializeblockList
