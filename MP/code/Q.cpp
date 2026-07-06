//
// Created by tomek on 5/12/26.
//



/*
Merge sort
dwie tablice - dzielimy nasza tablice
na dwa ciagle i rekurencyjnie stalamy


liczymy inwersje w momencie scalania
to znaczy rekurencyjnie zwracam ze w danym
segmencie bylo iles inwersji
i teraz w trakcie przepisywania licze
ile takich i zeby byla inwersja
pomiedzy segmentami


trzymamy w jakiejs zmiennej z
ostatniego kandydata ktory
dla poprzedniego j (elementu prawego segmentu)
byl zly juz od momentu z
no i teraz dla nowego j nowy z bedzie nim lub po nim
co oznacza ze zmienna z przejdzie przez segment
tylko raz liniowo
*/

#include <iostream>
using namespace std;

constexpr int max_n = 1000000;
int height[max_n];
int pom[max_n];



long long merge_sort(int start, int end, int error) {
    if (start == end) return 0;
    int middle = (start + end) / 2;
    long long result = 0;
    result += merge_sort(start, middle, error);
    result += merge_sort(middle + 1, end, error);

    int z = start;
    for (int j = middle + 1; j <= end; ++j) {
        while (z <= middle && height[z] + error >= height[j]) {
            z++;
        }
        result += (middle - z + 1);
    }

    int i = start;
    int j = middle + 1;
    int k = start;



    while (i <= middle && j <= end) {
        if (height[i] >= height[j]) {
            pom[k++] = height[i++];
        } else {
            pom[k++] = height[j++];
        }
    }

    while (i <= middle) {
        pom[k++] = height[i++];
    }
    while (j <= end) {
        pom[k++] = height[j++];
    }
    for (int c = start; c <= end; ++c) {
        height[c] = pom[c];
    }
    return result;

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, k;
    cin>>z;
    while(z--) {
        cin>>n>>k;
        for (int i = 0; i < n; ++i) {
            cin>>height[i];
        }
        long long result = merge_sort(0, n-1, k);

        for (int i = 0; i < n; ++i) {
            cout<<height[i]<<' ';
        }
        cout<<'\n'<<result<<'\n';
    }
}


