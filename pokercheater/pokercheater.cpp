/* poker.cpp : Defines the entry point for the console application.

Program symuluj¹cy grê w pokera i obliczaj¹cy prawdopodobieñstwo uzyskania
wy¿szego uk³adu w kartach (widzi karty innych graczy i na tej podstawie oblicza prawdopodobieñstwo).

Jest to klasyczny "podwórkowy" poker. Ka¿dy z graczy otrzymuje piêæ kart, wtedy jest obliczane prawdopodobieñstwo
otrzymaniainnych uk³adów z kart, nastêpnie wymiana maksymalnie 4 kart przez ka¿dego z graczy, który chce wymieniæ i prezentacja wyników.

Poniewa¿ dla 4 graczy wydawane jest 20 kart (po 5), ka¿dy z nich mo¿e wymieniæ 4 karty, czyli razem 16, aby nie zabrak³o kart dla graczy,
co pi¹ty gracz dok³adana jest kolejna talia kart.

Obliczane prawdopodobieñstwo bêdzie tylko w przypadku gdy gracz ma w kartach:
- jedn¹ parê,
- dwie pary,
- trójkê,
- brak uk³adu.

Przyjêto za³o¿enie, ¿e uk³ady takie jak strit, full, kareta, kolor i poker s¹ ju¿ wysokimi uk³adami, które zda¿aj¹ siê dosyæ rzadko,
dlatego te¿ nie jest obliczane prawdopodobieñstwo uzyskania wy¿szych uk³adów. W przypadku posiadania tych uk³adów gracz ma bardzo du¿¹ szansê 
na wygranie danej rozgrywki.

*/

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;

int talia[1040];
int IloscGraczy;
int gracz[400];
int gracz1[40];
int gracz2[5];
long long int wyniki[2][20];
int resztki[17];

void StworzTalie()
{
	int i, j;
	j = 0;
	for (i = 0; i < 52 * ((IloscGraczy+3)/4); i++)
	{
		talia[i] = j;
		j++;
		if (j > 51) j = 0;
		
	}
	cout << "talia zostala stworzona\n";
}

void RozdajKarty()
{
	for (int i = 0; i < (IloscGraczy * 5); i++)
	{
		int X = (rand() % (52 * ((IloscGraczy + 3) / 4)));

		while (talia[X] > 51)
			{
			X = X - 52; 
			};
		while (talia[X]==99) X++;
		gracz[i] = talia[X];
		talia[X] = 99;
		}
}

void SortujKarty()
{
	int i, j, tmp;

	int k;
	for (k = 0; k < IloscGraczy; k++)
	{
		for (i = 0; i <= 3; i++)
		{

			for (j = 0; j <= 3; j++)
			if (gracz[j + 5 * k] > gracz[j + 1 + 5 * k])
			{
				tmp = gracz[j + 5 * k];
				gracz[j + 5 * k] = gracz[j + 1 + 5 * k];
				gracz[j + 1 + 5 * k] = tmp;
			}
		}
		cout << endl;
	}
	cout << "\n";
}

void SprawdzJednaKarte(int jednakarta)
{
	{
		int kolor = (jednakarta % 4);
		int figura = (jednakarta / 4);

		switch (figura + 2)
		{
		case 2:
			cout << " 2 ";
			break;
		case 3:
			cout << " 3 ";
			break;
		case 4:
			cout << " 4 ";
			break;
		case 5:
			cout << " 5 ";
			break;
		case 6:
			cout << " 6 ";
			break;
		case 7:
			cout << " 7 ";
			break;
		case 8:
			cout << " 8 ";
			break;
		case 9:
			cout << " 9 ";
			break;
		case 10:
			cout << "10 ";
			break;
		case 11:
			cout << " J ";
			break;
		case 12:
			cout << " Q ";
			break;
		case 13:
			cout << " K ";
			break;
		case 14:
			cout << "AS ";
			break;
		default: break;
		}
		switch (kolor)
		{
		case 0:
			cout << "pik, ";
			break;
		case 1:
			cout << "trefl, ";
			break;
		case 2:
			cout << "kier, ";
			break;
		case 3:
			cout << "karo, ";
			break;
		default: break;
		}

		cout << endl;
	}
}

void SprawdzKarte(int player, int wersja)
{
	int i;

	for (i = 0; i <= 4; i++)
	{
		int kolor = (gracz[i + player * 5] % 4);
		int figura = (gracz[i + player * 5] / 4);

		if (wersja == 0)
		{
			cout << "gracz " << player + 1 << " :";
		}
		if (wersja == 1)
		{
			cout << i + 1 << ": ";
		}

		switch (figura + 2)
		{
		case 2:
			cout << " 2 ";
			break;
		case 3:
			cout << " 3 ";
			break;
		case 4:
			cout << " 4 ";
			break;
		case 5:
			cout << " 5 ";
			break;
		case 6:
			cout << " 6 ";
			break;
		case 7:
			cout << " 7 ";
			break;
		case 8:
			cout << " 8 ";
			break;
		case 9:
			cout << " 9 ";
			break;
		case 10:
			cout << "10 ";
			break;
		case 11:
			cout << " J ";
			break;
		case 12:
			cout << " Q ";
			break;
		case 13:
			cout << " K ";
			break;
		case 14:
			cout << "AS ";
			break;
		default: break;
		}
		switch (kolor)
		{
		case 0:
			cout << "pik, ";
			break;
		case 1:
			cout << "trefl, ";
			break;
		case 2:
			cout << "kier, ";
			break;
		case 3:
			cout << "karo, ";
			break;
		default: break;
		}

		cout << endl;
	}
}

int SprawdzUkladPrzed(int player) 
{
	bool czypara1 = false;
	bool czypara2 = false;
	bool czytrojka = false;
	bool czyfull = false;
	bool czykareta = false;
	bool czykolor = false;
	bool czypoker = false;
	bool czystrit = false;
	
	if //sprawdzenie kareta
		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4))
		||
		((gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		czykareta = true;
		cout << "\n gracz " << player + 1 << " ma karete";
		switch ((gracz[(player * 5) + 1] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0200000;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0300000;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0400000;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0500000;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0600000;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0700000;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0800000;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0900000;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x0A00000;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x0B00000;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x0C00000;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x0D00000;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x0E00000;
			break;
		default: break;
		}
		return 0;
	}

	if //sprawdz full'a :)
		(((gracz[(player * 5)] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)) ||
		((gracz[(player * 5)] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		czyfull = true;
		cout << "\n gracz " << player + 1 << " ma full'a";
		wyniki[0][player] += 0x0010000;

	}
	
	if //sprawdz trojke
		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))
		||
		((gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4))
		||
		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		czytrojka = true;

		if ((czyfull == false) && (czykareta == false)) 
		{
			cout << "\n gracz " << player + 1 << " ma trojke";
			switch ((gracz[(player * 5) + 2] / 4) + 2)
			{
			case 2:
				cout << " 2 ";
				wyniki[0][player] += 0x0000200;
				break;
			case 3:
				cout << " 3 ";
				wyniki[0][player] += 0x0000300;
				break;
			case 4:
				cout << " 4 ";
				wyniki[0][player] += 0x0000400;
				break;
			case 5:
				cout << " 5 ";
				wyniki[0][player] += 0x0000500;
				break;
			case 6:
				cout << " 6 ";
				wyniki[0][player] += 0x0000600;
				break;
			case 7:
				cout << " 7 ";
				wyniki[0][player] += 0x0000700;
				break;
			case 8:
				cout << " 8 ";
				wyniki[0][player] += 0x0000800;
				break;
			case 9:
				cout << " 9 ";
				wyniki[0][player] += 0x0000900;
				break;
			case 10:
				cout << "10 ";
				wyniki[0][player] += 0x0000A00;
				break;
			case 11:
				cout << " J ";
				wyniki[0][player] += 0x0000B00;
				break;
			case 12:
				cout << " Q ";
				wyniki[0][player] += 0x0000C00;
				break;
			case 13:
				cout << " K ";
				wyniki[0][player] += 0x0000D00;
				break;
			case 14:
				cout << "AS ";
				wyniki[0][player] += 0x0000E00;
				break;
			default: break;
			}
		}	
	}
	
	if //sprawdz pierwsza pare (na pierwszych trzech kartach, ni¿szych)
		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) ||
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4)))
	{
		if ((czytrojka == false) && (czykareta == false)){
			czypara1 = true;
			switch ((gracz[(player * 5) + 1] / 4) + 2)
			{
			case 2:
				cout << " 2 ";
				wyniki[0][player] += 0x0000020;
				break;
			case 3:
				cout << " 3 ";
				wyniki[0][player] += 0x0000030;
				break;
			case 4:
				cout << " 4 ";
				wyniki[0][player] += 0x0000040;
				break;
			case 5:
				cout << " 5 ";
				wyniki[0][player] += 0x0000050;
				break;
			case 6:
				cout << " 6 ";
				wyniki[0][player] += 0x0000060;
				break;
			case 7:
				cout << " 7 ";
				wyniki[0][player] += 0x0000070;
				break;
			case 8:
				cout << " 8 ";
				wyniki[0][player] += 0x0000080;
				break;
			case 9:
				cout << " 9 ";
				wyniki[0][player] += 0x0000090;
				break;
			case 10:
				cout << "10 ";
				wyniki[0][player] += 0x00000A0;
				break;
			case 11:
				cout << " J ";
				wyniki[0][player] += 0x00000B0;
				break;
			case 12:
				cout << " Q ";
				wyniki[0][player] += 0x00000C0;
				break;
			case 13:
				cout << " K ";
				wyniki[0][player] += 0x00000D0;
				break;
			case 14:
				cout << "AS ";
				wyniki[0][player] += 0x00000E0;
				break;
			default: break;
			}
		}
	}
	
	if //sprawdz druga pare (na kolejnych trzech kartach, wy¿szych)
		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) ||
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4))
	{
		if ((czytrojka == false) && (czykareta == false)){
			czypara2 = true;
			switch ((gracz[(player * 5) + 3] / 4) + 2)
			{
			case 2:
				cout << " 2 ";
				wyniki[0][player] += 0x0000002;
				break;
			case 3:
				cout << " 3 ";
				wyniki[0][player] += 0x0000003;
				break;
			case 4:
				cout << " 4 ";
				wyniki[0][player] += 0x0000004;
				break;
			case 5:
				cout << " 5 ";
				wyniki[0][player] += 0x0000005;
				break;
			case 6:
				cout << " 6 ";
				wyniki[0][player] += 0x0000006;
				break;
			case 7:
				cout << " 7 ";
				wyniki[0][player] += 0x0000007;
				break;
			case 8:
				cout << " 8 ";
				wyniki[0][player] += 0x0000008;
				break;
			case 9:
				cout << " 9 ";
				wyniki[0][player] += 0x0000009;
				break;
			case 10:
				cout << "10 ";
				wyniki[0][player] += 0x000000A;
				break;
			case 11:
				cout << " J ";
				wyniki[0][player] += 0x000000B;
				break;
			case 12:
				cout << " Q ";
				wyniki[0][player] += 0x000000C;
				break;
			case 13:
				cout << " K ";
				wyniki[0][player] += 0x000000D;
				break;
			case 14:
				cout << "AS ";
				wyniki[0][player] += 0x000000E;
				break;
			default: break;
			}
		}
	}

	if //je¿eli para jest na jednym z miejsc (nie gdy na obu) oblicza prawdopodobieñstwo
		((czypara1 == true && czypara2 == false) || (czypara1 == false && czypara2 == true))
	{
		//obliczanie prawdopodobienstwa majac w rece pare
		//wymienic mozna trzy karty lub dwie
		//jednej nie ma sensu

		int tmp1[3]; //tablica z kartami do wymiany
		int tmp2[2]; //tablica z kartami z ukladem w rece
		int gracztmp[5];
		double wartosc = 0;
		double wszystkie = 0;
		
		for (int l = 0; l < 5; l++) //przerzuca karty gracza do tablicy gracztmp[5] aby mo¿na by³o 
			//na nich operowaæ (kasowaæ, zamieniaæ) nie tracac ukladu jaki gracz posiada w rece
		{
			gracztmp[l] = gracz[l + (player * 5)];
		}

		if /*sprawdzenie gdzie w tablicy jest para gracza, przerzucenie ukladu do tablicy tmp2,
		   zamiana kart z ukladu na wartosc 99 (brak karty)*/
		   ((gracztmp[0] / 4) == (gracztmp[1] / 4))
		{
			tmp2[0] = gracztmp[0]; tmp2[1] = gracztmp[1]; gracztmp[0] = 99; gracztmp[1] = 99;
		}
		else if ((gracztmp[1] / 4) == (gracztmp[2] / 4))
		{
			tmp2[0] = gracztmp[1]; tmp2[1] = gracztmp[2]; gracztmp[1] = 99; gracztmp[2] = 99;
		}
		else if ((gracztmp[2] / 4) == (gracztmp[3] / 4))
		{
			tmp2[0] = gracztmp[2]; tmp2[1] = gracztmp[3]; gracztmp[2] = 99; gracztmp[3] = 99;
		}
		else if ((gracztmp[3] / 4) == (gracztmp[4] / 4))
		{
			tmp2[0] = gracztmp[3]; tmp2[1] = gracztmp[4]; gracztmp[3] = 99; gracztmp[4] = 99;
		}

		//sprawdza czy w rece gracza jest para i przerzuca karty z z poza uk³adu do tablicy tmp1

	
			int j = 0;
			for (int i = 0; i < 5; i++)
			{
				if (gracztmp[i] != 99)
				{
					tmp1[j] = gracztmp[i];
					j++;
				}
			}

			for (int m = 0; m < 13; m++) { wszystkie = wszystkie + resztki[m]; }

			{
				cout << "\n\ngracz " << player + 1 << " wymieniajac trzy karty: \n";
				for (int k = 0; k < 3; k++)	//wyswietla karty które nale¿y wymieniæ
				{
					SprawdzJednaKarte(tmp1[k]);
				}

				for (int m = 0; m < 13; m++) //zlicza ile kart pozosta³o dostêpnych w talii
				{
					wszystkie = wszystkie + resztki[m];
				}

				for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania drugiej pary
				{
					if (n != (tmp2[0] / 4)) {
						wartosc = wartosc + (resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1));
					}
				}
				cout << " masz szanse uzyskac dwie pary: " << wartosc * 100 << "%\n";
				wartosc = 0; // po wypisaniu prawdopodobieñstwa zmienna jest kasowana aby wykorzystaæ j¹ do nastêpnych uk³adów
				cout << " masz szanse uzyskac trojke: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
				cout << " masz szanse uzyskac fulla: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
				// do fula trzeba sprawdzic ktorych kart jest trzy sztuki np 5/47 (bo piec jest roznych kart po co najmniej 3 w talii
				// razy 1/47 bo trzeba dobrac druga karte


				cout << " masz szanse uzyskac karete: " << (resztki[(tmp2[0] / 4)] / wszystkie) * ((resztki[(tmp2[0] / 4)] - 1) / (wszystkie - 1)) * 100 << "%\n";

				if ((tmp2[0] % 4) == (tmp2[1] % 4))
				{
					cout << " masz szanse uzyskac kolor: " << (resztki[(tmp2[0] % 4) + 13] / wszystkie)*(((resztki[(tmp2[0] % 4) + 13]) - 1) / (wszystkie)-1)*(((resztki[(tmp2[0] % 4) + 13]) - 2) / (wszystkie)-2) * 100 << "%\n";
				}
				
			}


			{
				cout << "\nwymieniajac dwie karty: \n";
				for (int k = 0; k < 2; k++)
				{
					SprawdzJednaKarte(tmp1[k]);
				}



				for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania drugiej pary
				{
					if (n != (tmp2[0] / 4)) {
						wartosc = wartosc + (resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1));
					}
				}

				wartosc = (wartosc + resztki[(tmp1[2] / 4) - 2] / wszystkie);

				cout << " masz szanse uzyskac dwie pary: " << wartosc * 100 << "%\n";
				cout << " masz szanse uzyskac trojke: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
				//trzeba sprawdzic czy jest jeszcze taka talia w kartach ktora pozwoli uzyskac trojke

				cout << " masz szanse uzyskac fulla: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
				// 1/47 razy 1/47 bo musimy dobrac do trzeciej karty (trzeba sprawdzic czy jest wystarczajaco takich w talii

				cout << " masz szanse uzyskac karete: " << (resztki[(tmp2[0] / 4)] / wszystkie) * ((resztki[(tmp2[0] / 4)] - 1) / (wszystkie - 1)) * 100 << "%\n";

				if ((tmp2[0] % 4) == (tmp2[1] % 4))
				{
					cout << " masz szanse uzyskac kolor: " << (resztki[(tmp2[0] % 4) + 13] / wszystkie)*(((resztki[(tmp2[0] % 4) + 13]) - 1) / (wszystkie)-1)*(((resztki[(tmp2[0] % 4) + 13]) - 2) / (wszystkie)-2) * 100 << "%\n";
					//trzeba sprawdzic czy jest wystarczajaco kart w talii aby uzyskac kolor
				}
			}
		}
	
	if //sprawdz dwie pary
		((((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) ||
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))) &&
		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) ||
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		if ((czypara1==true) && (czypara2==true)) {
			cout << "\n gracz " << player + 1 << " ma dwie pary";
		}
		else if (czypara1 == true){
			cout << "\n gracz " << player + 1 << " ma pare";
		}
		else if (czypara2 == true){
			cout << "\n gracz " << player + 1 << " ma pare";
		}
	}

	
	
	if //sprawdz poker
		(((gracz[player * 5] / 4) == ((gracz[1 + (player * 5)] / 4) - 1) &&
		(gracz[1 + (player * 5)] / 4) == ((gracz[2 + (player * 5)] / 4) - 1) &&
		(gracz[2 + (player * 5)] / 4) == ((gracz[3 + (player * 5)] / 4) - 1) &&
		(gracz[3 + (player * 5)] / 4) == ((gracz[4 + (player * 5)] / 4) - 1))
		&&
		((gracz[player * 5] % 4) == (gracz[1 + (player * 5)] % 4) &&
		(gracz[1 + (player * 5)] % 4) == (gracz[2 + (player * 5)] % 4) &&
		(gracz[2 + (player * 5)] % 4) == (gracz[3 + (player * 5)] % 4) &&
		(gracz[3 + (player * 5)] % 4) == (gracz[4 + (player * 5)] % 4)))
	{
		cout << "\n gracz " << player + 1 << " ma pokera";
		switch ((gracz[(player * 5) + 4] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x20000000;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x30000000;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x40000000;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x50000000;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x60000000;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x70000000;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x80000000;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x90000000;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0xA0000000;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0xB0000000;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0xC0000000;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0xD0000000;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0xE0000000;
			break;
		default: break;
		}
	}

	if //sprawdz kolor
		((gracz[player * 5] % 4) == (gracz[1 + (player * 5)] % 4) &&
		(gracz[1 + (player * 5)] % 4) == (gracz[2 + (player * 5)] % 4) &&
		(gracz[2 + (player * 5)] % 4) == (gracz[3 + (player * 5)] % 4) &&
		(gracz[3 + (player * 5)] % 4) == (gracz[4 + (player * 5)] % 4))
	{
		cout << "\n gracz " << player + 1 << " ma kolor";

		switch (gracz[player * 5] % 4)
		{
		case 0:
			cout << "pik, ";
			wyniki[0][player] += 0x1000000;
			break;
		case 1:
			cout << "trefl, ";
			wyniki[0][player] += 0x2000000;
			break;
		case 2:
			cout << "kier, ";
			wyniki[0][player] += 0x3000000;
			break;
		case 3:
			cout << "karo, ";
			wyniki[0][player] += 0x4000000;
			break;
		default: break;
		}
	}

	if //sprawdz strita
		((gracz[player * 5] / 4) == ((gracz[1 + (player * 5)] / 4) - 1) &&
		(gracz[1 + (player * 5)] / 4) == ((gracz[2 + (player * 5)] / 4) - 1) &&
		(gracz[2 + (player * 5)] / 4) == ((gracz[3 + (player * 5)] / 4) - 1) &&
		(gracz[3 + (player * 5)] / 4) == ((gracz[4 + (player * 5)] / 4) - 1))
	{
		cout << "\n gracz " << player + 1 << " ma strita";
		switch ((gracz[(player * 5) + 4] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0002000;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0003000;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0004000;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0005000;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0006000;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0007000;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0008000;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0009000;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x000A000;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x000B000;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x000C000;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x000D000;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x000E000;
			break;
		default: break;
		}
	}

	
	if //sprawdzenie prawdopodobienstwa przy rowerku
		((czypara1 == false) && (czypara2 == false) && 
		(czytrojka == false) && (czyfull == false) && (czykareta == false) && 
		(czykolor == false) && (czypoker == false) && (czystrit == false))
	{
		int tmp1[3]; //tablica z kartami do wymiany
		int tmp3[4]; //tablica z kartami do wymiany w rowerku
		int gracztmp[5];
		double wartosc = 0;
		double wszystkie = 0;
		int j = 0;

		for (int l = 0; l < 5; l++) //przerzuca karty gracza do tablicy gracztmp[5] aby mo¿na by³o 
			//na nich operowaæ (kasowaæ, zamieniaæ) nie tracac ukladu jaki gracz posiada w rece
		{
			gracztmp[l] = gracz[l + (player * 5)];
		}

		
		for (int i = 0; i < 5; i++)
		{
			if (gracztmp[i] != 99)
			{
				tmp3[j] = gracztmp[i];
				j++;
			}
		}
		cout << "\n\ngracz " << player+1 << " wymieniajac cztery karty: \n";
		for (int k = 0; k < 4; k++)	//wyswietla karty które nale¿y wymieniæ
		{
			SprawdzJednaKarte(tmp3[k]);
		}

		
		for (int m = 0; m < 13; m++) //zlicza ile kart pozosta³o dostêpnych w talii
		{
			wszystkie = wszystkie + resztki[m];
		}



		for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania pary z rowerka
		{
			if (n != (gracztmp[4] / 4)) {
				wartosc = wartosc + ((resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1)));
			}
		}
		wartosc = wartosc + (resztki[(gracztmp[4]/4)] / wszystkie);

		cout << " masz szanse uzyskac pare: " << wartosc * 100 << "%\n";
			wartosc = 0; // po wypisaniu prawdopodobieñstwa zmienna jest kasowana aby wykorzystaæ j¹ do nastêpnych uk³adów




			for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania dwoch par z rowerka
			{
				if (n != (gracztmp[4] / 4)) {
					wartosc = wartosc + ((resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1))*((resztki[n] - 2) / (wszystkie - 2)));
				}
			}

			wartosc = wartosc + (resztki[(gracztmp[4] / 4)] / wszystkie) * (resztki[(gracztmp[4] / 4) - 1] / wszystkie);

			cout << " masz szanse uzyskac dwie pary: " << wartosc * 100 << "%\n";
			wartosc = 0; // po wypisaniu prawdopodobieñstwa zmienna jest kasowana aby wykorzystaæ j¹ do nastêpnych uk³adów



		for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania dwoch par z rowerka
		{
			if (n != (gracztmp[4] / 4)) {
				wartosc = wartosc + ((resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1)));
			}
		}

		wartosc = wartosc * (resztki[(gracztmp[4]/4)] / wszystkie);

		cout << " masz szanse uzyskac trojki: " << wartosc * 100 << "%\n";
		wartosc = 0; // po wypisaniu prawdopodobieñstwa zmienna jest kasowana aby wykorzystaæ j¹ do nastêpnych uk³adów






		for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania fulla z rowerka
		{
			if (n != (gracztmp[4] / 4)) {
				wartosc = wartosc + ((resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1))*((resztki[n] - 2) / (wszystkie - 2)));
			}
		}

		wartosc = wartosc * (resztki[(gracztmp[4] / 4)] / wszystkie);

		cout << " masz szanse uzyskac fulla: " << wartosc * 100 << "%\n";
		wartosc = 0; // po wypisaniu prawdopodobieñstwa zmienna jest kasowana aby wykorzystaæ j¹ do nastêpnych uk³adów





		




	//	cout << " masz szanse uzyskac fulla: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
		// do fula trzeba sprawdzic ktorych kart jest trzy sztuki np 5/47 (bo piec jest roznych kart po co najmniej 3 w talii
		// razy 1/47 bo trzeba dobrac druga karte


	//	cout << " masz szanse uzyskac karete: " << (resztki[(tmp2[0] / 4)] / wszystkie) * ((resztki[(tmp2[0] / 4)] - 1) / (wszystkie - 1)) * 100 << "%\n";

	//	if ((tmp2[0] % 4) == (tmp2[1] % 4))
	//	{
	//		cout << " masz szanse uzyskac kolor: " << (resztki[(tmp2[0] % 4) + 13] / wszystkie)*(((resztki[(tmp2[0] % 4) + 13]) - 1) 
	//			/ (wszystkie)-1)*(((resztki[(tmp2[0] % 4) + 13]) - 2) / (wszystkie)-2) * 100 << "%\n";
	//	}
	}





	if (czytrojka == true) //prawdopodobienstwo przy trojce
	{

		int tmp1[3]; //tablica z kartami do wymiany
		int tmp2[2]; //tablica z kartami z ukladem w rece
		int gracztmp[5];
		double wartosc = 0;
		double wszystkie = 0;

		for (int l = 0; l < 5; l++) //przerzuca karty gracza do tablicy gracztmp[5] aby mo¿na by³o 
			//na nich operowaæ (kasowaæ, zamieniaæ) nie tracac ukladu jaki gracz posiada w rece
		{
			gracztmp[l] = gracz[l + (player * 5)];
		}

		int j = 0;
		for (int i = 0; i < 5; i++)
		{
			if (gracztmp[i] != 99)
			{
				tmp2[j] = gracztmp[i];
				j++;
			}
		}
		cout << "\n\ngracz " << player + 1 << " wymieniajac dwie karty: \n";
		for (int k = 0; k < 2; k++)	//wyswietla karty które nale¿y wymieniæ
		{
			SprawdzJednaKarte(tmp1[k]);
		}

		wszystkie = 0;


		for (int m = 0; m < 13; m++) //zlicza ile kart pozosta³o dostêpnych w talii
		{
			wszystkie = wszystkie + resztki[m];
		}

		for (int n = 0; n < 13; n++) //zlicza prawdopodobienstwo uzyskania drugiej pary
		{
			if (n != (tmp2[0] / 4)) {
				wartosc = wartosc + (resztki[n] / wszystkie)*((resztki[n] - 1) / (wszystkie - 1));
			}
		}
		//cout << " masz szanse uzyskac dwie pary: " << wartosc * 100 << "%\n";
		//wartosc = 0; // po wypisaniu prawdopodobieñstwa zmienna jest kasowana aby wykorzystaæ j¹ do nastêpnych uk³adów
		//cout << " masz szanse uzyskac trojke: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
		cout << " masz szanse uzyskac fulla: " << resztki[(tmp2[0] / 4)] / wszystkie * 100 << "%\n";
		// do fula trzeba sprawdzic ktorych kart jest trzy sztuki np 5/47 (bo piec jest roznych kart po co najmniej 3 w talii
		// razy 1/47 bo trzeba dobrac druga karte


		cout << " masz szanse uzyskac karete: " << (resztki[(tmp2[0] / 4)] / wszystkie) * 100 << "%\n";

	/*	if ((tmp2[0] % 4) == (tmp2[1] % 4))
		{
			cout << " masz szanse uzyskac kolor: " << (resztki[(tmp2[0] % 4) + 13] / wszystkie)*(((resztki[(tmp2[0] % 4) + 13]) - 1)
				/ (wszystkie)-1)*(((resztki[(tmp2[0] % 4) + 13]) - 2) / (wszystkie)-2) * 100 << "%\n";
		}*/
	}



	return 0;
}

//int SprawdzUkladPo(int player)
//{
//	bool czypara1 = false;
//	bool czypara2 = false;
//	bool czytrojka = false;
//	bool czyfull = false;
//
//	if //sprawdz trojke
//		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) &&
//		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))
//		||
//		((gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
//		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4))
//		||
//		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
//		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
//	{
//		czytrojka = true;
//		cout << "\n gracz " << player + 1 << " ma trojke";
//		switch ((gracz[(player * 5) + 2] / 4) + 2)
//		{
//		case 2:
//			cout << " 2 ";
//			wyniki[0][player] += 0x0000200;
//			break;
//		case 3:
//			cout << " 3 ";
//			wyniki[0][player] += 0x0000300;
//			break;
//		case 4:
//			cout << " 4 ";
//			wyniki[0][player] += 0x0000400;
//			break;
//		case 5:
//			cout << " 5 ";
//			wyniki[0][player] += 0x0000500;
//			break;
//		case 6:
//			cout << " 6 ";
//			wyniki[0][player] += 0x0000600;
//			break;
//		case 7:
//			cout << " 7 ";
//			wyniki[0][player] += 0x0000700;
//			break;
//		case 8:
//			cout << " 8 ";
//			wyniki[0][player] += 0x0000800;
//			break;
//		case 9:
//			cout << " 9 ";
//			wyniki[0][player] += 0x0000900;
//			break;
//		case 10:
//			cout << "10 ";
//			wyniki[0][player] += 0x0000A00;
//			break;
//		case 11:
//			cout << " J ";
//			wyniki[0][player] += 0x0000B00;
//			break;
//		case 12:
//			cout << " Q ";
//			wyniki[0][player] += 0x0000C00;
//			break;
//		case 13:
//			cout << " K ";
//			wyniki[0][player] += 0x0000D00;
//			break;
//		case 14:
//			cout << "AS ";
//			wyniki[0][player] += 0x0000E00;
//			break;
//		default: break;
//		}
//	}
//
//
//
//
//
//	if //sprawdz pierwsza pare (na pierwszych trzech kartach, ni¿szych)
//		((((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) ||
//		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))) && czytrojka == false)
//	{
//		czypara1 = true;
//		switch ((gracz[(player * 5) + 1] / 4) + 2)
//		{
//		case 2:
//			cout << " 2 ";
//			wyniki[0][player] += 0x0000020;
//			break;
//		case 3:
//			cout << " 3 ";
//			wyniki[0][player] += 0x0000030;
//			break;
//		case 4:
//			cout << " 4 ";
//			wyniki[0][player] += 0x0000040;
//			break;
//		case 5:
//			cout << " 5 ";
//			wyniki[0][player] += 0x0000050;
//			break;
//		case 6:
//			cout << " 6 ";
//			wyniki[0][player] += 0x0000060;
//			break;
//		case 7:
//			cout << " 7 ";
//			wyniki[0][player] += 0x0000070;
//			break;
//		case 8:
//			cout << " 8 ";
//			wyniki[0][player] += 0x0000080;
//			break;
//		case 9:
//			cout << " 9 ";
//			wyniki[0][player] += 0x0000090;
//			break;
//		case 10:
//			cout << "10 ";
//			wyniki[0][player] += 0x00000A0;
//			break;
//		case 11:
//			cout << " J ";
//			wyniki[0][player] += 0x00000B0;
//			break;
//		case 12:
//			cout << " Q ";
//			wyniki[0][player] += 0x00000C0;
//			break;
//		case 13:
//			cout << " K ";
//			wyniki[0][player] += 0x00000D0;
//			break;
//		case 14:
//			cout << "AS ";
//			wyniki[0][player] += 0x00000E0;
//			break;
//		default: break;
//		}
//	}
//
//
//
//
//
//	if //sprawdz pare dwa razy
//		(((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) ||
//		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)) && czytrojka == false)
//	{
//		czypara2 = true;
//		switch ((gracz[(player * 5) + 3] / 4) + 2)
//		{
//		case 2:
//			cout << " 2 ";
//			wyniki[0][player] += 0x0000002;
//			break;
//		case 3:
//			cout << " 3 ";
//			wyniki[0][player] += 0x0000003;
//			break;
//		case 4:
//			cout << " 4 ";
//			wyniki[0][player] += 0x0000004;
//			break;
//		case 5:
//			cout << " 5 ";
//			wyniki[0][player] += 0x0000005;
//			break;
//		case 6:
//			cout << " 6 ";
//			wyniki[0][player] += 0x0000006;
//			break;
//		case 7:
//			cout << " 7 ";
//			wyniki[0][player] += 0x0000007;
//			break;
//		case 8:
//			cout << " 8 ";
//			wyniki[0][player] += 0x0000008;
//			break;
//		case 9:
//			cout << " 9 ";
//			wyniki[0][player] += 0x0000009;
//			break;
//		case 10:
//			cout << "10 ";
//			wyniki[0][player] += 0x000000A;
//			break;
//		case 11:
//			cout << " J ";
//			wyniki[0][player] += 0x000000B;
//			break;
//		case 12:
//			cout << " Q ";
//			wyniki[0][player] += 0x000000C;
//			break;
//		case 13:
//			cout << " K ";
//			wyniki[0][player] += 0x000000D;
//			break;
//		case 14:
//			cout << "AS ";
//			wyniki[0][player] += 0x000000E;
//			break;
//		default: break;
//		}
//	}
//
//
//
//
//
//	if //sprawdz dwie pary
//		((((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) ||
//		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))) &&
//		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) ||
//		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
//	{
//		if ((czypara1 == true) && (czypara2 == true)) {
//			cout << "\n gracz " << player + 1 << " ma dwie pary";
//		}
//		else if (czypara1 == true){
//			cout << "\n gracz " << player + 1 << " ma pare";
//		}
//		else if (czypara2 == true){
//			cout << "\n gracz " << player + 1 << " ma pare";
//		}
//	}
//
//
//
//	if //sprawdz poker
//		(((gracz[player * 5] / 4) == ((gracz[1 + (player * 5)] / 4) - 1) &&
//		(gracz[1 + (player * 5)] / 4) == ((gracz[2 + (player * 5)] / 4) - 1) &&
//		(gracz[2 + (player * 5)] / 4) == ((gracz[3 + (player * 5)] / 4) - 1) &&
//		(gracz[3 + (player * 5)] / 4) == ((gracz[4 + (player * 5)] / 4) - 1))
//		&&
//		((gracz[player * 5] % 4) == (gracz[1 + (player * 5)] % 4) &&
//		(gracz[1 + (player * 5)] % 4) == (gracz[2 + (player * 5)] % 4) &&
//		(gracz[2 + (player * 5)] % 4) == (gracz[3 + (player * 5)] % 4) &&
//		(gracz[3 + (player * 5)] % 4) == (gracz[4 + (player * 5)] % 4)))
//	{
//		cout << "\n gracz " << player + 1 << " ma pokera";
//		switch ((gracz[(player * 5) + 4] / 4) + 2)
//		{
//		case 2:
//			cout << " 2 ";
//			wyniki[0][player] += 0x20000000;
//			break;
//		case 3:
//			cout << " 3 ";
//			wyniki[0][player] += 0x30000000;
//			break;
//		case 4:
//			cout << " 4 ";
//			wyniki[0][player] += 0x40000000;
//			break;
//		case 5:
//			cout << " 5 ";
//			wyniki[0][player] += 0x50000000;
//			break;
//		case 6:
//			cout << " 6 ";
//			wyniki[0][player] += 0x60000000;
//			break;
//		case 7:
//			cout << " 7 ";
//			wyniki[0][player] += 0x70000000;
//			break;
//		case 8:
//			cout << " 8 ";
//			wyniki[0][player] += 0x80000000;
//			break;
//		case 9:
//			cout << " 9 ";
//			wyniki[0][player] += 0x90000000;
//			break;
//		case 10:
//			cout << "10 ";
//			wyniki[0][player] += 0xA0000000;
//			break;
//		case 11:
//			cout << " J ";
//			wyniki[0][player] += 0xB0000000;
//			break;
//		case 12:
//			cout << " Q ";
//			wyniki[0][player] += 0xC0000000;
//			break;
//		case 13:
//			cout << " K ";
//			wyniki[0][player] += 0xD0000000;
//			break;
//		case 14:
//			cout << "AS ";
//			wyniki[0][player] += 0xE0000000;
//			break;
//		default: break;
//		}
//	}
//
//	if //sprawdz kolor
//		((gracz[player * 5] % 4) == (gracz[1 + (player * 5)] % 4) &&
//		(gracz[1 + (player * 5)] % 4) == (gracz[2 + (player * 5)] % 4) &&
//		(gracz[2 + (player * 5)] % 4) == (gracz[3 + (player * 5)] % 4) &&
//		(gracz[3 + (player * 5)] % 4) == (gracz[4 + (player * 5)] % 4))
//	{
//		cout << "\n gracz " << player + 1 << " ma kolor";
//
//		switch (gracz[player * 5] % 4)
//		{
//		case 0:
//			cout << "pik, ";
//			wyniki[0][player] += 0x1000000;
//			break;
//		case 1:
//			cout << "trefl, ";
//			wyniki[0][player] += 0x2000000;
//			break;
//		case 2:
//			cout << "kier, ";
//			wyniki[0][player] += 0x3000000;
//			break;
//		case 3:
//			cout << "karo, ";
//			wyniki[0][player] += 0x4000000;
//			break;
//		default: break;
//		}
//	}
//
//	if //sprawdzenie kareta
//		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) &&
//		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
//		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4))
//		||
//		((gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
//		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
//		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
//	{
//		cout << "\n gracz " << player + 1 << " ma karete";
//		switch ((gracz[(player * 5) + 1] / 4) + 2)
//		{
//		case 2:
//			cout << " 2 ";
//			wyniki[0][player] += 0x0200000;
//			break;
//		case 3:
//			cout << " 3 ";
//			wyniki[0][player] += 0x0300000;
//			break;
//		case 4:
//			cout << " 4 ";
//			wyniki[0][player] += 0x0400000;
//			break;
//		case 5:
//			cout << " 5 ";
//			wyniki[0][player] += 0x0500000;
//			break;
//		case 6:
//			cout << " 6 ";
//			wyniki[0][player] += 0x0600000;
//			break;
//		case 7:
//			cout << " 7 ";
//			wyniki[0][player] += 0x0700000;
//			break;
//		case 8:
//			cout << " 8 ";
//			wyniki[0][player] += 0x0800000;
//			break;
//		case 9:
//			cout << " 9 ";
//			wyniki[0][player] += 0x0900000;
//			break;
//		case 10:
//			cout << "10 ";
//			wyniki[0][player] += 0x0A00000;
//			break;
//		case 11:
//			cout << " J ";
//			wyniki[0][player] += 0x0B00000;
//			break;
//		case 12:
//			cout << " Q ";
//			wyniki[0][player] += 0x0C00000;
//			break;
//		case 13:
//			cout << " K ";
//			wyniki[0][player] += 0x0D00000;
//			break;
//		case 14:
//			cout << "AS ";
//			wyniki[0][player] += 0x0E00000;
//			break;
//		default: break;
//		}
//		return 0;
//	}
//
//	if //sprawdz full'a :)
//		(((gracz[(player * 5)] / 4) == (gracz[1 + (player * 5)] / 4) &&
//		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
//		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)) ||
//		((gracz[(player * 5)] / 4) == (gracz[1 + (player * 5)] / 4) &&
//		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
//		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
//	{
//		cout << "\n gracz " << player + 1 << " ma full'a";
//		wyniki[0][player] += 0x0010000;
//
//	}
//
//
//	if //sprawdz strita
//		((gracz[player * 5] / 4) == ((gracz[1 + (player * 5)] / 4) - 1) &&
//		(gracz[1 + (player * 5)] / 4) == ((gracz[2 + (player * 5)] / 4) - 1) &&
//		(gracz[2 + (player * 5)] / 4) == ((gracz[3 + (player * 5)] / 4) - 1) &&
//		(gracz[3 + (player * 5)] / 4) == ((gracz[4 + (player * 5)] / 4) - 1))
//	{
//		cout << "\n gracz " << player + 1 << " ma strita";
//		switch ((gracz[(player * 5) + 4] / 4) + 2)
//		{
//		case 2:
//			cout << " 2 ";
//			wyniki[0][player] += 0x0002000;
//			break;
//		case 3:
//			cout << " 3 ";
//			wyniki[0][player] += 0x0003000;
//			break;
//		case 4:
//			cout << " 4 ";
//			wyniki[0][player] += 0x0004000;
//			break;
//		case 5:
//			cout << " 5 ";
//			wyniki[0][player] += 0x0005000;
//			break;
//		case 6:
//			cout << " 6 ";
//			wyniki[0][player] += 0x0006000;
//			break;
//		case 7:
//			cout << " 7 ";
//			wyniki[0][player] += 0x0007000;
//			break;
//		case 8:
//			cout << " 8 ";
//			wyniki[0][player] += 0x0008000;
//			break;
//		case 9:
//			cout << " 9 ";
//			wyniki[0][player] += 0x0009000;
//			break;
//		case 10:
//			cout << "10 ";
//			wyniki[0][player] += 0x000A000;
//			break;
//		case 11:
//			cout << " J ";
//			wyniki[0][player] += 0x000B000;
//			break;
//		case 12:
//			cout << " Q ";
//			wyniki[0][player] += 0x000C000;
//			break;
//		case 13:
//			cout << " K ";
//			wyniki[0][player] += 0x000D000;
//			break;
//		case 14:
//			cout << "AS ";
//			wyniki[0][player] += 0x000E000;
//			break;
//		default: break;
//		}
//	}
//
//
//
//
//
//
//
//
//
//	return 0;
//}

int SprawdzUkladPo(int player)
{
	bool czydwiepary = 0;


	if //sprawdz poker
		(((gracz[player * 5] / 4) == ((gracz[1 + (player * 5)] / 4) - 1) &&
		(gracz[1 + (player * 5)] / 4) == ((gracz[2 + (player * 5)] / 4) - 1) &&
		(gracz[2 + (player * 5)] / 4) == ((gracz[3 + (player * 5)] / 4) - 1) &&
		(gracz[3 + (player * 5)] / 4) == ((gracz[4 + (player * 5)] / 4) - 1))
		&&
		((gracz[player * 5] % 4) == (gracz[1 + (player * 5)] % 4) &&
		(gracz[1 + (player * 5)] % 4) == (gracz[2 + (player * 5)] % 4) &&
		(gracz[2 + (player * 5)] % 4) == (gracz[3 + (player * 5)] % 4) &&
		(gracz[3 + (player * 5)] % 4) == (gracz[4 + (player * 5)] % 4)))
	{
		cout << "\n gracz " << player + 1 << " ma pokera";
		switch ((gracz[(player * 5) + 4] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x20000000;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x30000000;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x40000000;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x50000000;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x60000000;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x70000000;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x80000000;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x90000000;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0xA0000000;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0xB0000000;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0xC0000000;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0xD0000000;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0xE0000000;
			break;
		default: break;
		}
	}

	if //sprawdz kolor
		((gracz[player * 5] % 4) == (gracz[1 + (player * 5)] % 4) &&
		(gracz[1 + (player * 5)] % 4) == (gracz[2 + (player * 5)] % 4) &&
		(gracz[2 + (player * 5)] % 4) == (gracz[3 + (player * 5)] % 4) &&
		(gracz[3 + (player * 5)] % 4) == (gracz[4 + (player * 5)] % 4))
	{
		cout << "\n gracz " << player + 1 << " ma kolor";

		switch (gracz[player * 5] % 4)
		{
		case 0:
			cout << "pik, ";
			wyniki[0][player] += 0x1000000;
			break;
		case 1:
			cout << "trefl, ";
			wyniki[0][player] += 0x2000000;
			break;
		case 2:
			cout << "kier, ";
			wyniki[0][player] += 0x3000000;
			break;
		case 3:
			cout << "karo, ";
			wyniki[0][player] += 0x4000000;
			break;
		default: break;
		}
	}

	if //sprawdzenie kareta
		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4))
		||
		((gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		cout << "\n gracz " << player + 1 << " ma karete";
		switch ((gracz[(player * 5) + 1] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0200000;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0300000;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0400000;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0500000;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0600000;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0700000;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0800000;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0900000;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x0A00000;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x0B00000;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x0C00000;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x0D00000;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x0E00000;
			break;
		default: break;
		}
		return 0;
	}

	if //sprawdz full'a :)
		(((gracz[(player * 5)] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)) ||
		((gracz[(player * 5)] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		cout << "\n gracz " << player + 1 << " ma full'a";
		wyniki[0][player] += 0x0010000;

	}


	if //sprawdz strita
		((gracz[player * 5] / 4) == ((gracz[1 + (player * 5)] / 4) - 1) &&
		(gracz[1 + (player * 5)] / 4) == ((gracz[2 + (player * 5)] / 4) - 1) &&
		(gracz[2 + (player * 5)] / 4) == ((gracz[3 + (player * 5)] / 4) - 1) &&
		(gracz[3 + (player * 5)] / 4) == ((gracz[4 + (player * 5)] / 4) - 1))
	{
		cout << "\n gracz " << player + 1 << " ma strita";
		switch ((gracz[(player * 5) + 4] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0002000;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0003000;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0004000;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0005000;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0006000;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0007000;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0008000;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0009000;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x000A000;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x000B000;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x000C000;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x000D000;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x000E000;
			break;
		default: break;
		}
	}

	if //sprawdz trojke
		(((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) &&
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))
		||
		((gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4) &&
		(gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4))
		||
		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) &&
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4))
		)
	{
		cout << "\n gracz " << player + 1 << " ma trojke";
		switch ((gracz[(player * 5) + 2] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0000200;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0000300;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0000400;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0000500;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0000600;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0000700;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0000800;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0000900;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x0000A00;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x0000B00;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x0000C00;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x0000D00;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x0000E00;
			break;
		default: break;
		}
	}

	if //sprawdz dwie pary
		((((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) ||
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))) &&
		((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) ||
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)))
	{
		cout << "\n gracz " << player + 1 << " ma dwie pary";
		czydwiepary = true;
	}

	if //sprawdz druga pare
		((((gracz[player * 5] / 4) == (gracz[1 + (player * 5)] / 4) ||
		(gracz[1 + (player * 5)] / 4) == (gracz[2 + (player * 5)] / 4))) && czydwiepary == false)
	{
		cout << "\n gracz " << player + 1 << " ma pare";
		switch ((gracz[(player * 5) + 1] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0000020;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0000030;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0000040;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0000050;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0000060;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0000070;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0000080;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0000090;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x00000A0;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x00000B0;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x00000C0;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x00000D0;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x00000E0;
			break;
		default: break;
		}
	}

	if //sprawdz pare dwa razy
		(((gracz[2 + (player * 5)] / 4) == (gracz[3 + (player * 5)] / 4) ||
		(gracz[3 + (player * 5)] / 4) == (gracz[4 + (player * 5)] / 4)) && czydwiepary == false)
	{
		cout << "\n gracz " << player + 1 << " ma pare";
		switch ((gracz[(player * 5) + 3] / 4) + 2)
		{
		case 2:
			cout << " 2 ";
			wyniki[0][player] += 0x0000002;
			break;
		case 3:
			cout << " 3 ";
			wyniki[0][player] += 0x0000003;
			break;
		case 4:
			cout << " 4 ";
			wyniki[0][player] += 0x0000004;
			break;
		case 5:
			cout << " 5 ";
			wyniki[0][player] += 0x0000005;
			break;
		case 6:
			cout << " 6 ";
			wyniki[0][player] += 0x0000006;
			break;
		case 7:
			cout << " 7 ";
			wyniki[0][player] += 0x0000007;
			break;
		case 8:
			cout << " 8 ";
			wyniki[0][player] += 0x0000008;
			break;
		case 9:
			cout << " 9 ";
			wyniki[0][player] += 0x0000009;
			break;
		case 10:
			cout << "10 ";
			wyniki[0][player] += 0x000000A;
			break;
		case 11:
			cout << " J ";
			wyniki[0][player] += 0x000000B;
			break;
		case 12:
			cout << " Q ";
			wyniki[0][player] += 0x000000C;
			break;
		case 13:
			cout << " K ";
			wyniki[0][player] += 0x000000D;
			break;
		case 14:
			cout << "AS ";
			wyniki[0][player] += 0x000000E;
			break;
		default: break;
		}

	}
	return 0;
}             

void WymianaKart()
{
	int i;
	char CzyWymienic;
	int KtoWymienia, IloscKart, KartaDoWymiany;

	cout << "\nCzy ktorys z graczy chce wymienic karte? t/n" << endl;
	cin >> CzyWymienic;
	while (CzyWymienic == 't')
	{
		cout << "Ktory gracz chce wymienic karty? Aby przerwac wybierz N\n";
		cin >> KtoWymienia;
		cout << "Ile kart chcesz wymienic?";
		cin >> IloscKart;



		SprawdzKarte(KtoWymienia - 1, 1);
		cout << "Wpisz ktora z kolei karte chcesz wimienic potwierdzajac kazda ENTERem?";
		for (i = 1; i <= IloscKart; i++)
		{
			cin >> KartaDoWymiany;
			int X = (rand() % (52 * ((IloscGraczy / 5) + 1)));
			//cout << endl << i << "wylosowano " << X << endl;
			while (talia[X] == 99)
			{
				if (X>51 && IloscGraczy <5) {
					X = X - 51;
				};
				if (X>103 && IloscGraczy >4) {
					X = X - 103;
				};
				X++;
			}

			gracz[(((KtoWymienia - 1) * 5) + (KartaDoWymiany - 1))] = talia[X];
			talia[X] = 99;
		}
		cout << "Czy ktos jeszcze chce wymienic karty T? Aby zakonczyc wybierz N";
		cin >> CzyWymienic;
	}

}

void SprawdzCoZostalo()
{
	resztki[0] = 0; //2
	resztki[1] = 0; //3
	resztki[2] = 0; //4
	resztki[3] = 0; //5
	resztki[4] = 0; //6
	resztki[5] = 0; //7
	resztki[6] = 0; //8
	resztki[7] = 0; //9
	resztki[8] = 0; //10
	resztki[9] = 0; //J
	resztki[10] = 0; //Q
	resztki[11] = 0; //K
	resztki[12] = 0; //AS
	resztki[13] = 0; //PIK
	resztki[14] = 0; //TREFL
	resztki[15] = 0; //KIER
	resztki[16] = 0; //KARO

	for (int i = 0; i < 52 * ((IloscGraczy + 3) / 4); i++)
	{			
		if (talia[i] != 99)
		{

			int figura = (talia[i] / 4);

			switch (figura + 2)
			{
			case 2:
				resztki[0]++;
				break;
			case 3:
				resztki[1]++;
				break;
			case 4:
				resztki[2]++;
				break;
			case 5:
				resztki[3]++;
				break;
			case 6:
				resztki[4]++;
				break;
			case 7:
				resztki[5]++;
				break;
			case 8:
				resztki[6]++;
				break;
			case 9:
				resztki[7]++;
				break;
			case 10:
				resztki[8]++;
				break;
			case 11:
				resztki[9]++;
				break;
			case 12:
				resztki[10]++;
				break;
			case 13:
				resztki[11]++;
				break;
			case 14:
				resztki[12]++;
				break;
			default: break;
			}


			int kolor = (talia[i] % 4);

			switch (kolor)
			{
			case 0:
				resztki[13]++;
				break;
			case 1:
				resztki[14]++;
				break;
			case 2:
				resztki[15]++;
				break;
			case 3:
				resztki[16]++;
				break;
			default: break;
			}
		}
	}
}


int main()
{
	int i;
	int k = 0;
	srand(static_cast<unsigned int>(time(NULL)));

	cout << "Podaj liczbe graczy od 1 do 20: ";
	cin >> IloscGraczy;
	while ((IloscGraczy <= 0) || (IloscGraczy >= 21))
	{
		cout << "Podaj liczbe graczy z przedzialu 1 - 20: ";
		cin >> IloscGraczy;
	}
	StworzTalie();
	RozdajKarty();
	SortujKarty();
	SprawdzCoZostalo();

	for (i = 0; i < IloscGraczy; i++)
		SprawdzKarte(i, 0);

	for (i = 0; i < IloscGraczy; i++)
		SprawdzUkladPrzed(i);

	/*for (i = 0; i < IloscGraczy; i++)
		SprawdzParePP(i);*/

	WymianaKart();
	SortujKarty();

	for (i = 0; i < IloscGraczy; i++)
		SprawdzKarte(i, 0);

	for (i = 0; i < IloscGraczy; i++)
		SprawdzUkladPo(i);

	system("PAUSE");
	return 0;
}