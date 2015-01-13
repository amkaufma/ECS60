// Author: Frank Chung and Andrew Kaufman
        #ifndef _BINARY_HEAP_H_
        #define _BINARY_HEAP_H_

        using namespace std;
        
        struct CostIndexObj{
   	       int cost;
   		   int index;
		}; 

        class BinaryHeap
        {
          public:
            
            BinaryHeap(int capacity);
            void insert( CostIndexObj costIndexItem );
            CostIndexObj deleteMin( );
            CostIndexObj tmp1;
            int currentSize;  // Number of elements in heap
            CostIndexObj *array; 
            void percolateDown( int hole );
        };

        #include "BinaryHeap.cpp"
        #endif
