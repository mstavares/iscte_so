#include "defines.h"

int main() {
  aluno_t a;

  so_debug("\nA estrutura aluno_t tem %d bytes: \
    \n\t int numero: %d bytes \
    \n\t char nome [99]: %d bytes \
    \n\t float nota: %d bytes;", 
    sizeof(a), sizeof(a.numero), sizeof(a.nome), sizeof(a.nota)");

  return 0;
}