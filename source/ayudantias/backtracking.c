#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int checked(int aRow, int aCol, char * solution, int Nsol){
  for(int i=0; i<Nsol; i++){
    if (solution[i] == (6*aRow + aCol)) return 1;
  }
  return 0;
}


int backtracking(int aRow, int aCol, int fRow, int fCol, char * board, char * solution, int Nsol){ //a=actual, f=final
  // Marcar la posición actual como revisada (para no volver a ella en futuras iteraciones)
  solution[Nsol] = aRow * 6 + aCol;
  printf("We are on (%d,%d)\n", aRow, aCol);

  // Revisar si llegamos a la posición final
  if (aRow == fRow && aCol == fCol) {
    printf("LLEGAMOS!\n");
    return 1;
    }

  // Revisamos los 4 caminos, solo si no se sale del tablero, la posición siguiente es '1' y no ha sido revisada
  // Hacia arriba
  if (aRow > 0 && board[(aRow - 1) * 6 + aCol] == '1' && !checked(aRow - 1, aCol, solution, Nsol)){
    if (backtracking(aRow - 1, aCol, fRow, fCol, board, solution, Nsol + 1)) return 1;
  }

  // Hacia abajo
  if (aRow < 5 && board[(aRow + 1) * 6 + aCol] == '1' && !checked(aRow + 1, aCol, solution, Nsol)){
    if (backtracking(aRow + 1, aCol, fRow, fCol, board, solution, Nsol + 1)) return 1;
  }

  // Hacia la derecha
  if (aCol < 5 && board[aRow * 6 + aCol + 1] == '1' && !checked(aRow, aCol + 1, solution, Nsol)){
    if (backtracking(aRow, aCol + 1, fRow, fCol, board, solution, Nsol + 1)) return 1;
  }

  // Hacia la izquierda
  if (aCol > 0 && board[aRow * 6 + aCol - 1] == '1' && !checked(aRow, aCol - 1, solution, Nsol)){
    if (backtracking(aRow, aCol - 1, fRow, fCol, board, solution, Nsol + 1)) return 1;
  }

  return 0;
}

int main (int argc, char *argv[]){
  /* Definamos un tablero de 6x6
     _0_1_2_3_4_5_
  0 | 1 1 1 0 1 1  --> row 0
  1 | 0 0 1 0 1 0 
  2 | 0 1 1 1 1 1
  3 | 1 1 0 1 0 1
  4 | 1 0 0 1 0 1
  5 |*1 0 0 1 0 1*
      |
      V
     col 0
  */
  char * board = "111011001010011111110101100101100101";
  
  // Definimos un arreglo donde guardar las posiciones revisadas. (y la solución)
  char solution[36];
  
  // Definimos la posición inicial
  int initialRow = 5;
  int initialCol = 0;

  // Definimos la posición final
  int finalRow = 5;
  int finalCol = 5;

  // Hacemos el backtracking
  int ret = backtracking(initialRow, initialCol, finalRow, finalCol, board, solution, 0);
  printf("RET: %d\n", ret);

  printf("\nLa solución es:\n");
  for(int i=0;i<36;i++){
    int row = solution[i]/6; int col = solution[i]%6;
    printf("(%d,%d)\n", row, col);

    if (row == finalRow && col == finalCol) break;
  }
}
