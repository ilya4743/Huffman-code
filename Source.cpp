#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

void print(int * count)
{
	cout << "Statistika: \n";
	for (int i = 0; i<4; i++)
	{
		cout << count[i] << " ";
	}
	cout << endl;
}

void printMasStr(char(*zamena)[4])
{
	for (int i = 0; i<4; i++)
	{
		cout << zamena[i] << endl;
	}
}

void sort(int* count, int* masSort)
{
	int k, k1;
	cout << "Sortirovka:\n";
	for (int i = 0; i<3; i++)
		for (int j = i + 1; j<4; j++)
		{
			if (count[j]>count[i])
			{
				k = count[i]; k1 = masSort[i];
				count[i] = count[j]; masSort[i] = masSort[j];
				count[j] = k; masSort[j] = k1;
			}
		}
}

void fzamena(int * masSort, char(*zamena)[4], char(*shifr)[4])
{
	for (int i = 0; i<4; i++)
		strcpy(zamena[masSort[i]], shifr[i]);
}

void initMass(int* count, int* masSort)
{
	for (int i = 0; i<4; i++)
	{
		count[i] = 0;
		masSort[i] = i;
	}
}

void createCount(char *fin, int* count)
{
	int k, j = 0;
	char ch;
	while (1)
	{
		ch = fin[j];
		if (j == strlen(fin))
			break;
		for (int i = 0; i<4; i++)
		{
			k = (ch >> (6 - i * 2)) & 3;
			count[k]++;
		}
		j++;
	}
}

void create_fout(char *fin, char *fout, char(*zamena)[4])
{
	int k, j = 0;
	char ch;
	char ch1[4][4];
	while (1)
	{
		ch = fin[j];
		if (fin[j] == NULL)
			break;
		for (int i = 0; i<4; i++)
		{
			k = (ch >> (6 - i * 2)) & 3;
			strcat(fout, zamena[k]);
		}
		j++;
	}
}

void Initn(char *fout, int n)
{
	for (int i = 0; i < n; i++)
		fout[i] = NULL;
}
int k = 0;
void createMasStr(char *fin, char(*mas)[4])
{
	char ch;

	for (int i = 0; i<4; i++)
	{
		ch = fin[k];
		if (ch == '0')
			strcpy(mas[i], "0");
		else if (ch == '1')
		{
			k++;
			ch = fin[k];
			if (ch == '0')
				strcpy(mas[i], "10");
			else
			{
				k++;
				ch = fin[k];
				if (ch == '0')
					strcpy(mas[i], "110");
				else
					strcpy(mas[i], "111");
			}
		}
		k++;
	}
}

void putToChar(char * fout, char(*str)[4], char(*zamena)[4])
{
	char chToFile = 0;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
			if (strcmp(str[i], zamena[j]) == 0)
				chToFile = chToFile | (j & 3) << (6 - i * 2);
	}
	if (chToFile >= 32) fout[strlen(fout)] = char(chToFile);
}

void main()
{
	char zamena[4][4];
	char shifr[4][4] = { "0", "10", "110", "111" }; // код Хаффмана
	char fin[1024];
	char fout[1024];
	char statistic[1024];
	int count[4], masSort[4];
	initMass(count, masSort);
	Initn(fout, 1024);
	Initn(statistic, 1024);
	cin.getline(fin, 1024);
	createCount(fin, count);
	print(count); // распечатка статистики
	sort(count, masSort); // сорт-ка - эл-т masSort содержит {0,1.2.3}
	print(count);
	print(masSort);
	fzamena(masSort, zamena, shifr); // эл-т м. zamena содержит код Хафф.
	printMasStr(zamena);

	for (int i = 0; i<4; i++)
	{
		strcat(fout, zamena[i]);
	}

	create_fout(fin, fout, zamena); // fout - текстовый файл, содержит коды Хафф.
	cout << fout;
	//	============ unzip_unzip_unzip_unzip_unzip =====================
	char str[4][4];
	char foutzip[1024];
	Initn(foutzip, 1024);
	int b = 0;
	createMasStr(fout, zamena);
	printMasStr(zamena);
	k = 0;
	while (1)
	{
		createMasStr(fout, str);
		if (fout[k - 1] == NULL)
			break;
		putToChar(foutzip, str, zamena);
		b++;
	}
	cout << foutzip<<endl;
	system("pause");
}