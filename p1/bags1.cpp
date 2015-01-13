// Andrew Kaufman & Frank Chung

#include "StackLi.h"
#include "QueueAr.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	short val;
	short end;
	
	int j = 0;
	int num = atoi(argv[2]);
	Queue<short> myQ(num);
	char *filename = argv[1];

	typedef Queue<short> *q_ptr;
	q_ptr p1 = &myQ;
	q_ptr ptr;

	StackLi<q_ptr> mystack;

	ifstream infile;
	infile.open(filename);

	
	while( infile >> val)
	{
		if(j < num)
		{
			p1->enqueue(val);
			j++;
			
		}
		else
		{	
			mystack.push(p1);
			j=0;
			p1 = new Queue<short>(num);
			p1->enqueue(val);
			j++;
			
		}
	} 	

	mystack.push(p1);
	
	while(!mystack.isEmpty())
	{
	
		ptr = mystack.top();
	
		while(!ptr->isEmpty())
		{
			end = ptr->dequeue();
			cout << end << " ";
		}
	
		mystack.pop();
	}

	cout << endl;
	return 0;
}


