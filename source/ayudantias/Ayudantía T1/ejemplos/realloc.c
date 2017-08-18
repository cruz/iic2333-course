#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

   /* Initial memory allocation */
   char *str = malloc(15 * sizeof(char));
   strcpy(str, "Sistemas");
   printf("String = %s,  Address = %p\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, " Operativos");
   printf("String = %s,  Address = %p\n", str, str);

   free(str);

   return 0;
}
