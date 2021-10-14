#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

void cheker(int **A, bool *c, int n)
{
	for (int i = n; i > 0; i--) {
		if (A[n][i] == 1 && c[i] == false) {
			c[i] = true;
			cheker(A, c, i);
		}
	}
}

int main()
{
	int length = 0;
	int **matrix = (int **)malloc(sizeof(int *));
	FILE *graf;
	char *fname = "gr.gv";
	graf = fopen(fname, "w");
	fprintf(graf, "digraph g{");
	printf("select graph: \n");
	char c = getchar();
	char boofer = '&';
	while (c != '|') {
		if (c == '\n')
		{
			fprintf(graf, ";");
			boofer = '&';
		}
		fprintf(graf, "%c", c);
		if (isdigit(c))
			if (boofer == '&') {
				boofer = c;
			}
			else {
				if (boofer - '0' > length || c - '0' > length) {
					int n = max(boofer - '0', c - '0');
					matrix = (int **)realloc(matrix, (n + 1) * sizeof(int*));
					for (int i = length + 1; i <= n; i++) {
						matrix[i] = (int *)malloc(sizeof(int));
					}
					for (int i = 1; i <= n; i++) {
						matrix[i] = (int *)realloc(matrix[i], n*sizeof(int));
					}

					length = n;
				}
				matrix[boofer - '0'][c - '0'] = 1;
				matrix[c - '0'][boofer - '0'] = 1;
				boofer = '&';
			}
		c = getchar();
	}
	fprintf(graf, "}");
	fclose(graf);
		for (int i = 1; i <= length; i++) {
		for (int j = 1; j <= length; j++) {
			printf("%*d", 5, matrix[i][j]);
		}
		printf("\n");
	}
	bool *chek = (bool *)malloc((length + 1) * sizeof(bool));
	for (int i = 1; i < length; i++)chek[i] = false;
	chek[length] = true;
	cheker(matrix, chek, length);
	bool f = true;
	for (int i = 1; i <= length; i++)
		if (!chek[i])f = false;
	if (f) printf("True");
	else printf("False");
	//system("dot -Tpng gr.gv -o gr.png");
	return 0;
}