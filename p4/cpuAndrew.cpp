// Author: Sean Davis
#include "cpu.h"
#include <iostream>
using namespace std;

unsigned tableSize = 5323;//64000/sizeof(CacheObj);


CPU::CPU()
{
    myCache = new CacheObj[tableSize];
    for(unsigned pos = 0; pos < tableSize; pos++)
    {
        myCache[pos].dirty = 'e';
    }
   
} // CPU()



enum stateofOp{ADD1, ADD2, ADD3, FINISHED};
stateofOp state;

unsigned addr1temp, pos1;
unsigned addr2temp, pos2;
unsigned addr3temp, pos3;
unsigned done = 0;



void CPU::operation(OpCode &opCode, Instruction &instruction, int &buffer)
{
  switch (opCode)
  {
    case ADD  : // *addr3 = *addr1 + *addr2
        state = ADD1;
        doAdd(opCode, instruction, buffer);
        break;
    case LOAD :  // buffer contains int requested from RAM
        doLoad(opCode, instruction, buffer);
        break;
    case STORE:  // Sent by RAM after a STORE
        doStore(opCode, instruction, buffer);
        break;
    case DONE : //  All ADDs in file have been sent.  Time to STORE dirty cache.
        state = FINISHED;
        done = 0;
        doDone(opCode, instruction, buffer);
        break;
  } // switch
} // operation()

void CPU::doAdd(OpCode &opCode, Instruction &instruction, int &buffer)
{

    
    if(state == ADD1)
    {
        addr1temp = instruction.addr1;
        addr2temp = instruction.addr2;
        addr3temp = instruction.addr3;
    
        pos1 = hash(addr1temp, tableSize);
        pos2 = hash(addr2temp, tableSize);
        pos3 = hash(addr3temp, tableSize);
        
        if(myCache[pos1].tag != addr1temp && myCache[pos1].dirty == 'd')
        {
            opCode = STORE;
            instruction.addr1 = myCache[pos1].tag;// addr1temp is not equal to the address in cache
            // ^^ should be instruction.addr1 = myCache[pos1].address
            // because the addresses were different
            buffer = myCache[pos1].value;
            return;
        }
        else if(myCache[pos1].tag == addr1temp)
        {
            
            if(myCache[pos2].tag != addr2temp && myCache[pos2].dirty == 'd')
            {
                opCode = STORE;
                instruction.addr1 = myCache[pos2].tag;
                // ^^ instruction.addr1 = myCache[pos2].address
                buffer = myCache[pos2].value;
                state = ADD2;
                return;          
            }
            else if(myCache[pos2].tag == addr2temp)
            {
                if(myCache[pos3].tag != addr3temp && myCache[pos3].dirty == 'd')
                {
                    opCode = STORE;
                    instruction.addr1 = myCache[pos3].tag;
                    // ^^ instruction.addr1 = myCache[pos3].address
                    buffer = myCache[pos3].value;
                    state = ADD3;
                    return;
                }
                else
                {
                    myCache[pos3].value = myCache[pos1].value + myCache[pos2].value;
                    myCache[pos3].tag = addr3temp;
                    myCache[pos3].dirty = 'd';
                    opCode = ADD;
                    return;
                }
            }
            else
            {
                instruction.addr1 = addr2temp;
                state = ADD2;
                opCode = LOAD;
                return;
            }
        }
        else
        {
            
            instruction.addr1 = addr1temp;
            opCode = LOAD;
            return;
        }
            

        // those changes look good i dont see anything wrong there
        
    }//ADD1
    else if(state == ADD2)
        // line 36 you do: state = ADD1 right before you call this function
        // this if statement will never be true then if im seeing it correctly
    {
        if(myCache[pos2].tag != addr2temp && myCache[pos2].dirty == 'd')
        {
            opCode = STORE;
            instruction.addr1 = addr2temp;
            buffer = myCache[pos2].value;
            return;
        }
        else if(myCache[pos2].tag == addr2temp)
        {
                if(myCache[pos3].tag != addr3temp && myCache[pos3].dirty == 'd')
                {
                    opCode = STORE;
                    instruction.addr1 = addr3temp;
                    buffer = myCache[pos3].value;
                    state = ADD3;
                    return;
                }
                else
                {
                    myCache[pos3].value = myCache[pos1].value + myCache[pos2].value;
                    myCache[pos3].tag = addr3temp;
                    myCache[pos3].dirty = 'd';
                    opCode = ADD;
                    return;
                }
        }
        else
        {
            instruction.addr1 = addr2temp;
            opCode = LOAD;
            return;
        }
    }

    else if(state == ADD3)// will never be true -Matt
    {
        if(myCache[pos3].tag != addr3temp && myCache[pos3].dirty == 'd')
        {
            opCode = STORE;
            instruction.addr1 = addr3temp;
            buffer = myCache[pos3].value;
            return;
        }
        else
        {
            myCache[pos3].value = myCache[pos1].value + myCache[pos2].value;
            myCache[pos3].dirty = 'd';
            myCache[pos3].tag = addr3temp;
            opCode = ADD;
            return;
        }
    }

}

void CPU::doLoad(OpCode& opCode, Instruction& instruction, int& buffer)
{
    if(state == ADD1)
    {
        myCache[pos1].tag = addr1temp;
        myCache[pos1].value = buffer;
        myCache[pos1].dirty = 'c';
        state = ADD2;
        doAdd(opCode, instruction, buffer);
    }
    
    else if(state == ADD2)
    {
        myCache[pos2].tag = addr2temp;
        myCache[pos2].value = buffer;
        myCache[pos2].dirty = 'c';
        state = ADD3;
        doAdd(opCode, instruction, buffer);
    }
}// this all looks good

void CPU::doStore(OpCode &opCode, Instruction &instruction, int &buffer)
{
    if(state == ADD1)
    {
        myCache[pos1].dirty = 'c';
        opCode = LOAD;
        instruction.addr1 = addr1temp;
        return;
    }
    else if(state == ADD2)
    {
        myCache[pos2].dirty = 'c';
        opCode = LOAD;
        instruction.addr1 = addr2temp;
        return;
    }
    else if(state == ADD3)
    {
        myCache[pos3].value = myCache[pos1].value + myCache[pos2].value;
        myCache[pos3].dirty = 'd';
        myCache[pos3].tag = addr3temp;
        opCode = ADD;
        return;
    }
    else if(state == FINISHED)
    {
        myCache[pos3].dirty = 'c';
        doDone(opCode, instruction, buffer);
        return;
    }
    
}// this looks good

void CPU::doDone(OpCode &opCode, Instruction &instruction, int &buffer)
{
   
    while(done < tableSize)
    {
        if(myCache[done].dirty == 'd')
        {
            opCode = STORE;
            instruction.addr1 = myCache[done].tag;
            buffer = myCache[done].value;
            done++;
            return;
        }

        done++;       
    }
    opCode = DONE;
    return;
}// looks good

unsigned CPU::hash(unsigned key, unsigned tableSize)
{
    unsigned pos;

    pos = (key % tableSize);     

    return pos;
}

