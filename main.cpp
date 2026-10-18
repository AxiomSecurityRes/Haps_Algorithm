#include <bits/stdc++.h>

#define T 1000000
#define x 3
#define y 3
#define SEL 9
#define Al 2

#define t_mod 618.22
#define t_y 1717.71
#define t_n 2174.28

using namespace std;

struct S{
    int a, b, c; //세 가지 속성
};

int cmp(int a, int b, int c) {
    if (!((a + b + c) % 3)) return 1;
    else return 0;
}

string BaseConv (int n, int b, int l) {
    n -= 1;
    if (n == 0) return "000";
    string tmp = "";
    while (1) {
        if (n < 1) break;
        int r = n % b;
        tmp += to_string(r);
        n /= b;
    }
    reverse(tmp.begin(), tmp.end());
    string ret;
    for (int i = 0; i < l - tmp.size(); i++) {
        ret += "0";
    }
    ret += tmp;
    return ret;
}

int HasCard[3][3][3];
int BruteForce(vector<S> cards) {
    for (int i = 0; i < 9; i++) {
        HasCard[cards[i].a][cards[i].b][cards[i].c] = true;
    }
    int hap = 0;
    // W.L.O.G. i < j < k
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            int a = (6 - cards[i].a - cards[j].a) % 3;
            int b = (6 - cards[i].b - cards[j].b) % 3;
            int c = (6 - cards[i].c - cards[j].c) % 3;
            if (HasCard[a][b][c]) hap++;
        }
    }
    return hap / 3;
}

// 합 못 찾으면: return -1

pair<int, double> BruteAl(vector<S> cards) {
    double steps = 0.0;
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 9; j++) {
            int a = (6 - cards[i].a - cards[j].a) % 3;
            int b = (6 - cards[i].b - cards[j].b) % 3;
            int c = (6 - cards[i].c - cards[j].c) % 3;
            steps += 3 * t_mod;
            if (HasCard[a][b][c]) {
                steps += t_y;
                return {0, steps};
            }
            steps += t_n;
        }
    }
    return {1, steps};
}

pair<int, double> OptAl (vector<S> cards) {
    double steps = 0.0;
    vector<pair<int,int>> order = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {4, 5}, {4, 6}, {4, 7}, {4, 8}, {5, 6}, {5, 7}, {5, 8}, {6, 7}, {6, 8}, {7, 8}};
    for (int i = 0; i < order.size(); i++) {
    	int xx = order[i].first;
    	int yy = order[i].second;

    	int a = (6 - cards[xx].a - cards[yy].a) % 3;
    	int b = (6 - cards[xx].b - cards[yy].b) % 3;
    	int c = (6 - cards[xx].c - cards[yy].c) % 3;
    	steps += 3 * t_mod;
    	if (HasCard[a][b][c]) {
    		steps += t_y;
    		return {0, steps};
		}
		steps += t_n;
	}
	return {1, steps};
}

int main() {
    // 빠른 입출력
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<int> dist(1, 3);

    int N = pow(x, y);
    vector<int> numbers(N);
    iota(numbers.begin(), numbers.end(), 1);

    vector<S> cards(SEL);
    vector<double> st(Al + 1, 0);
    vector<int> f(Al + 1, 0);
    vector<double> f_t(Al + 1, 0);

    for (int i = 0; i < T; i++) {
        memset(HasCard[0], 0, sizeof(HasCard));
        shuffle(numbers.begin(), numbers.end(), gen);
        for (int j = 0; j < SEL; j++) {
            int idx = numbers[j];
            string temp = BaseConv(idx, 3, 3);
            cards[j] = {temp[0] - 48, temp[1] - 48, temp[2] - 48};
        }

        BruteForce(cards);

        pair<int, double> tmp = BruteAl(cards);
        st[1] += tmp.second;
        f[1] += tmp.first;
        if (tmp.first) f_t[1] += tmp.second;

        pair<int, double> tmp2 = OptAl(cards);
        st[2] += tmp2.second;
        f[2] += tmp2.first;
        if (tmp2.first) f_t[2] += tmp2.second;
    }

    vector<string> name = {"", "Brute-Force", "Optimized Algorithm"};
    for (int i = 1; i <= Al; i++) {
        cout << "======" << name[i] << " ======\n";
        cout << "Average Steps: " << st[i] / T << "\n";
        cout << "Total Fails: " << f[i] << "\n";
        if (f[i]) cout << "Fail: Average Steps: " << f_t[i] / f[i] << "\n\n";
    }
    return 0;
}
