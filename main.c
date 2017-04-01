#include "turing.h"

int main ( void ) 
{
	/*------declarari de variabile-----*/
	long int* stari;
	long int* stari_finale;
	long int stare_curenta, stare_urm, stare_initiala;	//starile 
	char mutare, caracter1, caracter2;					//caracterele din comenzile de tranzitie
	
	int N, M, P;
	int i, k, t;										//variabile diverse: contoare, cursor, nr_stari etc. 
	int cod;
	int cursor = 1;

	FTR** functie_tranz;								//matricea tranzitiilor

	char* banda = malloc (sizeof (char) * 1001);		//banda masinii turing

	char* linie = malloc (sizeof (char) * 8000);		//linia citita din fisier

	/*-----deschidem fisierele-----*/
	FILE* banda_in = fopen ("tape.in", "r");			//fisierul benzii
	fgets (banda, 1001, banda_in);
	fclose (banda_in);
	
	char* banda_cod = malloc (200 * sizeof(char));		//prelucram banda: o codificam si o completam cu '#'
	extract_banda (banda, banda_cod);

	fill_banda(banda);
	

	FILE* in = fopen ("tm.in", "r");					//fisierul datelor de intrare
	fgets (linie, 8000, in);

	/*-----citim multimea starilor-----*/
	char* p; 
	p = strtok (linie, " ");							//impartim linia dupa spatii folosind strtok

	N = atoi (p);
	stari = malloc (N * sizeof(long int) );				//declaram vectorul starilor

	p = strtok (NULL, " ");

	i = 0;
	
	while (p)											//citim pana la final
	{
		k = 0;		
		char* numar = malloc (10);						//salvam numarul dupa caracter 'S' intr-un string nou
		for ( ; p[k+1] != '\0'; k++ )
		{
			numar[k] = p[k+1];				
		}

		stari[i] = atol (numar);						//il convertim la long 
		i++;
		p = strtok (NULL, " ");							//continuam citirea
	}

	
	/*-----citim starile finale si numarul lor-----*/
	fgets (linie, 8000, in);

	p = strtok (linie, " ");
	P = atoi (p);										//numarul starilor finale
	

	stari_finale = malloc ( sizeof(long int) * P); 		//alocam vectorul starilor finale

	t = 0;											
	p = strtok (NULL, " \n");		
	
	while (p)											//citim starile finale si le punem in vector
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
	stare_curenta = atol (numar);						//de la aceasta stare vom incepe deci putem considera starea curenta ca 
														//fiind starea initiala by default 
	
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

	functie_tranz = init_matrix (functie_tranz, N, 200);//initializam celulele matricii

	
	char* banda2 = strdup(banda);						//just to be safe

	/*-----incepem citirea tranzitiilor din fisier-----*/
	while ( (M > 0))									
	{
		fgets (linie, 8000, in);
		
		p = strtok (linie, " ");						//citim starea din care pornim
		char* numar = malloc (10);
		for (k = 0; p[k+1] != '\0'; k++)
		{
			numar[k] = p[k+1];
		}

		stare_initiala = atol(numar);					//convertim la long

		p = strtok (NULL, " ");							//citim caracterul pe care trebuie sa il citim
		caracter1 = p[0];

		p = strtok (NULL, " ");							//citim starea in care trebuie sa mergem
		char* numar1 = malloc (10);
		for (k = 0; p[k+1] != '\0'; k++)
		{
			numar1[k] = p[k+1];
		}
		stare_urm = atol (numar1);						//convertim la long

		p = strtok (NULL, " ");							//citim caracterul care trebuie scris
		caracter2 = p[0];

		p = strtok (NULL, " \n");						//citim mutarea
		mutare = p[0];
		
		cod = codify (caracter1, banda_cod);			//aflam pe ce coloana a matricii de structuri trebuie sa scriem 

		if (cod == -1)									//daca nu exista il adaugam in vectorul de codificari
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