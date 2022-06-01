#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
  char command[256];
  char **comando;
  int procesos[150];
  int procesosActivos = 0;

  while (1) {
    printf("> ");
    leer_de_teclado(256, command);
    int x = 0;
    int y = 0;
    comando = de_cadena_a_vector(command);
    if (strcmp(command,"salir") == 0) break;
    if(strcmp(command, "tareas") == 0){
      printf("%s\n", "Los procesos activos son:");
      for(int i = 0; i < procesosActivos; i++){
        if(procesos[i]){
          printf("%d\n", procesos[i]);
        }
      }
    }
    else if(strcmp(comando[0], "detener" ) == 0){
      int pidtokill = atoi(comando[1]);
      for(int i = 0; i < procesosActivos; i++){
        if(pidtokill == procesos[i]){
          kill(procesos[i], SIGKILL);
          procesos[i] = NULL;
        }
      }
    }else{
      while(comando[x]){
        x++;
      }
      pid_t pid = fork();
      if (!pid){
        if(strcmp(comando[x-1], "&") == 0){
          comando[x-1] = '\x0';
        }   
        execvp(comando[0], comando);
      }
      else{
        if(strcmp(comando[x-1], "&") == 1){
          wait(NULL);
        }else{
          procesos[procesosActivos] = (int) pid;
          procesosActivos++;
          printf("%d\n", procesosActivos);
        }
      }

    }
  }
  return 0;
}
