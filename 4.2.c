#include <stdio.h>   //untuk printf and puts
#include <sys/socket.h>
#include <arpa/inet.h> //untuk ipv4
#include <string.h>  //untuk baca char
#include <unistd.h>
#include <stdlib.h> //untuk perror

int main(int argc, char*argv[])
{
 int socket_desc, new_socket, c;
 struct sockaddr_in server, client;
 char *message;
 char creply[4000];
 
 //Create socket
 socket_desc = socket(AF_INET, SOCK_STREAM, 0);
 if(socket_desc == -1)
 {
  printf("Could not create socket");
 }

 //Prepare the sockaddr_in structure
 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons(8888);

 //Bind
 if( bind(socket_desc,(struct sockaddr*)&server ,sizeof(server)) < 0)
 {
  puts("bind failed");
  return 1;
 }
 puts("bind successfull!  \n");

 //Listen
 listen(socket_desc,3);
 
 printf("Waiting for incoming connections...  \n");

 //Accept and incoming connection
 c = sizeof(struct sockaddr_in);

 while((new_socket = accept(socket_desc, (struct sockaddr *)&client,(socklen_t*)&c)))
 {
   printf("Connection accepted!");
   //message from client
   recv(new_socket, creply, 4000, 0);
   puts(creply);

   //reply to client
   message = "Dear client, your connection is accepted!\n";
   write(new_socket, message, strlen(message));
 }
 
 if(new_socket < 0)
 {
  perror("accept failed");
  return 1;
 }

 
 close(socket_desc); 
 return 0;
}
