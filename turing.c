#include "turing.h"


void extract_banda (char* banda, char* cod_banda)
{
	char* banda_dup;
	banda_dup = strdup (banda);

	int contor = 1;
	int i = 1;
	cod_banda[0] = '#';
	for (; contor < strlen(banda); contor++ )
	{
		if ( (banda_dup[contor] != '#') && (banda_dup[contor]!= '$') )
		{
			cod_banda[i] = banda_dup[contor];
			i++;
			int j;

			for (j = contor + 1; j < strlen (banda_dup); j++ )
			{
				if ( banda_dup[j] == banda_dup[contor] )
				{
					banda_dup[j] = '$';
				}
			} 
		}
	}
	cod_banda[strlen(cod_banda)] = '\0';

}

void fill_banda (char *banda)
{
	int i = strlen (banda) - 1;
	for (; i < 1000; i++)
	{
		banda[i] = '#';
	}

	banda[1001] = '\0';

}

int codify (char caracter, char* string)
{
	int i = 0;
	for (i = 0; i <= strlen(string); i++)
	{
		if (string[i] == caracter)
			return i;
	}
	return -1;

}

int extr_index (long int numar, long int* sir)
{
	int i = 0;
	while ( sir[i] != numar)
	{
		i++;
	}
	return i;
}

FTR** init_matrix (FTR** matrice, int n, int m)
{
	int i, j;
	for ( i = 0; i <= n; i++ )
		for ( j = 0; j <= m; j++ )
		{
			matrice[i][j] = malloc (sizeof(FTR));
			matrice[i][j]->state = -1;
			matrice[i][j]->character = '-';
			matrice[i][j]->move_order = '-';
		}
	return matrice;
}

int apartine (long n, long* m, int nr)
{
	int OK = 0;
	int i = 0;
	for (i = 0; i < nr; i++)
	{
		if (n == m[i])
		{
			OK = 1;
			return OK;
		}
	}
	return OK;
}

void turing (FILE* f, char* banda, FTR** functie, int cursor, long stare_curenta, long* stari_finale, long* stari, int nr_stari_f, char* banda_cod)
{
	
	int finish = 0;
	while ( finish == 0 )
	{
		int cod = codify (banda[cursor], banda_cod);
		

		if ( functie[extr_index(stare_curenta, stari)][cod]->state == -1)
		{
			fprintf (f, "Se agata!");
			finish = 2;
			return;
		}

		banda[cursor] = functie[extr_index(stare_curenta, stari)][cod]->character;
		if (functie[extr_index(stare_curenta, stari)][cod]->move_order == 'R')
		{
			cursor++;
		}
		else if (functie[extr_index(stare_curenta, stari)][cod]->move_order == 'L')
		{
			cursor--;
		}

		stare_curenta = functie[extr_index(stare_curenta, stari)][cod]->state;
		if ( apartine (stare_curenta, stari_finale, nr_stari_f) == 1 )
			{ finish = 1; }

	}
	fprintf (f, "%s", banda);
}