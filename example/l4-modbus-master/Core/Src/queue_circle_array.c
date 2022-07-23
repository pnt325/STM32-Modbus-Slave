#include "queue_circle_array.h"

uint8_t Queue_Initialize(struct_queue_array *queue, queue_data_type *array, uint16_t queueSize)
{
  if (queue == 0 || array == 0 || queueSize == 0)
    return RET_FALSE;

  queue->data = array;
  queue->queueSize = queueSize;
  queue->front = 0;
  queue->rear = 0;
  return RET_TRUE;
}

void Queue_MakeNull(struct_queue_array *queue)
{
  queue->front = 0;
  queue->rear = 0;
}

uint8_t Queue_IsEmpty(struct_queue_array *queue)
{
  return queue->rear == 0;
}

uint8_t Queue_IsFull(struct_queue_array *queue)
{
  return (((queue->rear + 1) - queue->front) % queue->queueSize) == 0;
}

uint8_t Queue_EnQueue(struct_queue_array *queue, queue_data_type element)
{
  if (Queue_IsFull(queue) == 0)
  {
    if (Queue_IsEmpty(queue))
      queue->front = 1;
    if (queue->rear == queue->queueSize)
      queue->rear = 1;
    else
      queue->rear++;
    *(queue->data + queue->rear - 1) = element;
    return RET_TRUE;
  }
  else
  {
    return RET_FALSE;
  }
}

queue_data_type Queue_DeQueue(struct_queue_array *queue)
{
  queue_data_type retVal;
  if (Queue_IsEmpty(queue))
  {
    return RET_FALSE;
  }
  else
  {
    retVal = *(queue->data + queue->front - 1);
    if (queue->front == queue->rear)
    {
      Queue_MakeNull(queue);
    }
    else
    {
      if (queue->front == queue->queueSize)
        queue->front = 1;
      else
        queue->front++;
    }
    return retVal;
  }
}

queue_data_type Queue_Peek(struct_queue_array *queue)
{
  queue_data_type retVal;
  if (Queue_IsEmpty(queue))
  {
    return RET_FALSE;
  }
  else
  {
    retVal = *(queue->data + queue->front - 1);
    return retVal;
  }
}

uint8_t Queue_Get(struct_queue_array *queue, queue_data_type *element)
{

  if (Queue_IsEmpty(queue))
  {
    return RET_FALSE;
  }
  else
  {
    *element = *(queue->data + queue->front - 1);
    if (queue->front == queue->rear)
    {
      Queue_MakeNull(queue);
    }
    else
    {
      if (queue->front == queue->queueSize)
        queue->front = 1;
      else
        queue->front++;
    }
    return RET_TRUE;
  }
}

uint8_t Queue_Check(struct_queue_array *queue, queue_data_type *element)
{
  if (Queue_IsEmpty(queue))
  {
    return RET_FALSE;
  }
  else
  {
    *element = *(queue->data + queue->front - 1);
    return RET_TRUE;
  }
}
//-----------------------------------------------------------------------------
uint16_t Queue_GetFill(struct_queue_array *queue)
{
  if (Queue_IsEmpty(queue))
    return 0;

  if (queue->rear >= queue->front)
  {
    return (queue->rear - queue->front + 1);
  }
  else
  {
    return (queue->queueSize - queue->front + queue->rear + 1);
  }
}
//-----------------------------------------------------------------------------
uint8_t Queue_PeekIndex(struct_queue_array *queue, queue_data_type *element, uint16_t index)
{
  // Index for data in buffer is (front+index-2)
  // Inbuffer, max index in (size - 1)

  if (index > Queue_GetFill(queue))
    return 0xFF; // Error

  if ((queue->front + index - 1) <= queue->queueSize)
    *element = *(queue->data + queue->front + index - 2);
  else
    *element = *(queue->data + queue->front + index - queue->queueSize - 2);

  return 0;
}
//-----------------------------------------------------------------------------
/*EnQueue if New Element*/
/*Return 0 if Enqueue success*/

uint8_t Queue_EnQueueNew(struct_queue_array *queue, queue_data_type element)
{
  uint16_t i = 0;
  uint16_t len = 0;
  queue_data_type temp = 0;
  uint8_t rc = 0;

  len = Queue_GetFill(queue);

  // Queue is empty, no neck to check
  if (len == 0)
  {
    Queue_EnQueue(queue, element);
    return 0;
  }
  else
  // Co phan tu trong Queue, can check
  {
    for (i = 0; i < len; i++)
    {
      rc = Queue_PeekIndex(queue, &temp, i + 1);
      if (temp == element)
      {
        return 1;
        break;
      }
    }

    if (Queue_EnQueue(queue, element) == RET_FALSE) // Queue Fulled!
    {
      return 2;
    }
    else
    {
      return 0;
    }
  }

  return 0xFF;
}
//-----------------------------------------------------------------------------
uint16_t Queue_GetToString(struct_queue_array *q, uint8_t *s)
{
  uint8_t *tempS;
  uint8_t c, ret;
  uint16_t i = 0;

  ret = 0;
  tempS = s;
  while (Queue_Get(q, &c) == 0)
  {
    tempS[i] = c;
    i++;
  }
  tempS[i] = '\0';
  return i;
}
//----------------------------------------------------------------------------
uint16_t Queue_GetRemainSize(struct_queue_array *q)
{
  if (Queue_IsEmpty(q))
    return (uint16_t)q->queueSize;
  return (q->queueSize - ((q->rear + 1 - q->front + q->queueSize) % q->queueSize));
}
