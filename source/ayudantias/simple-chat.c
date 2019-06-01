#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "math.h"
#define IP "0.0.0.0"
#define PORT 8080

/* Función que inicializa el servidor en el port
con ip */
int initializeServer(char* ip, int port){
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	/*---- Creación del Socket. Se pasan 3 argumentos ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP en este caso) */
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configuración de la estructura del servidor ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number */
	serverAddr.sin_port = htons(port);
	/* Setear IP address como localhost */
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	/* Setear todos los bits del padding en 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*---- Bindear la struct al socket ----*/
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*---- Listen del socket, con un máximo de 5 conexiones (solo como ejemplo) ----*/
	if(listen(welcomeSocket,5)==0)
		printf("Waiting for the second user to connect...\n");
	else
		printf("Error\n");

	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	printf("Conected\n");
	return newSocket;
}

/* Función que inicializa el cliente en el port
con ip */
int initializeClient(char* ip, int port){
	int clientSocket;
  //char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Creación del Socket. Se pasan 3 argumentos ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP en este caso) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  /*---- Configuración de la estructura del servidor ----*/
	/* Address family = Internet */
  serverAddr.sin_family = AF_INET;
	/* Set port number */
  serverAddr.sin_port = htons(port);
  /* Setear IP address como localhost */
  serverAddr.sin_addr.s_addr = inet_addr(ip);
  /* Setear todos los bits del padding en 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Conectar el socket al server ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	printf("Connected to server!\n");
  /*---- Read the message from the server into the buffer ----*/
  // recv(clientSocket, buffer, 1024, 0);
  // /*---- Print the received message ----*/
  // printf("Data received: %s",buffer);
  // strcpy(buffer,"Bye World\n");
  // send(clientSocket,buffer,11,0);
	return clientSocket;
}

char* recieveMessage(int socket, char* message){
  printf("Waiting message... ♔ \n");
  recv(socket, message, 1024, 0);
  return message;
}

void sendMessage(int socket, char* message){
  send(socket, message, 1024,0);
}

int main (int argc, char *argv[])
//Elemento 1 de argv será 1 si es server o 0 si es client
{
  int socket;
  if (*argv[1]== '1'){
    printf("Server\n");
    socket = initializeServer(IP, PORT);
    int count = 0;

    while (count<10) {
      char* message = malloc(sizeof(char)*1024);
      char* msg = recieveMessage(socket, message);
      printf(msg, "%s\n");
      printf("\nYour Message: ");
      scanf("%s", msg);
      printf("\n");
      sendMessage(socket, msg);

    }
  }

  else{
    printf("Client\n");
    socket = initializeClient(IP, PORT);
    int count = 0;

    while (count<10) {
      char* message = malloc(sizeof(char)*1024);
      printf("\nYour Message: ");
      scanf("%s", message);
      printf("\n");
      sendMessage(socket, message);
      char* msg = recieveMessage(socket, message);
      printf(msg, "%s\n");

    }

  }
}
