#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
  char command[256];
  char **comando;
  while (1) {
    printf("> ");
    leer_de_teclado(256, command);
    int x = strlen(command);
    if (strcmp(command,"salir") == 0) break;
    comando = de_cadena_a_vector(command);
    int rc = fork();
      assert(rc >= 0);
      if (rc == 0){
        if(command[x-1] == 38){
          for(int i=2; i >= 0; i--){
            if(i ==0){
              comando[0] = NULL;
              break;
            }
            comando[i] = comando[i-1];
          }   
          execvp(comando[1], &comando[1]);
        }else{
          execvp(comando[0], comando);
        }
      }
      else{
        if(command[x-1] != 38){
          wait(NULL);
        }
      }
  }
  return 0;
}
