#include "../include/so_utils.h"
#include <sys/stat.h>

void validar_argumentos(int argc) {
  printf("validar_argumentos: %d\n", argc);

  if(argc != 3) {
    so_error("2a", "o programa deve receber 1 argumento, ex: ./file-writer.out teste.txt");
    exit(1);
  }
}

void validar_se_ficheiro_existe(char *file_name) {
  printf("validar_se_ficheiro_existe: %s\n", file_name);

  /**
   0 -> OK
  -1 -> ERROR
  https://pubs.opengroup.org/onlinepubs/009696799/functions/stat.html
  */
  struct stat buffer;
  if(stat(file_name, &buffer) != 0) {
    so_error("1b", "o ficheiro nao existe");
    exit(1);
  }
}

void validar_se_e_fifo(char *file_name) {
  printf("validar_se_e_fifo: %s\n", file_name);

  struct stat st;
  // Valida se o ficheiro é um FIFO.
  // https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
  if (!S_ISFIFO(st.st_mode)) {
    so_error("1c", "o ficheiro existe mas não é um FIFO!");
    exit(1);
  }
}

FILE* abrir_ficheiro_de_texto(char *file_name) {
  printf("abrir_ficheiro_de_texto: %s\n", file_name);

  FILE *file = fopen(file_name, "a");
  if(file == NULL) {
    so_error("2c", "o nao foi possivel abrir o ficheiro");
    exit(1);
  }

  return file;
}

void escrever_no_ficheiro_de_texto(FILE *file, char *content) {
  printf("escrever_no_ficheiro_de_texto: %s\n", content);

  fprintf(file, "%s\n", content);
}

int main(int argc, char **argv) {
  validar_argumentos(argc);
  char *file_name = argv[1];

  validar_se_ficheiro_existe(file_name);

  // 3.4
  validar_se_e_fifo(file_name);

  FILE *file = abrir_ficheiro_de_texto(file_name);
  escrever_no_ficheiro_de_texto(file, argv[2]);
  
  fclose(file);

  return 0;
}