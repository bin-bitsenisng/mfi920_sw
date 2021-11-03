/************************************************************************
 | Project Name: 
 |    File Name: linked_queue.c
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

#include <stdlib.h>
#include "linked_queue.h"

void InitQueue(LINKED_QUEUE* queue, uint32_t max_len)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->len = 0;
    queue->max_len = max_len;
}

void ResetQueue(LINKED_QUEUE* queue)
{
    queue_item_t item;
    QUEUE_NODE* node_ptr = queue->front;
    QUEUE_NODE* node_ptr_temp;
    int i = 0;

    for(i = 0; i < queue->len; i++)
    {
        node_ptr_temp = node_ptr->next;
        free(node_ptr);
        node_ptr = node_ptr_temp;
    }

    queue->len = 0;
}

uint32_t GetQueueSize(LINKED_QUEUE* queue)
{
    return queue->len;
}

uint32_t IsQueueEmpty(LINKED_QUEUE* queue)
{
    return (queue->len == 0);
}

uint32_t IsQueueFull(LINKED_QUEUE* queue)
{
    return (queue->len >= queue->max_len);
}

uint32_t PutQueue(LINKED_QUEUE* queue, queue_item_t* item)
{       
    QUEUE_NODE *node = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
    node->item = *item;
    node->next = NULL;
    if (IsQueueEmpty(queue)) {
        queue->front = queue->rear = node;
    }
    else if(IsQueueFull(queue)) {
        printf("Queue is Full..\n");
        return os_retFail;
    }
    else {
        queue->rear->next = node;
        queue->rear = queue->rear->next;
    }
    queue->len++;
    return os_retOK;
}

uint32_t GetQueue(LINKED_QUEUE* queue, queue_item_t* item)
{
    if (IsQueueEmpty(queue)) {
    //    printf("Queue is Empty..\n");
        return os_retFail;
    }
    else {
        QUEUE_NODE *del_node = queue->front;
        *item = del_node->item;
        queue->len--;
        queue->front = del_node->next;
        if(queue->front == NULL)
            queue->rear = NULL;
        free(del_node);        
        return os_retOK;
    }    
}

uint32_t PeekQueue(LINKED_QUEUE* queue, queue_item_t* item)
{
    if (IsQueueEmpty(queue)) {
    //    printf("Queue is Empty..\n");
        return os_retFail;
    }
    else
    {
        *item = queue->front->item;
        return os_retOK;
    }
}

void PrintQueue(LINKED_QUEUE* queue)
{
    QUEUE_NODE* node_ptr = queue->front;
    int i = 0;
    int j = 0;

    printf("Print Queue items..\n");

    for(i = 0; i < queue->len; i++)
    {
        printf("[item %d]: ", i);
        for(j = 0; j < node_ptr->item.size; j++)
        {
            printf("%d ", node_ptr->item.buffptr[j]);
        }
        printf("\n");
        node_ptr = node_ptr->next;
    }
}