#include <vector>
#include <string>
#include <climits>
#include <iostream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> mat;
typedef vector<double> vd;
typedef vector<string> vs;
typedef vector<bool> vb;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;

template <class T1, class T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
    return is >> p.first >> p.second;
}

template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for (auto &i : v) {
        is >> i;
    }
    return is;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (auto &i : v) {
        os << i << " ";
    }
    return os;
}

#define pb push_back
#define pob pop_back
#define emb emplace_back
#define mp make_pair
#define fi first
#define se second
#define endl '\n'
#define sz(c) int(c.size())

#define all(c) begin(c), end(c)
#define rall(c) rbegin(c), rend(c)
#define rep(i, s, e) for (int i = (s); i < (e); i++)
#define repd(i, s, e) for (int i = s - 1; i >= (e); i--)
#define fore(i, c) for (auto &i : (c))

#define umin(a, b) (a) = min((a), (b))
#define umax(a, b) (a) = max((a), (b))
#define chmin(a, b) (((a) = min((a), (b))) == b)
#define chmax(a, b) (((a) = max((a), (b))) == b)

const int inf = INT_MAX / 2;
const ll infl = 1LL << 60;

int n, m, p, k;
vi l, s, A;
vector<vi> X;
int model = 0;

void input_data(int, char **);

int main(int argc, char **argv) {
    clock_t tic, toc;
    struct timespec start, end;
    tic = clock();
    clock_gettime(CLOCK_REALTIME, &start);
    input_data(argc, argv);

    if (model == 1) {
        vector<vi> ans(m, vi(8, 0));
// #pragma omp parallel for // 並列処理を試したい場合は、この行のコメントアウトを外してください
        rep(i, 0, m) {
            int ceil = min(8, m - i);
            rep(j, 0, n) {
                rep(l, 0, ceil) {
                    if (A[i + l] == X[j][i + l]) {
                        ans[i][l]++;
                    } else {
                        break;
                    }
                }
            }
        }
        FILE *file = fopen(argv[3], "w");
        rep(i, 0, p) {
            fprintf(file, "%d, %d, %d\n", l[i], s[i], ans[l[i]][s[i] - 1]);
        }
        fclose(file);
    }
    toc = clock();
    clock_gettime(CLOCK_REALTIME, &end);
    cout << "clock: " << (double)(toc - tic) / CLOCKS_PER_SEC << endl;
    cout << "time: "
         << ((double)end.tv_sec - (double)start.tv_sec) +
                ((double)end.tv_nsec - (double)start.tv_nsec) / 1e9
         << endl;
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
    X.resize(n);
    l.resize(p);
    s.resize(p);
    A.resize(m);
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

    for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
        X[i].resize(m);
        for (int j = 0; j < m; j++) {
            X[i][j] = line[j] - '0';
        }
    }
}
