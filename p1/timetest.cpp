// Andrew Kaufman & Frank Chung

#include "CPUTimer.h"
#include "StackLi.h"
#include "StackAr.h"
#include "LinkedList.h"
#include "dsexceptions.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "vector.h"
#include "SkipList.h"
#include <iostream>
#include <string>
#include <fstream>

const int MAX_SIZE = 250000;
vector<CursorNode <int> >cursorSpace(MAX_SIZE);
using namespace std;

int getChoice();
void RunList(char* filename);
void RunCursorList(char* filename);
void RunStackAr(char* filename);
void RunStackLi(char* filename);
void RunQueueAr(char* filename);
void RunSkipList(char* filename);

int main()
{
	char filename[80];
	int choice;
	CPUTimer ct;
	
	cout << "Filename >> ";
	//getline(cin,filename);
	cin >> filename;
	cout << endl;

	do
	{
		choice = getChoice();
		ct.reset();
		switch(choice)
		{
			case 1: RunList(filename);
				break;
			case 2:	RunCursorList(filename);
				break;
			case 3: RunStackAr(filename);
				break;
			case 4: RunStackLi(filename);
				break;
			case 5: RunQueueAr(filename);
				break;
			case 6: RunSkipList(filename);
				break;
			default:
				break;
		}

		cout << "CPU time: " << ct.cur_CPUTime() << endl << endl;

	}while(choice > 0);

	return 0;

}

int getChoice()
{

	int choice;	

	cout << "      ADT Menu" << endl;
	cout << "0. Quit" << endl;
	cout << "1. LinkedList" << endl;
	cout << "2. CursorList" << endl;
	cout << "3. StackAr" << endl;
	cout << "4. StackLi" << endl;
	cout << "5. QueueAr" << endl;
	cout << "6. SkipList" << endl;
	cout << "Your choice >> ";
	cin >> choice;
	
	return choice;
}

void RunList(char* filename)
{
	List<int> llist;
	ListItr<int> listItr = llist.zeroth();

	char waste[256];
	
	char command;
	ifstream infile;
	infile.open(filename);
	
	infile.getline(waste, 256);
	
	int num;
	while(infile >> command >> num)
	{		
		if(command == 'i')
		{
			llist.insert(num, listItr);
		}
		if(command == 'd')
		{
			llist.remove(num);
		}
	}

	infile.close();
	return;
}

void RunCursorList(char* filename)
{
	CursorList<int> clist(cursorSpace);
	CursorListItr<int> clistItr = clist.zeroth();

	char waste[256];
	char command;

	int num;

	ifstream infile;
	infile.open(filename);
	infile.getline(waste, 256);

	while(infile >> command >> num)
	{
		if(command == 'i')
		{
			clist.insert(num, clistItr);
		}
		if(command == 'd')
		{
			clist.remove(num);
		}
	}

	infile.close();
	return;
}

void RunStackAr(char* filename)
{
	StackAr<int> stackarr(MAX_SIZE);
	
	char waste[256];
	char command;
	int num;

	ifstream infile;
	infile.open(filename);
	infile.getline(waste, 256);

	while(infile >> command >> num)
	{
		if(command == 'i')
		{
			stackarr.push(num);
		}
		if(command == 'd')
		{
			stackarr.pop();
		}

	}

	infile.close();
	return;
}

void RunStackLi(char* filename)
{
	StackLi<int> stackl;

	char waste[256];
	char command;
	int num;

	ifstream infile;
	infile.open(filename);
	infile.getline(waste, 256);

	while(infile >> command >> num)
	{
		if(command == 'i')
		{
			stackl.push(num);
		}
		if(command == 'd')
		{
			stackl.pop();
		}
	}

	infile.close();
	return;
}

void RunQueueAr(char* filename)
{
	Queue<int> q_ar(MAX_SIZE);
	
	char waste[256];
	char command;
	int num;

	ifstream infile;
	infile.open(filename);
	infile.getline(waste, 256);

	while(infile >> command >> num)
	{
		if(command == 'i')
		{
			q_ar.enqueue(num);
		}
		if(command == 'd')
		{
			q_ar.dequeue();
		}

	}

	infile.close();
	return;
}

void RunSkipList(char* filename)
{
	SkipList<int> mylist(1,MAX_SIZE);
	
	char waste[256];
        char command;
        int num;

        ifstream infile;
        infile.open(filename);
        infile.getline(waste, 256);

        while(infile >> command >> num)
        {
                if(command == 'i')
                {
                        mylist.insert(num);
                }
                if(command == 'd')
                {
                        mylist.deleteNode(num);
                }
	}

	infile.close();
	return;
}
