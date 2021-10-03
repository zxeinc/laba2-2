#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

void multiply(int size)
{
	setlocale(LC_ALL, "RUS");

	int i = 0, j = 0, r = 0;
	int elem_c;

	//clock_t start, end;

	srand(time(NULL));// инициализируем параметры генератора случайных чисел
	int** a = 0;
	int** b = 0;
	int** c = 0;
	//int size;
	//printf("Введите размер матриц: ");
	//scanf("%d", &size);


	a = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
	{
		a[i] = (int*)malloc(size * sizeof(int));
	}

	b = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
	{
		b[i] = (int*)malloc(size * sizeof(int));
	}

	c = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
	{
		c[i] = (int*)malloc(size * sizeof(int));
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			a[i][j] = rand() % 99;
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			b[i][j] = rand() % 99;
		}
	}

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			elem_c = 0;
			for (r = 0; r < size; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}
}

void shell(int* items, int count)
{

	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
	int i = 0, j;
	int x, y;

	i = left; j = right;

	//выбор компаранда
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

int comp(const int* a, const int* b)
{
	return *a - *b;
}



int main(void)
{

	int count = 0, size = 0;
	clock_t start, end;
	setlocale(LC_ALL, "RUS");

	FILE* file;
	char inputname[16], filename[16];
	setlocale(LC_ALL, "Russian");
	printf("Введите название нового файла:\n>");		// Создание файла
	scanf("%s", inputname);
	strcpy(filename, inputname);
	file = fopen(filename, "w+");
	printf("Файл создан.");
	Sleep(999);
	system("cls");

	/*Умножение матриц*/
	printf("Умножение матриц:\n");
	printf("Введите размер матриц: ");
	scanf("%d", &size);
	start = clock();
	multiply(size);
	end = clock();
	float time = end - start;
	fprintf(file, "Умножение матриц: Время выполнения работы программы=%.4f с\n\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);
	end = 0;
	start = 0;

	/*Сортировка Шелла=================================================================*/
	printf("Сортировка Шелла:\n\n");
	printf("Введите размер маcсива:\n");

	scanf("%d", &count);
	int* items = (int*)malloc(count * sizeof(items));

	for (int i = 0; i < count; i++)
	{
		items[i] = rand() % 100;
	}
	printf("1. Случайный набор данных:\n");
	start = clock();
	shell(items, count);
	end = clock();
	time = end - start;
	fprintf(file, "Размер массива %d\n\n", count);
	fprintf(file, "Шелл, случайный набор данных: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);


	for (int i = 0; i < count; i++)
	{
		items[i] = i;
	}
	printf("2. Исходные данные по возрастанию:\n");
	start = clock();
	shell(items, count);
	end = clock();
	time = end - start;
	fprintf(file, "Шелл, исх. данные по возр.: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);


	for (int i = 0; i < count; i++)
	{
		items[i] = count - i;
	}
	printf("3. Исходные данные по убыванию:\n");
	start = clock();
	shell(items, count);
	end = clock();
	time = end - start;
	fprintf(file, "Шелл, исх. данные по убыванию: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		if (i < count / 2) {
			items[i] = i;
		}
		else {
			items[i] = count - i;
		}
	}
	printf("4. Исходные данные по возр. до середины массива, дальше - по убыванию\n");
	start = clock();
	shell(items, count);
	end = clock();
	time = end - start;
	fprintf(file, "Шелл, исх. данные возрастающе-убывающие.: Время выполнения =%.4f с\n\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);


	/*Быстрая сортировка=================================================================*/
	printf("Быстрая сортировка\n");
	printf("Размер массива %d\n\n", count);
	for (int i = 0; i < count; i++)
	{
		items[i] = rand() % 100;
	}
	printf("1. Случайный набор данных\n");
	start = clock();
	qs(items, count / 2, count - 1);
	end = clock();
	time = end - start;
	fprintf(file, "Быстрая сортировка, исх. данные по убыванию: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		items[i] = i;
	}
	printf("2. Исходные данные по возрастанию:\n");
	start = clock();
	qs(items, count / 2, count - 1);
	end = clock();
	time = end - start;
	fprintf(file, "Быстрая сортировка, исх. данные по возрастанию: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		items[i] = count - i;
	}
	printf("3. Исходные данные по убыванию:\n");
	start = clock();
	qs(items, count / 2, count - 1);
	end = clock();
	time = end - start;
	fprintf(file, "Быстрая сортировка, исх. данные по убыванию: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		if (i < count / 2) {
			items[i] = i;
		}
		else {
			items[i] = count - i;
		}
	}
	printf("4. Исходные данные по возр. до середины массива, дальше - по убыванию\n");
	start = clock();
	shell(items, count);
	end = clock();
	time = end - start;
	fprintf(file, "Быстрая с., исх. данные возрастающе-убывающие.: Время выполнения =%.4f с\n\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	/*quicksort=================================================================*/

	printf("Quicksort\n");
	printf("Размер массива %d\n\n", count);
	for (int i = 0; i < count; i++)
	{
		items[i] = rand() % 100;
	}
	printf("1. Случайный набор данных\n");
	start = clock();
	qsort(items, count, sizeof(int), (int(*) (const void*, const void*))comp);
	end = clock();
	time = end - start;
	fprintf(file, "Qsort, случайный набор данных: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		items[i] = i;
	}
	printf("2. Исходные данные по возрастанию:\n");
	start = clock();
	qsort(items, count, sizeof(int), (int(*) (const void*, const void*))comp);
	end = clock();
	time = end - start;
	fprintf(file, "Qsort, исх. данные по возрастанию: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		items[i] = count - i;
	}
	printf("3. Исходные данные по убыванию:\n");
	start = clock();
	qsort(items, count, sizeof(int), (int(*) (const void*, const void*))comp);
	end = clock();
	time = end - start;
	fprintf(file, "Qsort, исх. данные по убыванию: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);

	for (int i = 0; i < count; i++)
	{
		if (i < count / 2) {
			items[i] = i;
		}
		else {
			items[i] = count - i;
		}
	}
	printf("4. Исходные данные по возр. до середины массива, дальше - по убыванию\n");
	start = clock();
	qsort(items, count, sizeof(int), (int(*) (const void*, const void*))comp);
	end = clock();
	time = end - start;
	fprintf(file, "Qsort, исх. данные возрастающе-убывающие.: Время выполнения =%.4f с\n", time / CLOCKS_PER_SEC);
	printf("Время выполнения =%.4f с, результат записан в файл.\n\n", time / CLOCKS_PER_SEC);
	fclose(file);



	/*int variant;
	system("cls");  // очищаем экран
	printf("Главное меню\n\n");
	printf("Введите номер действия:\n");
	printf("1. Умножение матриц\n");
	printf("2. Сортировка Шелла\n");
	printf("3. Быстрая сортировка\n");
	printf("4. Быстрая сортировка(из ст. библиотеки)\n");
	printf("5. Выход\n");
	printf(">");

	do {
		scanf("%d", &variant);
		switch (variant) {
		case 1:
		{
			system("cls");
			multiply();
		}
		break;
		case 2:
		{
			system("cls");
			clock_t start, end;
			int count;
			int data;
			printf("Сортировка Шелла\n\n");
			printf("Введите размерность массива: ");
			scanf("%d", &count);
			int* items = (int*)malloc(count * sizeof(items));
			printf("По возр. или по уб.:\n");
			printf("1. По возрастанию\n");
			printf("2. По убыванию\n");
			printf("3. Случайный набор\n");
			printf("4. Пила\n");
			printf(">");
			scanf("%d", &data);

			switch (data)
			{
			case 1:
				for (int i = 0; i < count; i++)
				{
					items[i] = i;
				}
				break;
			case 2:
				for (int i = 0; i < count; i++)
				{
					items[i] = count - i;
				}
				break;
			case 3:
				for (int i = 0; i < count; i++)
				{
					items[i] = rand() % 100;
				}
				break;
			case 4:
				for (int i = 0; i < count; i++)
				{
					if (i < count / 2) {
						items[i] = i;
					}
					else {
						items[i] = count - i;
					}
				}
				break;
			}

			start = clock();
			shell(items, count);
			end = clock();
			float time = end - start;
			printf("Время выполнения работы программы=%.4f с\n", time / CLOCKS_PER_SEC);

		}
		break;
		case 3:
		{
			system("cls");
			clock_t start, end;
			int count;
			int data;
			printf("Быстрая сортировка\n\n");
			printf("Введите размерность массива: ");
			scanf("%d", &count);
			int* items = (int*)malloc(count * sizeof(items));
			printf("По возр. или по уб.:\n");
			printf("1. По возрастанию\n");
			printf("2. По убыванию\n");
			printf("3. Случайный набор\n");
			printf("4. Пила\n");
			printf(">");
			scanf("%d", &data);

			switch (data)
			{
			case 1:
				for (int i = 0; i < count; i++)
				{
					items[i] = i;
				}
				break;
			case 2:
				for (int i = 0; i < count; i++)
				{
					items[i] = count - i;
				}
				break;
			case 3:
				for (int i = 0; i < count; i++)
				{
					items[i] = rand() % 100;
				}
				break;
			case 4:
				for (int i = 0; i < count; i++)
				{
					if (i < count / 2) {
						items[i] = i;
					}
					else {
						items[i] = count - i;
					}
				}
				start = clock();
				qs(items, count / 2, count - 1);
				end = clock();
				float time = end - start;
				printf("Время выполнения работы программы=%.4f с\n", time / CLOCKS_PER_SEC);
				exit(0);
			}

			start = clock();
			qs(items, 0, count - 1);
			end = clock();
			float time = end - start;
			printf("Время выполнения работы программы=%.4f с\n", time / CLOCKS_PER_SEC);

		}
		break;

		case 4:
		{
			system("cls");
			clock_t start, end;
			int count;
			int data;
			printf("Сортировка qsort\n\n");
			printf("Введите размерность массива: ");
			scanf("%d", &count);
			int* items = (int*)malloc(count * sizeof(items));
			printf("По возр. или по уб.:\n");
			printf("1. По возрастанию\n");
			printf("2. По убыванию\n");
			printf("3. Случайный набор\n");
			printf("4. Пила\n");
			printf(">");
			scanf("%d", &data);

			switch (data)
			{
			case 1:
				for (int i = 0; i < count; i++)
				{
					items[i] = i;
				}
				break;
			case 2:
				for (int i = 0; i < count; i++)
				{
					items[i] = count - i;
				}
				break;
			case 3:
				for (int i = 0; i < count; i++)
				{
					items[i] = rand() % 100;
				}
				break;
			case 4:
				for (int i = 0; i < count; i++)
				{
					if (i < count / 2) {
						items[i] = i;
					}
					else {
						items[i] = count - i;
					}
				}
				break;
			}

			for (int i = 0; i < count; i++)
			{
				printf("(%d) ", items[i]);
			}
			start = clock();
			qsort(items, count, sizeof(int), (int(*) (const void*, const void*))comp);
			end = clock();
			float time = end - start;
			printf("Время выполнения работы программы=%.4f с\n", time / CLOCKS_PER_SEC);
			for (int i = 0; i < count; i++)
			{
				printf("(%d) ", items[i]);
			}
		}
		break;
		case 5:
		{
			exit(0);
		}
		break;
		}
		if (variant != 5)
			system("pause"); // задерживаем выполнение, чтобы пользователь мог увидеть результат выполнения выбранного пункта
	} while (variant != 5);*/
}
