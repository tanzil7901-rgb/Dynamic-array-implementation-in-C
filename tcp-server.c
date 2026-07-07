#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
struct sockaddr_in address;
char buffer[1024];
int client;
ssize_t valread;

int main(){
  int server = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;
  setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  bind(server, (struct sockaddr *)&address, sizeof(address));

  listen(server, 1);
  printf("Server listening on port %d...\n", PORT);

  socklen_t addrlen = sizeof(address);
  if((client = accept(server, (struct sockaddr *)&address, &addrlen)) > 0){
    printf("Successfully connected to client!\n");
  }
  else{
    return 1;
  }

  while((valread = read(client, buffer, sizeof(buffer) - 1)) > 0){
    buffer[valread] = '\0';
    printf("%s", buffer);
    memset(buffer, 0, sizeof(buffer));
  }

  close(client);
  printf("Client disconnected\n"); 
  close(server);
  return 0; 
}