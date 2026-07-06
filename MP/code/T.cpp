//
// Created by tomek on 5/19/26.
//



/*


Dla kazdego liscia licze odleglosc wazona do roota
z tych lisci ktore sa ujsciami to nic juz nie robie
sortuje osobno zrodla i ujscia w sensie od 1..t i t+1...2t
a jesli chodzi o zrodla to wszysstkie konflikty dzieja
sie na granicy
tzn najpierw licze dystans
5 5 7 7 7 8
i potem ida konflikty jednogodzinne
5 6 7 8 9 10



sortujemy tak

piszemy zapisujemy liczbe w systemie o podstawie n
i wtedy mamy co najwyzej trzy cyfry

i sortujemy pozycyjnie
to znaczy mamy liczbe x w formie

x/n^2 | x/n % n | x % n

i od najmniej znaczacego czyli od prawego
robimy count sort
po k-tej cyfrze
tzn mam tablice P[n]
potem licze ile razy sie w tablicy do posortowania pojawia dana cyfra
i zapisuje w P
no i potem licze sumy prefiksowe tego co policzylem
no i wtedy przechaddzam sie po tablicy do posortowania
mam nowa tasblice posortowana
i wiem w ktorych indeksach mam postawic dany element
np 0 pojawia sie 3 razy
potem 1 pojawia sie 4 razy
wiec w P mam 0,3,7
tzn najpierw pierwsze 3 beda 0
potem nastepne 4 beda jedynki

jak znajde liczbe ktora ma 0 to daje ja jak pierwsza i zwiekszam P[0]++
i jak znajde ja drugi raz to daje w indeks P[0] i zwiekszam

*/



#include<algorithm>
#include<iostream>
#include <queue>
using namespace std;



constexpr int max_vertices = 2000000;
vector<pair<int, int>> tree[max_vertices];
bool visited[max_vertices]{};

int dist[max_vertices];
int sorted[max_vertices];
int count_digits[max_vertices]{};



void dfs(int vertex) {
    for (auto edge : tree[vertex]) {
        int child = edge.first;
        if (!visited[child]) {
            int weight = edge.second;
            dist[child] = dist[vertex] + weight;
            visited[child] = true;
            dfs(child);
        }
    }
}

void radix_sort(int start, int t, int n){
    for (int p = 0; p < 3; ++p) {
        for (int i = start; i < start + t; ++i) {
            int digit = dist[i];
            for (int j = 3 - p; j < 3; j++) {
                digit /= n;
            }
            digit %= n;
            count_digits[digit]++;
        }
        for (int i = 1; i < n; ++i) {
            count_digits[i] += count_digits[i-1];
        }
        for (int i = start + t - 1; i >= start; --i) {
            int digit = dist[i];
            for (int j = 3 - p; j < 3; j++) {
                digit /= n;
            }
            digit %= n;
            sorted[start + --count_digits[digit]] = dist[i];
        }
        for (int i = start; i < start + t; ++i) {
            dist[i] = sorted[i];
        }
        fill_n(count_digits,n,0);
    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, t, n, a, b, c;
    cin>>z;
    while(z--) {
        cin>>t>>n;
        fill_n(visited, n, false);
        for (int i = 0; i < n; ++i) {
            tree[i].clear();
        }
        for (int i = 0; i < n-1; ++i) {
            cin>>a>>b>>c;
            tree[a].emplace_back(b,c);
            tree[b].emplace_back(a,c);
        }
        dist[0] = 0;
        visited[0] = true;
        dfs(0);
        radix_sort(1, t, n);
        radix_sort(t + 1, t, n);

        for (int i = 1; i <= t ; ++i) {
            cout<<dist[i]<<' ';
        }
        cout<<'\n';

        for (int i = 1; i <= t; ++i) {
            cout<<dist[t + i]<<' ';
        }
        cout<<'\n';
        for (int i = 2; i <= t ; ++i) {
            if (dist[i-1] >= dist[i]) {
                dist[i] = dist[i-1] + 1;
            }
        }
        int result = 1;
        for (int i = 1; i <= t; ++i) {
            if (dist[i] + dist[2*t + 1 - i] + 1 > result) {
                result = dist[i] + dist[2*t + 1 - i] + 1;
            }
        }
        cout<<result;
        cout<<'\n';



    }


}