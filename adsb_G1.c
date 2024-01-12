#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned short us;

int n, m, p, k;

int model = 0;

int thread_num = 1;

char line[10000 + 302];
char A[10000 + 302];

int main(int argc, char **argv) {
    clock_t tic, toc;
    struct timespec start, end;

    if (argc != 4) {
        perror("the number of command line arguments should be three\n");
        exit(1);
    }

    tic = clock();
    clock_gettime(CLOCK_REALTIME, &start);

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
        us *ans;
        ans = (us *)malloc(sizeof(us) * (m + 8));
        us left;
        for (; fgets(line, sizeof(line), data) != NULL;) {
            left = 0;
            for (int i = 0; i < m; i++) {
                if (A[i] == line[i]) {
                    ans[i - left + i - 1]++;
                } else {
                    left = i;
                }
            }
        }
        short l, s;
        for (; fscanf(range, "%hd, %hd/n", &l, &s) != EOF;) {
            fprintf(output, "%d, %d, %d\n", l, s, ans[l + s - 1]);
        }
        free(ans);
    } else if (model == 2) {
        short l, s;
        for (; fscanf(range, "%hd, %hd/n", &l, &s) != EOF;) {
            // fprintf(output, "%d, %d, %d\n", l, s, ans[l][s - 1]);
        }
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
