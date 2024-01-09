#include <stdio.h>
#include <stdlib.h>

int n, m, p, k;
int *l, *s, *A;
int **data;

int model = 0;

void input_data(int, char **);

int main(int argc, char **argv) {
    input_data(argc, argv);

    FILE *file = fopen(argv[3], "w");

    if (model == 1) {
        int **ans = (int **)malloc(sizeof(int *) * m);
        for (int i = 0; i < m; i++) {
            int ceil = (8 < m - i) ? 8 : m - i;
            ans[i] = (int *)calloc(sizeof(int), k);
            for (int j = 0; j < n; j++) {
                for (int l = 0; l < ceil; l++) {
                    if (A[i + l] == data[j][i + l + 1]) {
                        ans[i][l]++;
                    } else {
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < p; i++) {
            fprintf(file, "%d, %d, %d\n", l[i], s[i], ans[l[i]][s[i] - 1]);
        }
    } else if (model == 2) {
        for (int i = 0; i < p; i++) {
            int ans = 0;
            for (int j = 0; j < n; j++) {
                if (s[i] == (data[j][l[i] + s[i]] - data[j][l[i]])) {
                    ans++;
                }
            }
            fprintf(file, "%d, %d, %d\n", l[i], s[i], ans);
        }
    }

    fclose(file);

    free(l);
    free(s);
    free(data);
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
            model = 1;
        } else {
            n = 1000, m = 10000, p = 50000, k = 300;
            model = 2;
        }
    }
    data = (int **)malloc(sizeof(int *) * n);
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
            A[j] = line[j] - '0';
        }
    }

    if (model == 1) {
        for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
            data[i] = (int *)malloc(sizeof(int) * (m + 1));
            data[i][0] = 0;
            for (int j = 0; j < m; j++) {
                data[i][j + 1] = line[j] - '0';
            }
        }
    } else if (model == 2) {
        for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
            data[i] = (int *)malloc(sizeof(int) * (m + 1));
            data[i][0] = 0;
            int now = 0, next;
            for (int j = 0; j < m; j++) {
                now = next;
                if (line[j] - '0' == A[j]) {
                    next = (data[i][j + 1] = now + 1);
                } else {
                    next = (data[i][j + 1] = now);
                }
            }
        }
    }
}
