#include "app.h"
#include "modbus.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char *get_message(int option) {
  unsigned char *message;

  switch (option) {
  case SEND_INT:
    message = send_int();
    break;

  case SEND_FLOAT:
    message = send_float();
    break;

  case SEND_STR:
    message = send_string();
    break;

  default:
    message = (unsigned char *) "";
    break;
  }
  return message;
}

void write_message(int option) {
  int message_size, pos = 0;
  unsigned char *message, *buffer;

  message = get_message(option);

  if(option >= SEND_INT && option != SEND_STR)
    message_size = 4;
  else
    message_size = strlen((char *)message);

  buffer = malloc(message_size + BUFF_MIN_SIZE);

  buffer[pos++] = option;

  if (option == SEND_STR)
    buffer[pos++] = message_size;

  memcpy(&buffer[pos], message, message_size);
  pos += message_size;

  send_modbus_message(buffer, pos);

  free(buffer);
}

void receive_message() {
  unsigned char option, *message = NULL;

  message = receive_modbus_message();
  if(message == NULL) return;

  option = message[0];

  switch (option){
  case REQUEST_INT: case SEND_INT:
    read_int(&message[1]);
    break;
  case REQUEST_FLOAT: case SEND_FLOAT:
    read_float(&message[1]);
    break;
  case REQUEST_STR: case SEND_STR:
    read_str(&message[1]);
    break;

  default:
    printf("[ERRO] Opção inválida! %d\n", option);
    break;
  }
}
