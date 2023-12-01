#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

 typedef struct process_information{
         int p_priority;
         int pid;
         char process_name[50];
         char process_state[50];
         long int memory_limit;
 }process;
 

 
int main(int argc,char *argv[])
{        
         if (argc!= 2) 
         {
          fprintf(stderr, "Usage: %s <no_of_processes>\n", argv[0]);
          exit(1);
         }
         int msgqid;
         int no_process=atoi(argv[1]);//atoi to convert character array to integer
       
         //No of process will information will be collected as argv[1] during run time
        
         process* prc_data =(process*)malloc(no_process*sizeof(process)); /*process data type pointer declaration and dynamic memory allocation */
         long msgtyp = 0;//message type 
             for(int i=0;i<no_process;i++)
             {
                 msgqid=msgget((key_t)14538,0666|IPC_CREAT); //same key value of the sender program who created message queue
         
                 if (msgqid == -1) // -1 means the message queue is not created
                 {       
                 printf("Error in creating queue\n");
                 exit(0);
                 }
        //int msgrcv(int msgid, void *msgp, size_t msgsz, long int msgtyp, int msgflg);
        //If msgtyp is equal to zero, the first message on the queue is received.      
                msgrcv(msgqid,(void *)prc_data,sizeof(process),msgtyp, MSG_NOERROR | IPC_NOWAIT);   
             
                 
                 //Using pointer
         
                printf("\n PCB %d Details",i+1);
                printf("\n Process id :%d,Process Prority : %d , Process Name : %s ,Process state : %s ,Memory Limit : %ld bytes",prc_data->pid,prc_data->p_priority,prc_data->process_name,prc_data->process_state,prc_data->memory_limit);
               prc_data++;
               }
          //msgctl(msgid,IPC_RMID,0);
 }
