#include "../include/so_utils.h"
#include <sys/stat.h>

void validar_argumentos(int argc) {
  printf("validar_argumentos: %d\n", argc);

  if(argc != 2) {
    so_error("1a", "o programa deve receber 1 argumento, ex: ./file-reader.out teste.txt");
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

FILE* abre_ficheiro_de_texto(char *file_name) {
  printf("abre_ficheiro_de_texto: %s\n", file_name);

  FILE *file = fopen(file_name, "r");
  if(file == NULL) {
    so_error("1c", "o nao foi possivel abrir o ficheiro");
    exit(1);
  }

  return file;
}

void imprimir_ficheiro_de_texto(FILE *file) {
  printf("imprimir_ficheiro_de_texto \n");

  char linha[1000];
  unsigned int numero_linha = 1;

  while(!feof(file)) {
    if(so_fgets(linha, sizeof(linha), file) != NULL) {
      printf("Li a linha: %d: %s\n", numero_linha++, linha);
    } else {
      //so_error("1d", "Ocorreu um erro na leitura do ficheiro");
    }
  }

}

void eliminar_ficheiro(char *file_name) {
  printf("eliminar_ficheiro: %s\n", file_name);

  if(remove(file_name) != 0) {
    so_error("3.4", "o nao foi possivel eliminar o ficheiro");
    exit(1);
  }
}

int main(int argc, char **argv) {
  validar_argumentos(argc);
  char *file_name = argv[1];

  validar_se_ficheiro_existe(file_name);

  // 3.3
  validar_se_e_fifo(file_name);

  FILE *file = abre_ficheiro_de_texto(file_name);
  imprimir_ficheiro_de_texto(file);

  fclose(file);

  // 3.4
  eliminar_ficheiro(file_name);

  return 0;
}