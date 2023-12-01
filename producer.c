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
 void error_handler(char *message) {
    perror(message);
    exit(1);// unsucessful process termination
}
 
 int main(int argc,char *argv[])
 {
        if (argc != 2) {
        fprintf(stderr, "Usage: %s <no_of_processes>\n", argv[0]);
        exit(1);
        }
          
         int no_process=atoi(argv[1]);//atoi to convert character array to integer
         int msgqid;
        //No of process will information will be collected as argv[1] during run time
         process prc_data[no_process]; //array of struct variable
         
             for(int i=0;i<no_process;i++)
             {
             //int msgget(key_t key, int msgflg);
                 msgqid=msgget((key_t)14538,0666|IPC_CREAT); //Message Queue created using msgget system call with a given key value
         
                 if (msgqid == -1) // -1 means the message queue is not created
                 {       
                 error_handler("Error in creating queue\n");
                
                 }
                 printf("\n Process %d Data",i+1);
                 printf("\nEnter the process id :");
                 scanf("%d",&prc_data[i].pid);
                 printf("\nEnter the process priority :");
                 scanf("%d",&prc_data[i].p_priority);
                 printf("\nEnter the process Name : ");
                 scanf("%s",prc_data[i].process_name);
                 printf("\nEnter the process State : ");
                 scanf("%s",prc_data[i].process_state);
                 printf("\nEnter the memory limit in bytes : ");
                 scanf("%ld",&prc_data[i].memory_limit); 
                 
           /*      printf("\n Process id :%d,Process Prority : %d , Process Name : %s ,Process State : %s ,Memory_limit : %ld",prc_data[i].pid,prc_data[i].p_priority,prc_data[i].process_name,prc_data[i].process_state,prc_data[i].memory_limit); */
   //int msgsnd(int msgid, const void *msgp, size_t msgsz, int msgflg);
   //The total number of messages on the queue is equal to the system-imposed limit  
   //Flags specifying the message queue behavior 
   /* if msgFlag=IPC_NOWAIT, then message will not be sent if the Queue is full and the calling process will return immediately   */       
                if(msgsnd(msgqid,(void *)&prc_data[i],no_process*sizeof(process),IPC_NOWAIT)==-1) // msgsnd returns -1 if the message is not sent
                 {
                        error_handler("Msg not sent\n");
                 }
                
             } //for loop end
 }
