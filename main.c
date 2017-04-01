#include "turing.h"

int main ( void ) 
{
	/*------declarari de variabile-----*/
	long int* stari;
	long int* stari_finale;
	long int stare_curenta, stare_urm, stare_initiala;	 
	char mutare, caracter1, caracter2;					
	
	int N, M, P;
	int i, k, t;										 
	int cod;
	int cursor = 1;

	FTR** functie_tranz;								

	char* banda = malloc (sizeof (char) * 1001);		

	char* linie = malloc (sizeof (char) * 8000);		

	/*-----deschidem fisierele-----*/
	FILE* banda_in = fopen ("tape.in", "r");			
	fgets (banda, 1001, banda_in);
	fclose (banda_in);
	
	char* banda_cod = malloc (200 * sizeof(char));		
	extract_banda (banda, banda_cod);

	fill_banda(banda);
	

	FILE* in = fopen ("tm.in", "r");					
	fgets (linie, 8000, in);

	/*-----citim multimea starilor-----*/
	char* p; 
	p = strtok (linie, " ");							

	N = atoi (p);
	stari = malloc (N * sizeof(long int) );				

	p = strtok (NULL, " ");

	i = 0;
	
	while (p)											
	{
		k = 0;		
		char* numar = malloc (10);						
		for ( ; p[k+1] != '\0'; k++ )
		{
			numar[k] = p[k+1];				
		}

		stari[i] = atol (numar);						 
		i++;
		p = strtok (NULL, " ");							
	}

	
	/*-----citim starile finale si numarul lor-----*/
	fgets (linie, 8000, in);

	p = strtok (linie, " ");
	P = atoi (p);										
	

	stari_finale = malloc ( sizeof(long int) * P); 		

	t = 0;											
	p = strtok (NULL, " \n");		
	
	while (p)											
	{
		char* numar = malloc (10);
		k = 0;
		for ( ; p[k+1] != '\0'; k++ )
		{
			numar[k] = p[k+1];
		}	

		stari_finale[t] = atol(numar);
		t++;

		p = strtok (NULL, " \n");
	}

	/*-----citim starea initiala-----*/
	fgets (linie, 8000, in);

	char* numar = malloc (10);
	for (k = 0; linie[k+1]!= '\n'; k++)
	{
		numar[k] = linie[k+1];
	}
	stare_curenta = atol (numar);						
														
	
	/*-----citim numarul tranzitiile si tranzitiile-----*/
	fgets (linie, 8000, in);
	p = strtok (linie, " \n");
	M = atoi (p);

	/*-----alocam memorie matricii de structuri-----*/
	functie_tranz = (FTR**) malloc ( N * sizeof (FTR **) );
	for ( i = 0; i <= N; i++ )
	{
		functie_tranz[i] = (FTR *) (malloc (200 * sizeof (FTR*) ) );
	}

	functie_tranz = init_matrix (functie_tranz, N, 200);

	
	char* banda2 = strdup(banda);						

	/*-----incepem citirea tranzitiilor din fisier-----*/
	while ( (M > 0))									
	{
		fgets (linie, 8000, in);
		
		p = strtok (linie, " ");						
		char* numar = malloc (10);
		for (k = 0; p[k+1] != '\0'; k++)
		{
			numar[k] = p[k+1];
		}

		stare_initiala = atol(numar);					

		p = strtok (NULL, " ");							
		caracter1 = p[0];

		p = strtok (NULL, " ");							
		char* numar1 = malloc (10);
		for (k = 0; p[k+1] != '\0'; k++)
		{
			numar1[k] = p[k+1];
		}
		stare_urm = atol (numar1);						

		p = strtok (NULL, " ");							
		caracter2 = p[0];

		p = strtok (NULL, " \n");						
		mutare = p[0];
		
		cod = codify (caracter1, banda_cod);			

		if (cod == -1)									
		{
			banda_cod [strlen(banda_cod)] = caracter1;
			cod = strlen(banda_cod) - 1;
		}

		/*-----completam matricea de structuri------*/
		functie_tranz[extr_index(stare_initiala, stari)][cod]->state = stare_urm;
		functie_tranz[extr_index(stare_initiala, stari)][cod]->character = caracter2;
		functie_tranz[extr_index(stare_initiala, stari)][cod]->move_order = mutare;

		M--;
	}

	/*-----apelam functia si scriem rezultatul in noul fisier-----*/
	FILE* f = fopen ("tape.out", "w");
	turing (f, banda2, functie_tranz, cursor, stare_curenta, stari_finale, stari, P, banda_cod);
	
	/*-----eliberam memoria si inchidem fisierele deschise------*/
	fclose (in);
	fclose (f);
	free (linie);
	free (banda2);
	free (banda);
	free (banda_cod);
	
	return 0;

}