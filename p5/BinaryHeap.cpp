// Author: Frank Chung and Andrew Kaufman
        #include "BinaryHeap.h"
        
        BinaryHeap::BinaryHeap(int capacity)
        {
        	array = new CostIndexObj[capacity+1];
        	currentSize = 0;
        }
        
        void BinaryHeap::insert( CostIndexObj costIndexItem )
        {
                // Percolate up
            int hole = ++currentSize;
            for( ; hole > 1 && costIndexItem.cost < array[ hole / 2 ].cost ; hole /= 2 )
                array[ hole ] = array[ hole / 2 ];
            array[ hole ] = costIndexItem;
        }

    	CostIndexObj BinaryHeap::deleteMin( )
        {
            tmp1 = array[1];
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
            return tmp1;
        }
        
        void BinaryHeap::percolateDown( int hole )
        {
/* 1*/      int child;
/* 2*/      CostIndexObj tmp = array[ hole ];

/* 3*/      for( ; hole * 2 <= currentSize; hole = child )
            {
/* 4*/          child = hole * 2;
/* 5*/          if( child != currentSize && array[child + 1].cost < array[child].cost)
/* 6*/              child++;
/* 7*/          if( array[child].cost < tmp.cost )
/* 8*/              array[hole] = array[child];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;
        }
