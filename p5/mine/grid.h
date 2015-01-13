// Author: Sean Davis
#ifndef gridH
#define gridH

#include <iostream>
#include "PowerMain.h"
using namespace std;

typedef struct
{
    bool visited;
    int distance;
} DTable;

typedef struct
{
    int block;
    int key;
    int prev;
} Heap;

class Grid
{
    
public:
  Grid(int gridSize, const Block *blocks, int previous[]);
  DTable *table;
  Heap *heap;
  int *positions;
  void insert(const Block *blocks, int *previous);
  void dijkstra(int gridSize, const Block *blocks, int *previous);
  void makeEmpty(int gridSize, const Block *blocks, int *previous);
  void percolateup(const Block *blocks);
  void percolatedown(int gridSize, const Block *blocks);
  void decreasekey(int pos, int newkey, const Block *blocks, int *previous);
  void deleteMin(int gridSize, const Block *blocks, int *previous);
}; // class Grid

#endif
