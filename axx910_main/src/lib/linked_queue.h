/************************************************************************
 | Project Name: 
 |    File Name: linked_queue.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.01.20  0.0   mhkim   Creation;
 |***********************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdint.h>
//#include "bts_queue.h"
#include "os.h"

typedef struct
{
    uint8_t *buffptr;
    //size_t size;
    uint32_t size;
} queue_item_t;

typedef struct queue_node QUEUE_NODE;

struct queue_node {
    queue_item_t item;
    QUEUE_NODE* next;
};

typedef struct linked_queue {
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
    uint32_t len;
    uint32_t max_len;
} LINKED_QUEUE;

void InitQueue(LINKED_QUEUE* queue, uint32_t max_len);
void ResetQueue(LINKED_QUEUE* queue);
uint32_t GetQueueSize(LINKED_QUEUE* queue);
uint32_t IsQueueEmpty(LINKED_QUEUE* queue);
uint32_t IsQueueFull(LINKED_QUEUE* queue);
uint32_t PutQueue(LINKED_QUEUE* queue, queue_item_t* item);
uint32_t GetQueue(LINKED_QUEUE* queue, queue_item_t* item);
uint32_t PeekQueue(LINKED_QUEUE* queue, queue_item_t* item);
void PrintQueue(LINKED_QUEUE* queue);

#endif