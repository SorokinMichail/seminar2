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

int main()
{
	int length = 0;
	int** matrix = (int**)malloc(sizeof(int*));
	FILE* graf;
	char* fname = "gr.gv";
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
					matrix = (int**)realloc(matrix, (n + 1) * sizeof(int*));
					for (int i = length + 1; i <= n; i++) {
						matrix[i] = (int*)malloc(2*sizeof(int));
					}
					for (int i = 1; i <= n; i++) {
						matrix[i] = (int*)realloc(matrix[i], (n+1) * sizeof(int));
						for (int j = 1; j <= n; j++) {
							if (matrix[i][j] != 1)matrix[i][j] = 0;
						}
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
	bool* chek = (bool*)malloc((length + 1) * sizeof(bool));
	for (int i = 1; i < length; i++)chek[i] = false;
	chek[length] = true;
	cheker(matrix, chek, length,length);
	bool f = true;
	for (int i = 1; i <= length; i++)
		if (!chek[i])f = false;
	if (f) printf("True");
	else printf("False");
	system("dot -Tpng gr.gv -o gr.png");
	system("gr.png");
	return 0;
}
