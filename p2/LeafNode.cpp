#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
    int pos = count - 1;
    int max;
    
    if(count < leafSize)
    {
        if(count > 0)
        {
            for(pos = (count - 1); values[pos] > value && pos >= 0; pos--)
            {
                values[pos+1] = values[pos];
            }
            values[pos+1] = value;

            count++;
            if(parent)
                parent->updateKeys();
            
        }    
        else
        {
            pos = 0;
            values[pos] = value;
          
            count++;
            if(parent)
                parent->updateKeys();
        }
        
        return NULL;
    }
    else
    {
        pos = count - 1;
        max = value;
        if(values[leafSize-1] > value)          //if the last value in the array is greater than the value being inserted 
        {                                       //max equals the last value in the array
            max = values[leafSize-1];
            for(pos = (count - 1); values[pos] > value && pos >= 0; pos--) //then roll right to insert the value
            {
                values[pos+1] = values[pos];
            }
            values[pos+1] = value;
            if(parent)
                parent->updateKeys();
        }
                                    //else, max equals the value being inserted
        
        if(leftSibling && (leftSibling->getCount()) < leafSize)     //if leftSibling exists and is not full, give to leftSibling
        {
            leftSibling->insert(values[0]);    //insert current node's minimum into leftSibling
            pos = count - 1;
            for(int j = 0; j <= pos; j++)
            {
                values[j] = values[j+1];                            //roll current node left, now that the minimum is gone
            }
            count--;
            if(parent)
                parent->updateKeys();
            insert(max);                                            //we now have room to insert max
            
            return NULL;
        }
        if(rightSibling && (rightSibling->getCount()) < leafSize)   //if rightSibling exists and is not full, give to rightSibling
        {
            rightSibling->insert(max);  //insert max into rightSibling
            if(parent)
                parent->updateKeys();
        }
        else
        {
            return splitNode(this, max);                            //if we are full and cannot give to either sibling, split
        }
    }
   
    return NULL; //no split occurs so return NULL    
}  // LeafNode::insert()

LeafNode* LeafNode::splitNode(LeafNode *original, const int max)
{
    LeafNode *newNode = new LeafNode(leafSize, parent, this, rightSibling);     //create new LeafNode, leftSibling = this, rightSibling = this->rightSibling
    if(rightSibling)                                                            //if rightSibling is not NULL, set its leftSibling to newNode
        ((LeafNode*)rightSibling)->setLeftSibling(newNode);
    original->setRightSibling(newNode);
    
    newNode->insert(max);                               //insert max into newNode
    int half;
    if(leafSize%2 == 0)
        half = (leafSize/2) - 1;
    if(leafSize%2 > 0)
        half = leafSize/2;
    for(int pos = (original->count)-1; pos > half; pos--)   //when we split, give values from left to right (right should always have more if not even split)
    {
        newNode->insert(original->values[pos]);
        --(original->count);
    }
   
    return newNode;                                      //return pointer to new LeafNode
}

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
 
} // LeafNode::print()


