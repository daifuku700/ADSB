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

// void *model1(void *arg) {
//     range *se = (range *)arg;
//     int start = se->start;
//     int end = se->end;

//     for (int i = start; i < end; i++) {
//         for (int h = 0; h < 8; h++) {
//             if (A[i + h] == line[i + h]) {
//                 ans[i][h]++;
//             } else {
//                 break;
//             }
//         }
//     }
//     return NULL;
// }

struct pair {
    us sum;
    us lazy_sum;
};

typedef struct {
    us start;
    us end;
} range;

int main(int argc, char **argv) {
    clock_t tic, toc;
    struct timespec start, end;

    if (argc != 4) {
        perror("the number of command line arguments should be three\n");
        exit(1);
    }

    tic = clock();
    clock_gettime(CLOCK_REALTIME, &start);

    FILE *rg = fopen(argv[2], "r");
    if (rg == NULL) {
        perror("could not open the file\n");
        exit(2);
    }
    if (fgets(line, sizeof(line), rg) != NULL) {
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
        us *ans = (us **)malloc(sizeof(us) * (m + 8));
        us right = 0, left = 0;
        for (; fgets(line, sizeof(line), data) != NULL;) {
            for (int i = 0; i < 8; i++) {
                if (A[i] == line[i]) {
                    ans[i]++;
                    right++;
                } else {
                    break;
                }
            }
            while (right < m) {
                left = right;
                for (int i = left; i < m; i++) {
                    if (A[i] == line[i]) {
                        break;
                    }
                }
            }
        }
        short l, s;
        for (; fscanf(rg, "%hd, %hd/n", &l, &s) != EOF;) {
            fprintf(output, "%d, %d, %d\n", l, s, ans[l][s - 1]);
        }
    } else if (model == 2) {
        us *b = (us *)malloc(sizeof(us) * (m + 1));
        b[0] = 0;
        for (; fgets(line, sizeof(line), data) != NULL;) {
            for (int i = 0; i < m; i++) {
                if (A[i] == line[i]) {
                    b[i + 1] = b[i] + 1;
                } else {
                    b[i + 1] = b[i];
                }
            }
            for (int i = 0; i < m; i++) {
                us left = i + 1, right = i + 300;
                us mid;
                while (left < right) {
                    mid = (right + left) / 2;
                    us tmp = b[mid] - b[i];
                    if (mid > b[mid] - b[i]) {
                        right = mid - 1;
                    } else if (tmp) {
                        left = mid;
                    }
                }
                printf("mid: %d\n", mid);
                return 0;
            }
        }
        short l, s;
        for (; fscanf(rg, "%hd, %hd/n", &l, &s) != EOF;) {
            // fprintf(output, "%d, %d, %d\n", l, s, ans[l][s - 1]);
        }
    }

    fclose(data);
    fclose(rg);
    fclose(output);

    toc = clock();
    clock_gettime(CLOCK_REALTIME, &end);
    printf("clock: %lf\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    printf("time: %lf\n",
           ((double)end.tv_sec - (double)start.tv_sec) +
               ((double)end.tv_nsec - (double)start.tv_nsec) / 1e9);
    return 0;
}
