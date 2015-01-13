// Andrew Kuafman & Frank Chung

#include <iostream> 
#include <fstream>
#include "StackLi.h"

using namespace std;


struct Token{
	int line;
	char c;
	char c2;
};

int main(int argc, char *argv[])
{

	char *filename = argv[1];
	int count = 1;				//count set to one because you start at line 1
	ifstream infile;
	infile.open(filename);

	Token t1;
	typedef Token *t_ptr;			//assign a pointer to a struct
	t_ptr ptr = &t1;
	t_ptr end;

	StackLi<t_ptr> mystack;			
	char current;
	char next;
	bool comment = false;			//comment flag
	bool done = false;			//if closing bracket without opening bracket preceding it, you are done

	while(infile.get(current))
	{
		
		if(!done)
		{
	
			switch(current)
			{
				case '/':
					if(comment)				//if part of comment, don't do anything
						break;
					infile.get(next);
					if(next == '*')
					{
						comment = true;			//set comment flag
						ptr->c = current;
						ptr->c2 = next;
						ptr->line = count;
						mystack.push(ptr);
						ptr = new Token;
					}
					break;
				case '*':	
					infile.get(next);
					if(next == '/')
					{
						end = mystack.top();
						if(end->c == '/' && end->c2 == '*')
						{
							mystack.pop();
							comment = false;		//end comment
						}
					}
					break;
				case '[':
					if(comment)			//if within comment, don't push bracket
						break;
					ptr->line = count;
					ptr->c = current;
					mystack.push(ptr);
					ptr = new Token;
					break;
				case '{':
					if(comment)
						break;			//if within comment, don't push bracket
					ptr->line = count;
					ptr->c = current;
					mystack.push(ptr);
					ptr = new Token;
					break;
				case '(':
					if(comment)			//if within comment, don't push bracket
						break;
					ptr->line = count;
					ptr->c = current;
					mystack.push(ptr);
					ptr = new Token;
					break;
				case ']':
					if(comment)			//if within comment, don't push bracket
						break;
					end = mystack.top();
					if(end->c == '[')
						mystack.pop();
					else
					{
						ptr->c = current;
						ptr->line = count;
						mystack.push(ptr);
						ptr = new Token;
						done = true;			//if no opening bracket, set flag to quit
					}
					break;
				case '}':
					if(comment)				//if part of comment don't do anything
						break;
					end = mystack.top();
					if(end->c == '{')
						mystack.pop();
					else
					{
						ptr->c = current;
						ptr->line = count;
						mystack.push(ptr);
						ptr = new Token;
						done = true;			//if no opening bracket, set flag to quit
					}
					break;
				case ')':
					if(comment)				//if part of comment, don't do anything
						break;
					end = mystack.top();
					if(end->c == '(')
						mystack.pop();
					else
					{
						ptr->c = current;
						ptr->line = count;
						mystack.push(ptr);
						ptr = new Token;
						done = true; 		//if no opening bracket, set flag to quit
					}
					break;
				case '\n':
					++count;			//increment line count when a newline character is reached
					break;
				default:
					break;
			}
		}
		
	}
	

	if(mystack.isEmpty())						//if all brackets are paired, the stack is empty
		cout << "OK" << endl;
	else								//top of the stack is the first unmatched bracket
	{
		end = mystack.top();
		cout << "Unmatched " << end->c << end->c2 << " on line #" << end->line << endl;  		
	}
	
	return 0;

}
