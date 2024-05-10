#include "defines.h"

int main() {
  aluno_t a;

  // Tamanho da estrutura é diferente devido ao padding (otimizalção)
  // https://www.youtube.com/watch?v=iDD6qk8Amlw
  so_debug("\nA estrutura aluno_t tem %d bytes: \
    \n\t int numero: %d bytes \
    \n\t char nome [99]: %d bytes \
    \n\t float nota: %d bytes;", 
    sizeof(a), sizeof(a.numero), sizeof(a.nome), sizeof(a.nota));

  return 0;
}