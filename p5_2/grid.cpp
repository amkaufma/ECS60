// Author: Sean Davis

#include "grid.h"
#include <iostream>
#define MAX 1000000000

using namespace std;

int count;              //where to insert into heap array
int currentblock = 0;       //the block we are currently working on
int edges = 0;              //keep track of how many adjacent edges we have visited
int total = 0;

Grid::Grid(int gridSize, const Block *blocks, int previous[])
{
    table = new DTable[gridSize];
    heap = new Heap[gridSize + 1];
    positions = new int[gridSize];
    makeEmpty(gridSize, blocks, previous);
    dijkstra(gridSize, blocks, previous);
} // Grid()

void Grid::dijkstra(int gridSize, const Block *blocks, int* previous)
{
    
    for(int i = 0; i < gridSize; i++)
    {
        if(table[i].visited == true)
            continue;
        else
        {
            insert(blocks, previous);
            for(int k = 0; k < count; k++)
            {
                cout << k << " " << heap[k].block << " " << heap[k].key << endl;
            }
        }
        
        deleteMin(gridSize, blocks, previous);
        
    }
    

}

void Grid::insert(const Block *blocks, int *previous)
{
    int blocktemp;
    int keytemp;


    for(int i = 0; i < (blocks[currentblock].edgeCount); i++)
    {
        total = table[currentblock].distance;
        blocktemp = blocks[currentblock].adjBlocks[i];
        keytemp = blocks[currentblock].losses[i] + total;
        
        int hole = count;
        for(; hole > 1 && keytemp < heap[hole/2].key; hole /= 2)
        {
            heap[hole].key = heap[hole/2].key;
            heap[hole].block = heap[hole/2].block;
            positions[heap[hole].block] = hole;
        }
        
        heap[hole].key = keytemp;
        heap[hole].block = blocktemp;
        positions[heap[hole].block] = hole;
        previous[blocktemp] = currentblock;
        ++count;
        
        
    }
    
}

void Grid::makeEmpty(int gridSize, const Block *blocks, int *previous)
{
    for(int j = 0; j < gridSize + 1; j++)
    {
        heap[j].key = 0;
        heap[j].block = -1;
        table[j].visited = false;
        if(j < 10)
        {
            table[j].distance = 0;
            heap[j].block = j;
            heap[j].key = 0;
            count = j;
        }
        else
        {
            table[j].distance = MAX;
        }
        positions[j] = -1;
    }
    
    for(int j = 0; j < count; j++)
    {
        cout << heap[j].block << " " << heap[j].key << endl;
    }
    
    deleteMin(gridSize, blocks, previous);
    return;
}

void Grid::deleteMin(int gridSize, const Block *blocks, int *previous)
{
    if(table[heap[0].block].visited)
    {
        heap[0].block = heap[count - 1].block;
        heap[0].key = heap[count - 1].key;
        percolatedown(gridSize, blocks);
    }
    table[heap[0].block].visited = true;
    table[heap[0].block].distance = heap[1].key;
    currentblock = heap[0].block;
    heap[0].block = heap[count - 1].block;
    heap[0].key = heap[count - 1].key;
    count -= 1;
    percolatedown(gridSize, blocks);
    return;
}

void Grid::percolatedown(int gridSize, const Block* blocks)
{
    int child;
    int hole = 1;
    int ktemp = heap[hole].key;
    int btemp = heap[hole].block;
    
    for(; hole * 2 < count; hole = child)
    {
        child = hole * 2;
        if(child != count && heap[child + 1].key < heap[child].key)
            child++;
        if(heap[child].key < ktemp)
        {
            heap[hole].key = heap[child].key;
            heap[hole].block = heap[child].block;
            positions[heap[hole].block] = hole;
        }
        else
        {
            break;
        }
    }
    
    heap[hole].key = ktemp;
    heap[hole].block = btemp;
    positions[btemp] = hole;
    
    return;
    //--count;
}