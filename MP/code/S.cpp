//
// Created by tomek on 5/19/26.
//

/*

mediana z median magiczne 5

dzielimy tablice na piatki i znajdujemy srodkowy(3) element
(srodkowe elementy mozemy przestawic na poczateek)
albo mozna podzielic tablice na 5 czesci
i pierwsza piatka to 5 eleementow pierwszych z poszczegolnych fragmentow
druga piatka to drugie elementy itd
to troche lepsze bo potem partition musi mniej robic




kth(k,n,T){
    dziel na 5
    wybierz srodek
    v = kth(n/10,n/5,T)(albo te miejsce w tablicy ktore ma akurat srodki)
    partition(v);
    return kth( tej tablicy ktora ma sens)

to jest liniowe?

T(n) = c*n + T(n/5) + T(3*n/4)?

*/
#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

constexpr int max_n = 5000000;
int T[max_n];


pair<int, int> partition(int start, int end, int pivot) {

    int i = start;
    int j = start;
    int k = end;

    while (j <= k) {
        if (T[j] < pivot) {
            swap(T[i], T[j]);
            i++;
            j++;
        } else if (T[j] > pivot) {
            swap(T[j], T[k]);
            k--;
        } else {
            j++;
        }
    }

    return {i,k};
}



int kth(int start, int end, int k) {
    while (true) {
        int n = end - start + 1;

        if (n <= 15) {
            sort(T + start, T + end + 1);
            return T[start + k - 1];
        }

        int medians_count = 0;

        for (int i = start; i <= end; i += 5) {
            int group_size = min(5, end - i + 1);

            sort(T + i, T + i + group_size);

            int median_idx = i + group_size / 2;

            swap(T[start + medians_count], T[median_idx]);
            medians_count++;
        }

        int pivot = kth(start, start + medians_count - 1, medians_count / 2 + 1);

        auto [i, j] = partition(start, end, pivot);

        int less_count = i - start;
        int eq_count = j - i + 1;

        if (k <= less_count) {
            end = i - 1;
        } else if (k <= less_count + eq_count) {
            return pivot;
        } else {
            start = j + 1;
            k -= (less_count + eq_count);
        }
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, k;
    cin>>z;
    while(z--) {
        cin>>n>>k;
        for (int i = 0; i < n; ++i) {
            cin>>T[i];
        }
        cout<<kth(0, n - 1, k) << '\n';
    }
}


