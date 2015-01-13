#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int getMinimum() const;
  LeafNode* insert(int value); // returns pointer to new Leaf if splits
  LeafNode* splitNode(LeafNode *original, const int max);// will return LeafNode* to insert
  void print(Queue <BTreeNode*> &queue);
}; //LeafNode class

#endif
