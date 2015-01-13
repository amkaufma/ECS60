#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
    
    //BTreeNode *ptr = NULL;
    int pos = count - 1;
    
    while(value <= keys[pos] && pos > 0)
    {
        --pos;
    }

    BTreeNode *ptr = children[pos]->insert(value);
    keys[pos] = children[pos]->getMinimum();
    updateKeys();
    
    if(ptr)
    {
        if(count < internalSize) //if inode's count is less than internalSize, roll right to insert new leafNode into children
        {
            for(int i = (count-1); i > pos; i--)
            {
                children[i+1] = children[i];
                keys[i+1] = children[i+1]->getMinimum(); //update the keys when rolling right
            }
            
            children[pos+1] = ptr;  //insert the new leafNode into the correct position
            keys[pos+1] = children[pos+1]->getMinimum(); //update the keys for this position
            count++;    //increment inode's count

        }
        else    //if the count is equal to internalSize, we have to pass a child to left or right before splitting
        {
            int last = count - 1;
            BTreeNode *max = ptr;
            if((children[last]->getMinimum()) > (max->getMinimum()))
            {
                max = children[last];
                for(int j = (count - 1); j > pos; j--)
                {
                    children[j+1] = children[j];
                    keys[j+1] = children[j+1]->getMinimum();
                }
                
                children[pos+1] = ptr;
                keys[pos+1]= children[pos+1]->getMinimum();  
            }
            if(leftSibling && (leftSibling->getCount()) < internalSize)
            {
                ((InternalNode*)leftSibling)->insert(children[0]);
                children[0]->setParent(((InternalNode*)leftSibling));
                parent->updateKeys();
                pos = count - 1;
                for(int j = 0; j < pos; j++)
                {
                    children[j] = children[j+1];
                    keys[j] = children[j]->getMinimum();
                }
                count--;
                insert(max);
                
                return NULL;
            }
            if(rightSibling && (rightSibling->getCount()) < internalSize)
            {
                ((InternalNode*)rightSibling)->insert(max);
                max->setParent(((InternalNode*)rightSibling));
                parent->updateKeys();
            }
            else
            {
                return splitNode(this, max);
            }
            
            
            return NULL;
        }
    }
   
    return NULL; // to avoid warnings for now.
} // InternalNode::insert()

void InternalNode::updateKeys()
{
    for(int i = 0; i < (count-1); i++)
    {
        keys[i] = children[i]->getMinimum();
    }
}

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  // students must write this
    children[0] = oldRoot;
    children[0]->setParent(this);
    children[1] = node2;
    children[1]->setParent(this);
    count = 2;
    keys[0] = children[0]->getMinimum();
    keys[1] = children[1]->getMinimum();

} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  // students may write this
    int min = newNode->getMinimum();
    int pos;
    if(count == 0)
    {
        children[0] = newNode;
        keys[0] = children[0]->getMinimum();
        count++;
    }
    else
    {
   
        for(pos = (count - 1); (keys[pos]) > min  && pos >= 0; pos--)
        {
            children[pos+1] = children[pos];
            keys[pos+1] = children[pos+1]->getMinimum();
        }
        children[pos+1] = newNode;
        keys[pos+1] = children[pos+1]->getMinimum();
        count++;
    }
    

} // InternalNode::insert()

InternalNode* InternalNode::splitNode(InternalNode *original, BTreeNode* max)
{
    InternalNode *newNode = new InternalNode(internalSize, leafSize, parent, this, rightSibling);
    if(((InternalNode*)rightSibling))
        ((InternalNode*)rightSibling)->setLeftSibling(newNode);
    ((InternalNode*)original)->setRightSibling(newNode);
    
    ((InternalNode*)newNode)->insert(max);
    int half;
    if(internalSize%2 == 0)
        half = (internalSize/2) - 1;
    if(internalSize%2 > 0)
        half = internalSize/2;
    for(int pos = (original->count) - 1; pos > half; pos--)
    {
        ((InternalNode*)newNode)->insert(original->children[pos]);
        --(original->count);
        for(int i = (count-1); i >= 0; i--)
        {
            keys[i] = children[i]->getMinimum();
        }
    }
    
    return newNode;
}

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


