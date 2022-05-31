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
    int x = 0;
    if (strcmp(command,"salir") == 0) break;
    comando = de_cadena_a_vector(command);
    while(comando[x]){
      x++;
    }
    pid_t pid = fork();
    if (!pid){
      if(strcmp(comando[x-1], "&") == 0){
        comando[x-1] = '\x0';
        printf("%s\n", command); 
      }   
      execvp(comando[0], comando);
    }
    else{
      if(strcmp(comando[x-1], "&") == 1){
        wait(NULL);
      }
    }
  }
  return 0;
}
