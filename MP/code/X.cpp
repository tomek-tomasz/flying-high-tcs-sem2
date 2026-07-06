//
// Created by tomek on 6/2/26.
//


/*
to jest problem np
generujemy sobie permutacje rekurencyjnie jakos?

f(T,n,k)
for i = k...n-1
swap T[i], T[k]
if(cos co policzylismy dla danych k przedmiotow usatlonych
< od najlepszego co dotychczas policzylismy)
f(T,n,k+1)
swap T[i], T[k]


potrzebujemy funkcji ktora ocenia czy dane permutacje sa zle
tzn czy mozemy juz zakonczyc rekursje i odrzucic permutacje


mamy k elementow ustalonych
i liczymy dla nich przestoje
dodajemy sume reszty na maszynie A + min(b_i + c_i) i>k
sume reszy na maszynie B + min(c_i) gdzie i>k
sume reszty na maszynie C


mozna to jeszcze poprawic sortujac po oczekiwanych
ograniczeniach dolnych
i wywolywac od mniejszego do wiekszego
wiecej bedziemy wtedy pomijac permutacji
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long best_time;
vector<int> best_order;
vector<int> current_order;
vector<long long> A, B, C;
int n;

struct Branch {
    int index;
    long long lb;
    long long ca, cb, cc;
    bool operator<(const Branch& other) const {
        return lb < other.lb;
    }
};

void solve(int k, long long ca, long long cb, long long cc) {
    if (k == n) {
        if (cc < best_time) {
            best_time = cc;
            best_order = current_order;
        }
        return;
    }

    vector<Branch> branches;
    branches.reserve(n - k);

    for (int i = k; i < n; ++i) {
        int job = current_order[i];
        long long nca = ca + A[job];
        long long ncb = max(nca, cb) + B[job];
        long long ncc = max(ncb, cc) + C[job];

        long long lb = ncc;

        if (k + 1 < n) {
            long long sum_a = 0, sum_b = 0, sum_c = 0;
            long long min_bc = 1e18, min_c = 1e18;

            for (int j = k; j < n; ++j) {
                if (i == j) continue;
                int rem_job = current_order[j];
                sum_a += A[rem_job];
                sum_b += B[rem_job];
                sum_c += C[rem_job];
                min_bc = min(min_bc, B[rem_job] + C[rem_job]);
                min_c = min(min_c, C[rem_job]);
            }

            long long lb1 = nca + sum_a + min_bc;
            long long lb2 = ncb + sum_b + min_c;
            long long lb3 = ncc + sum_c;

            lb = max({lb1, lb2, lb3, ncc});
        }

        if (lb < best_time) {
            branches.push_back({i, lb, nca, ncb, ncc});
        }
    }

    sort(branches.begin(), branches.end());

    for (const auto& br : branches) {
        if (br.lb >= best_time) continue;
        swap(current_order[k], current_order[br.index]);
        solve(k + 1, br.ca, br.cb, br.cc);
        swap(current_order[k], current_order[br.index]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z;
    if (cin >> z) {
        while (z--) {
            cin >> n;
            A.resize(n);
            B.resize(n);
            C.resize(n);
            current_order.resize(n);
            for (int i = 0; i < n; ++i) {
                cin >> A[i] >> B[i] >> C[i];
                current_order[i] = i;
            }

            best_time = 2e18;
            solve(0, 0, 0, 0);

            cout << best_time << "\n";
            for (int i = 0; i < n; ++i) {
                cout << best_order[i] + 1 << (i == n - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}