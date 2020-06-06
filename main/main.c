
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;
QueueHandle_t queue1;

 void task1(void *arg)
{

char txbuff[50];

queue1= xQueueCreate(5, sizeof(txbuff));

 if( queue1 == 0 )
 {
    printf("failed to create queue1= %p \n",queue1); // Failed to create the queue.

 }


sprintf(txbuff,"hello world! 1");
xQueueSend(queue1, (void*)txbuff , (TickType_t)0 );


sprintf(txbuff,"hello world! 2");
xQueueSend(queue1, (void*)txbuff , (TickType_t)0 );


sprintf(txbuff,"hello world! 3");
xQueueSendToFront(queue1, (void*)txbuff , (TickType_t)0 );

 while(1){  

   printf("data waiting to be read : %d  available spaces: %d \n",uxQueueMessagesWaiting(queue1),uxQueueSpacesAvailable(queue1));

   vTaskDelay(pdMS_TO_TICKS(1000)); }
}

 void task2(void *arg)
{
char rxbuff[50];
while(1)

  { 
//if(xQueuePeek(queue1, &(rxbuff) , (TickType_t)5 ))
if(xQueueReceive(queue1, &(rxbuff) , (TickType_t)5 ))
{ 
printf("got a data from queue!  ===  %s \n",rxbuff); }




   vTaskDelay(pdMS_TO_TICKS(1000));
   }
}

void app_main()
{

    xTaskCreate(task1, "task1", 4096, NULL, 10, &myTask1Handle);
   xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &myTask2Handle,1);
}
