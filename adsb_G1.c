#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int model, i, j, dif, left;
short l, s;

char line[10000 + 2];
char A[10000 + 2];
FILE *range, *data, *output;

int main(int argc, char **argv) {
    if (argc != 4) {
        perror("the number of command line arguments should be three\n");
        exit(1);
    }

    clock_t start, end;
    start = clock();

    range = fopen(argv[2], "r");
    if (range == NULL) {
        perror("could not open the file\n");
        exit(2);
    }

    if (fgets(line, sizeof(line), range) != NULL) {
        if (line[5] == '1') {
            model = 1;
        } else {
            model = 2;
        }
    }

    data = fopen(argv[1], "r");
    if (data == NULL) {
        perror("could not open the file\n");
        exit(3);
    }

    if (fgets(line, sizeof(line), data) != NULL) {
        for (int j = 0; j < 10000; j++) {
            A[j] = line[j];
        }
    }

    output = fopen(argv[3], "w");
    if (output == NULL) {
        perror("could not open the file\n");
        exit(4);
    }

    if (model == 1) {
        short *ans = (short *)malloc(sizeof(short) * 80000);
        for (; fgets(line, sizeof(line), data) != NULL;) {
            left = -1; // 最後に回答が違った場所
            for (i = 0; i < 10000; i++) {
                if (A[i] == line[i]) {
                    dif = i - (left + 1); // 何個の回答が連続して同じか
                    if (dif > 7) {
                        dif = 7;
                        left++;
                    }
                    ans[(left + 1) * 8 + dif]++; // ans[l + 1][dif]++にする
                } else {
                    left = i;
                }
            }
        }
        for (i = 0; i < 9999; i++) {
            for (j = 1; j < 8; j++) {
                ans[(i + 1) * 8 + j - 1] += ans[i * 8 + j];
            }
        }
        for (; fscanf(range, "%hd, %hd\n", &l, &s) != EOF;) {
            fprintf(output, "%hd, %hd, %hd\n", l, s, ans[l * 8 + s - 1]);
        }
        free(ans);
    } else {
        short *ans = (short *)malloc(sizeof(short) * 3000000);
        for (; fgets(line, sizeof(line), data) != NULL;) {
            left = -1;
            for (i = 0; i < 10000; i++) {
                if (A[i] == line[i]) {
                    dif = i - (left + 1);
                    if (dif > 299) {
                        dif = 299;
                        left++;
                    }
                    ans[(left + 1) * 300 + dif]++;
                } else {
                    left = i;
                }
            }
        }
        for (i = 0; i < 9999; i++) {
            for (j = 1; j < 300; j++) {
                ans[(i + 1) * 300 + j - 1] += ans[i * 300 + j];
            }
        }
        for (; fscanf(range, "%hd, %hd\n", &l, &s) != EOF;) {
            fprintf(output, "%hd, %hd, %hd\n", l, s, ans[l * 300 + s - 1]);
        }
        free(ans);
    }

    fclose(data);
    fclose(range);
    fclose(output);

    end = clock();

    printf("clock: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
