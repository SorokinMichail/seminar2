#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
void cheker(int** A, bool* c, int n, int max)
{
	for (int i = max; i > 0; i--) {
		if (A[n][i] == 1 && c[i] == false) {
			c[i] = true;
			cheker(A, c, i, max);
		}
	}
}
int max(int x, int y)
{
	return (x > y ? x : y);
}
int main()
{
	int** matrix = (int**)malloc(2 * sizeof(int*));
	FILE* graf;
	char fname[] = "gr.gv";
	graf = fopen(fname, "w");
	fprintf(graf, "graph g{");
	printf("select graph: \n");
	char c = getchar();
	int x = 1;
	int y = 1;
	int by = 0;
	while (c != '|') {
		matrix[x] = (int*)malloc(by * sizeof(int));
		while (c != '\n' && c!= '|') {
			if (y > by)
			{
				matrix[x] = (int*)realloc(matrix[x], (y + 1) * sizeof(int));
				by = y;
			}
			matrix[x][y] = c - '0';
			y++;
			c = getchar();
		}
		y = 1;
		if (c == '|')break;
		x++;
		c = getchar();
		matrix = (int**)realloc(matrix, (x + 1) * sizeof(int*));
	}
	int** matrix2 = (int**)malloc((x+1) * sizeof(int*));
	for (int i = 1; i <= x; i++) {
		matrix2[i] = (int*)malloc((x+1) * sizeof(int));
		for (int j = 1; j <= x; j++) {
			matrix2[i][j] = 0;
		}
	}
	for (int i = 1; i <= by; i++) {
		int b1 = 0;
		int b2 = 0;
		bool f = false;
		for (int j = 1; j <= x; j++) {
			if (matrix[j][i] == 1) {
				if (f) b2 = j;
				else b1 = j;
				f = true;
			}
		}
		if (b1 != 0) {
			if (b2 == 0)fprintf(graf, "%d--%d;\n", b1,b1);
			else {
				fprintf(graf, "%d--%d;\n", b1, b2);
				matrix2[b1][b2] = 1;
				matrix2[b2][b1] = 1;
			}
		}
	}
	for (int i = 1; i <= x; i++) {
		float c=false;
		for (int j = 1; j <= by; j++) {
			if (matrix[i][j] == 1)c = true;
		}
		if(!c)fprintf(graf, "%d;\n", i);
	}
	fprintf(graf, "}");
	fclose(graf);
	bool* chek = (bool*)malloc((x + 1) * sizeof(bool));
	for (int i = 1; i <= x; i++)chek[i] = false;
	chek[1] = true;
	cheker(matrix2, chek, 1, x);
	bool f = true;
	for (int i = 1; i <= x; i++)
		if (!chek[i])f = false;
	if (f) printf("True");
	else printf("False");
	system("dot -Tpng gr.gv -o gr.png");
	system("gr.png");
	return 0;
}
