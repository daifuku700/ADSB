#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned short us;

int n, m, p, k;

int model = 0;

void input_data(int, char **);

int main(int argc, char **argv) {
    clock_t tic, toc;
    struct timespec start, end;

    if (argc != 4) {
        perror("the number of command line arguments should be three\n");
        exit(1);
    }

    tic = clock();
    clock_gettime(CLOCK_REALTIME, &start);

    char line[(int)1e4 + 10];
    char A[10000 + 10];

    FILE *range = fopen(argv[2], "r");
    if (range == NULL) {
        perror("could not open the file\n");
        exit(2);
    }
    if (fgets(line, sizeof(line), range) != NULL) {
        if (line[5] == '1') {
            n = 1000, m = 10000, p = 30000, k = 8;
            model = 1;
        } else {
            n = 1000, m = 10000, p = 50000, k = 300;
            model = 2;
        }
    }

    FILE *data = fopen(argv[1], "r");
    if (data == NULL) {
        perror("could not open the file\n");
        exit(3);
    }
    if (fgets(line, sizeof(line), data) != NULL) {
        for (int j = 0; j < m; j++) {
            A[j] = line[j];
        }
    }

    FILE *output = fopen(argv[3], "w");
    if (output == NULL) {
        perror("could not open the file\n");
        exit(4);
    }

    if (model == 1) {
        us **ans = (us **)malloc(sizeof(us *) * m);
        for (int i = 0; i < m; i++) {
            ans[i] = (us *)calloc(sizeof(us), 8);
        }
        for (; fgets(line, sizeof(line), data) != NULL;) {
            for (int i = 0; i < m; i++) {
                for (int h = 0; h < 8; h++) {
                    if (A[i + h] == line[i + h]) {
                        ans[i][h]++;
                    } else {
                        break;
                    }
                }
            }
        }
        int l, s;
        for (; fscanf(range, "%d, %d/n", &l, &s) != EOF;) {
            fprintf(output, "%d, %d, %d\n", l, s, ans[l][s - 1]);
        }
        printf("%d, %d, %d\n", l, s, ans[l][s - 1]);
    } else if (model == 2) {
        return 0;
        // for (int i = 0; i < p; i++) {
        //     int ans = 0;
        //     for (int j = 0; j < n; j++) {
        //         if (s[i] == (data[j][l[i] + s[i]] - data[j][l[i]])) {
        //             ans++;
        //         }
        //     }
        //     fprintf(output, "%d, %d, %d\n", l[i], s[i], ans);
        // }
    }

    fclose(data);
    fclose(range);
    fclose(output);

    toc = clock();
    clock_gettime(CLOCK_REALTIME, &end);
    printf("clock: %lf\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    printf("time: %lf\n",
           ((double)end.tv_sec - (double)start.tv_sec) +
               ((double)end.tv_nsec - (double)start.tv_nsec) / 1e9);
    return 0;
}
