#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned short us;

int n, m, p, k;

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
        } else {
            n = 1000, m = 10000, p = 50000, k = 300;
        }
    }

    FILE *data = fopen(argv[1], "r");
    if (data == NULL) {
        perror("could not open the file\n");
        exit(3);
    }
    if (fgets(A, sizeof(A), data) == NULL) {
        perror("could not read the file\n");
        exit(4);
    }

    FILE *output = fopen(argv[3], "w");
    if (output == NULL) {
        perror("could not open the file\n");
        exit(5);
    }

    us *ans;
    ans = (us *)malloc(sizeof(us) * (m * k));
    short left;
    for (; fgets(line, sizeof(line), data) != NULL;) {
        left = -1;
        for (int i = 0; i < m; i++) {
            if (A[i] == line[i]) {
                int dif = i - (left + 1);
                if (dif > k - 1) {
                    dif = k - 1;
                    left++;
                }
                ans[(left + 1) * k + dif]++;
            } else {
                left = i;
            }
        }
    }
    for (int i = 0; i < m - 1; i++) {
        for (int j = 1; j < k; j++) {
            ans[(i + 1) * k + j - 1] += ans[i * k + j];
        }
    }
    short l, s;
    for (; fscanf(range, "%hd, %hd/n", &l, &s) != EOF;) {
        fprintf(output, "%d, %d, %d\n", l, s, ans[l * k + s - 1]);
    }
    free(ans);

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
