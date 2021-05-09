#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 int socket_desc, new_socket, c;
 struct sockaddr_in server, client;
 char *message ;
 int optval; 
 socklen_t optlen = sizeof(optval);

 //create socket
 socket_desc = socket(AF_INET, SOCK_STREAM, 0);
 if(socket_desc == -1)
 {
  printf("Socket fail");
 }


 /* check the status for the keepalive option */
 if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0)
 {
  perror("getsocktopt()");
  close(socket_desc);
  exit(EXIT_FAILURE);
 }
 printf("SO_KEEPALIVE is %s\n", (optval ?"ON":"OFF"));
 


 /* set the option active*/
 optval = 1;
 optlen = sizeof(optval);
 if(setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen)<0)
 {
  perror("setsockopt()");
  close(socket_desc);
  exit(EXIT_FAILURE);
 }
 printf("SO_KEEPALIVE set on socket\n");

 /*check the status again*/
 if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen)< 0)
 {
  perror("getsockopt");
  close(socket_desc);
  exit(EXIT_FAILURE);
 }
 
 printf("SO_KEEPALIVE is %s\n", (optval ? "ON":"OFF"));


 //prepare the sockaddr_in structure
 server.sin_family =AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons(8888);

 //bind
 if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
 {
   puts("bind failed");
   return 1;
 }

 //Listen
 listen(socket_desc, 3);
  
 //Accept and incoming connection
  puts("waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  
  while((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
  {
    puts("Connection accepted");
   
    //reply to client
    message = "Dear client, your connection is accepted.\n";
    write(new_socket, message, strlen(message));
  }
  

  if(new_socket < 0)
  {
   perror("accept failed");
   return 1;
  } 
  
  return 0;
}
 
