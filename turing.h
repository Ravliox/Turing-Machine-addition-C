#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
	long int state;
	char character;
	char move_order;
} *FTR;

void extract_banda (char* banda, char* cod_banda);
void fill_banda (char *banda);
int codify (char caracter, char* string);
int extr_index (long int numar, long int* sir);
FTR** init_matrix (FTR** matrice, int n, int m);
int apartine (long n, long* m, int nr);
void turing (FILE* f, char* banda, FTR** functie, int cursor, long stare_curenta, long* stari_finale, long* stari, int nr_stari_f, char* banda_cod);



