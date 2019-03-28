#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> #include <stdlib.h> #include <math.h> #include <time.h>
struct zespolona
{
	float re, im;
};
struct element
{
	struct zespolona dane;
	struct element *poprzedni;
};
void push(struct element **gora, float re, float im)
{
	struct element *nowy;
	nowy = malloc(sizeof(struct element));
	nowy->dane.re = re;
	nowy->dane.im = im;
	nowy->poprzedni = *gora;
	*gora = nowy;
}
void pop(struct element **gora)
{
	struct element *tymczasowy;
	tymczasowy = (*gora)->poprzedni;
	free(*gora);
	*gora = tymczasowy;
}
void wyswietl(struct element **gora)
{

	struct element *tymczasowy;
	tymczasowy = *gora;
	if (pusty(&tymczasowy) != 0)
	{
		while (pusty(&tymczasowy) != 0)
		{
			
			printf("RE:%f\t", tymczasowy->dane.re);
			printf("IM:%f\t\n", tymczasowy->dane.im);
			tymczasowy = tymczasowy->poprzedni;
		}
	}
	else
	{
		printf("stos jest pusty\n");
	}
	printf("\nwprowadzaj liczby oddzielone spacja\naby wyjsc nacisnij 'w'\n aby wyczyscic stos nacisnij 'c'\n dozwolone operacje arytmetyczne: +  -  *  /\n");
}
void wyczysc(struct elementStosu **gora)
{
	while (pusty(&(*gora)) != 0)
	{
		pop(&(*gora));
	}
}
void suma(struct element **gora)
{
	struct element *jedna, *druga, *wynik;
	jedna = *gora;
	druga = (*gora)->poprzedni;
	float a, b;
	wynik = malloc(sizeof(struct element));
	a = wynik->dane.re = jedna->dane.re + druga->dane.re;
	b = wynik->dane.im = jedna->dane.im + druga->dane.im;
	pop(gora);
	pop(gora);
	push(gora, a, b);
}
void roznica(struct element **gora)
{
	struct element *jedna, *druga, *wynik;
	druga = *gora;
	jedna = (*gora)->poprzedni;
	float a, b;
	wynik = malloc(sizeof(struct element));
	a = wynik->dane.re = jedna->dane.re - druga->dane.re;
	b = wynik->dane.im = jedna->dane.im - druga->dane.im;
	pop(gora);
	pop(gora);
	push(gora, a, b);
}
void iloczyn(struct element **gora)
{
	struct element *jedna, *druga, *wynik;
	jedna = *gora;
	druga = (*gora)->poprzedni;
	float a, b;
	wynik = malloc(sizeof(struct element));
	a = wynik->dane.re = jedna->dane.re * druga->dane.re - jedna->dane.im * druga->dane.im;
	b = wynik->dane.im = jedna->dane.im * druga->dane.re + jedna->dane.re * druga->dane.im;
	pop(gora);
	pop(gora);
	push(gora, a, b);
}
void iloraz(struct element **gora)
{
	float a, b, mianownik;
	struct element *jedna, *druga, *wynik;
	jedna = *gora;
	druga = (*gora)->poprzedni;
	wynik = malloc(sizeof(struct element));
	mianownik = jedna->dane.re * jedna->dane.re + jedna->dane.im * jedna->dane.im;
	if (mianownik != 0)
	{
		a = wynik->dane.re = (jedna->dane.re * druga->dane.re + jedna->dane.im * druga->dane.im) / mianownik;
		b = wynik->dane.im = (jedna->dane.im * druga->dane.re - jedna->dane.re * druga->dane.im) / mianownik;
		pop(gora);
		pop(gora);
		push(gora, a, b);
	}
	else
	{
		printf("ERROR dzielenie przez 0\n");
	}
}
int pusty(struct element **gora)
{
	if (*gora == NULL)
			return 0;
	else
		return 1;
}

int main()
{
	printf("wprowadzaj liczby oddzielone spacja\naby wyjsc nacisnij 'w'\n aby wyczyscic stos nacisnij 'c'\n dozwolone operacje arytmetyczne: +  -  *  /\n");
	int koniec = 0;
	struct element *gora = NULL;
	float a, b;
	char tab[100];
	do
	{
			gets(&tab, stdin);
			sscanf(tab, "%f  %f", &a, &b);

		if (sscanf(tab, "%f %f", &a, &b) == 2)
		{
			push(&gora, a, b);
			system("cls");
			wyswietl(&gora);	
		}
		if (sscanf(tab, "%f %f", &a, &b) == 1)
		{
			b = 0;
			push(&gora, a, b);
			system("cls");
			wyswietl(&gora);
		}
		if (sscanf(tab, "%f %f", &a, &b) <= 0)
		{
			if (tab[0] == 'w')
			{
				wyczysc(&gora);
				koniec = 1;
				printf("wychodze z programu\n");
			}
			
			if (pusty(&gora) != 0)
			{

				if (gora->poprzedni != 0)
				
				{
					if (tab[0] == '+')
					{
						system("cls");
						suma(&gora);
						wyswietl(&gora);
					}
					if (tab[0] == '-')
					{
						system("cls");
						roznica(&gora);
						wyswietl(&gora);
					}
					if (tab[0] == '*')
					{
						system("cls");
						iloczyn(&gora);
						wyswietl(&gora);
					}
					if (tab[0] == '/')
					{
						system("cls");
						iloraz(&gora);
						wyswietl(&gora);
					}
					if (tab[0] == 'c')
					{
						wyczysc(&gora);
						printf("wyczyscilem stos\n");
					}
				}
				else
				{
					printf("wprowadz wiecej wartosci");
				}
			}
			else
			{
				printf("wprowadz wiecej wartosci");
			}
		}
	} while (koniec != 1);
system("pause");
}