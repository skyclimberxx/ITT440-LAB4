#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>      //inet_addr
#include <string.h>
#include <unistd.h>

int main(int argc, char*argv[])
{

 int socket_desc;
 struct sockaddr_in server;
 char *message;
 char reply[4000];

 //Create socket 
 socket_desc = socket(AF_INET, SOCK_STREAM, 0);
 if (socket_desc == -1)
 {
   printf("Could not create socket!");
 }



 server.sin_addr.s_addr = inet_addr("192.168.114.6"); //Pleaser enter your server VM
 server.sin_family = AF_INET;         //(ipv4)
 server.sin_port = htons(8888);

 //Connect to remote server 
 if (connect(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0)
 {
  puts("connect error!");
  return 1; 
 }


  puts("Connected!\n");


 //Send some data
 message = "Hi Server Skyclimberxx, saya dari client77";
 if (send(socket_desc, message, strlen(message),0) < 0)
 {
  puts("Message send is failed");
  return 1;
 }
 puts("Data Send Succescfull! \n");

 //read reply
 if (recv(socket_desc, reply, 4000, 0) < 0 )
 {
  puts("reply failed");
 }
 puts("This is server reply: \n");
 puts(reply);
 

 //close 
  close(socket_desc);

 return 0;
}


