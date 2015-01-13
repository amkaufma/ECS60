// Andrew Kaufman & Frank Chung
#ifndef cpuH
#define cpuH

#include "CPURunner.h"
//#include "mynew.h"
#define MAX_PRIME 63997

typedef struct
{
    int value;
    char dirty;
    unsigned tag;    
} CacheObj;

class CPU
{
public:
    
    CacheObj *myCache;
    
    CPU();
    void operation(OpCode &opCode, Instruction &instruction, int &buffer);
    void doAdd(OpCode &opCode, Instruction &instruction, int &buffer);
    void doLoad(OpCode &opCode, Instruction &instruction, int &buffer);
    void doStore(OpCode &opCode, Instruction &instruction, int &buffer);
    void doDone(OpCode &opCode, Instruction &instruction, int &buffer);
    unsigned hash(unsigned key, unsigned tableSize);
    void makeEmpty();
};
#endif
