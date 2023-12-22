#include <stdio.h>
#include <stdlib.h>

int n, m, p, k;
int *l, *s, *A;
int **X;

void input_data(int, char **);

int main(int argc, char **argv) {
    input_data(argc, argv);

    free(l);
    free(s);
    free(X);
    free(A);
    return 0;
}

void input_data(int argc, char **argv) {
    if (argc != 4) {
        perror("the number of command line arguments should be three\n");
        exit(1);
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("could not open the file\n");
        exit(2);
    }

    char line[(int)1e4 + 2];
    if (fgets(line, sizeof(line), file) != NULL) {
        if (line[5] == '1') {
            n = 1000, m = 10000, p = 30000, k = 8;
        } else {
            n = 1000, m = 10000, p = 50000, k = 300;
        }
    }
    X = (int **)malloc(sizeof(int *) * n);
    l = (int *)malloc(sizeof(int) * p);
    s = (int *)malloc(sizeof(int) * p);
    A = (int *)malloc(sizeof(int) * m);
    int a, b;
    for (int i = 0; fscanf(file, "%d, %d\n", &a, &b) != EOF; i++) {
        l[i] = a;
        s[i] = b;
    }

    fclose(file);

    file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("could not open the file\n");
        exit(3);
    }

    if (fgets(line, sizeof(line), file) != NULL) {
        for (int j = 0; j < m; j++) {
            A[j] = line[j];
        }
    }

    for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
        X[i] = (int *)malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++) {
            X[i][j] = line[j] - '0';
        }
    }
}
