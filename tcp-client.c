#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

struct sockaddr_in address;
char buffer[1024];

int main(int argc, char *argv[]){
  if(argc != 2){
    return 1;
  }
  int port = atoi(argv[1]);
  int client = socket(AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(port);

  if(connect(client, (struct sockaddr *)&address, sizeof(address)) == 0){
    printf("Successfully connected to server!\n");
    while(1){ 
      printf("Enter a message to send > ");
      fgets(buffer, sizeof(buffer), stdin);
      write(client, buffer, strlen(buffer));
      memset(buffer, 0, sizeof(buffer));                              
    }
  }
  else{
    return 1;
  }

  close(client);
  return 0;
}