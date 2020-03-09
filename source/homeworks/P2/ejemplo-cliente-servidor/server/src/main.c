#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "comunication.h"
#include "conection.h"

char * revert(char * message){
  int len = strlen(message) + 1;
  char * response = malloc(len);
  
  for (int i = 0; i < len-1; i++)
  {
    response[i] = message[len-2-i];
  }
  response[len-1] = '\0';
  return response;
}

int main(int argc, char *argv[]){
  // Se define una IP y un puerto
  char * IP = "0.0.0.0";
  int PORT = 8080;

  // Se crea el servidor y se obtienen los sockets de ambos clientes.
  PlayersInfo * players_info = prepare_sockets_and_get_clients(IP, PORT);

  // Le enviamos al primer cliente un mensaje de bienvenida
  char * welcome = "Bienvenido Cliente 1!!";
  server_send_message(players_info->socket_c1, 1, welcome);
  
  // Guardaremos los sockets en un arreglo e iremos alternando a quién escuchar.
  int sockets_array[2] = {players_info->socket_c1, players_info->socket_c2};
  int my_attention = 0;
  while (1)
  {
    // Se obtiene el paquete del cliente 1
    int msg_code = server_receive_id(sockets_array[my_attention]);

    if (msg_code == 1) //El cliente me envió un mensaje a mi (servidor)
    {
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);
      
      // Le enviaremos el mismo mensaje invertido jeje
      char * response = revert(client_message);
      
      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, response);
    }
    else if (msg_code == 2){ //El cliente le envía un mensaje al otro cliente
      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("Servidor traspasando desde %d a %d el mensaje: %s\n", my_attention+1, ((my_attention+1)%2)+1, client_message);
      
      // Mi atención cambia al otro socket
      my_attention = (my_attention + 1) % 2;
      
      server_send_message(sockets_array[my_attention], 2, client_message); 
    }
    printf("------------------\n");
  }

  return 0;
}
