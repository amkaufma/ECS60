// Author: Sean Davis

#include "grid.h"
#include <iostream>
#define MAX 1000000000

using namespace std;

int count = 1;              //where to insert into heap array
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
    int decreasepos;

    for(int i = 0; i <= (blocks[currentblock].edgeCount - 1); i++)
    {
        blocktemp = blocks[currentblock].adjBlocks[i];
        keytemp = blocks[currentblock].losses[i];
        if(table[blocktemp].visited)
            continue;
        else if(positions[blocktemp] == -1)
        {
            heap[count].block = blocks[currentblock].adjBlocks[i];
            heap[count].prev = currentblock;
            previous[blocks[currentblock].adjBlocks[i]] = currentblock;
            if(count == 0)
            {
                heap[count].key = blocks[currentblock].losses[i];
            }
            else
            {
                heap[count].key = blocks[currentblock].losses[i] + total;
            }
            positions[heap[count].block] = count;
            count++;
            percolateup(blocks);
        }
        else
        {   
            if(heap[blocktemp].key > keytemp)
            {
                decreasepos = positions[blocktemp];
                decreasekey(decreasepos, keytemp, blocks, previous);
            }
        }
    }
    
    /*int hole = ++count;
    for(; hole > 1 && )
    return;*/
}

void Grid::makeEmpty(int gridSize, const Block *blocks, int *previous)
{
    for(int j = 0; j < gridSize; j++)
    {
        heap[j].key = 0;
        heap[j].block = -1;
        table[j].visited = false;
        if(j < 10)
        {
            table[j].distance = 0;
            heap[j].block = j;
            heap[j].key = 0;
            count++;
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

void Grid::percolateup(const Block *blocks)
{
    //cout << count << endl;
    int loc = count - 1;        //keeps track of location in heap
    int temp, temp2;            //temporary variable if need to switch values; key, block
    if(loc == 0)                //if only one element in heap, no need to percolate down
    {
        return;
    }
    else
    {
        while(loc != 0)
        {
            if(heap[loc/2].key > heap[loc].key)
            {
                temp = heap[loc/2].key;
                temp2 = heap[loc/2].block;
                heap[loc/2].key = heap[loc].key;
                heap[loc/2].block = heap[loc].block;
                heap[loc/2] = heap[loc];
                positions[heap[loc/2].block] = loc;
                heap[loc].key = temp;
                heap[loc].block = temp2;
                positions[heap[loc].block] = loc/2;
                loc = (loc/2);  
            }
            else 
                return;
        }
    }
}

void Grid::decreasekey(int pos, int newkey, const Block *blocks, int *previous)
{
    heap[pos].key = newkey;// + heap[pos/2].key;
    previous[heap[pos].block] = currentblock;
    //heap[pos].prev = currentblock;
    percolateup(blocks);
    return;
}

void Grid::deleteMin(int gridSize, const Block *blocks, int *previous)
{
    //cout << heap[0].block << endl;
    table[heap[0].block].visited = true;
    table[heap[0].block].distance = heap[0].key;
    total = heap[0].key;
    currentblock = heap[0].block;
    //previous[heap[0].block] = heap[0].prev;
    percolatedown(gridSize, blocks);
    return;
}

void Grid::percolatedown(int gridSize, const Block* blocks)
{
    int start = 1;
    int left;// = 2 * start;
    int right;// = (2 * start) + 1;
    int min;
    int temp, temp2;
    heap[0] = heap[count - 1];
    count -= 1;
    
    while(start <= count)
    {
        left = 2 * start;
        right = (2 * start) + 1;
        if(start == 1)
        {
            if(heap[0].key > heap[left].key && heap[0].key > heap[right].key)
            {
                if(heap[left].key < heap[right].key)
                    min = left;
                else
                    min = right;
                
                temp = heap[0].key;
                temp2 = heap[0].block;
                heap[0] = heap[min];
                positions[heap[min].block] = 0;
                heap[min].key = temp;
                heap[min].block = temp2;
                positions[heap[0].block] = min;
                start = min; 

            }
            else if(heap[0].key > heap[left].key)
            {
                min = left;
                
                temp = heap[0].key;
                temp2 = heap[0].block;
                heap[0] = heap[min];
                positions[heap[min].block] = 0;
                heap[min].key = temp;
                heap[min].block = temp2;
                positions[heap[0].block] = min;
                start = min; 

            }
            else 
            {
                min = right;
                
                temp = heap[0].key;
                temp2 = heap[0].block;
                heap[0] = heap[min];
                positions[heap[min].block] = 0;
                heap[min].key = temp;
                heap[min].block = temp2;
                positions[heap[0].block] = min;
                start = min; 

            }
        }
        else
        {
            if(heap[start].key > heap[left].key && heap[start].key > heap[right].key)
            {
                if(heap[left].key < heap[right].key)
                    min = left;
                else
                    min = right;
                
                temp = heap[start].key;
                temp2 = heap[start].block;
                heap[start] = heap[min];
                positions[heap[min].block] = start;
                heap[min].key = temp;
                heap[min].block = temp2;
                positions[heap[start].block] = min;
                start = min; 

            }
            else if(heap[start].key > heap[left].key)
            {
                min = left;
                
                temp = heap[start].key;
                temp2 = heap[start].block;
                heap[start] = heap[min];
                positions[heap[min].block] = start;
                heap[min].key = temp;
                heap[min].block = temp2;
                positions[heap[start].block] = min;
                start = min; 

            }
            else 
            {
                min = right;
                
                temp = heap[start].key;
                temp2 = heap[start].block;
                heap[start] = heap[min];
                positions[heap[min].block] = start;
                heap[min].key = temp;
                heap[min].block = temp2;
                positions[heap[start].block] = min;
                start = min; 

            }
        }
    }
    
    return;
    //--count;
}