//
// Created by tomek on 5/5/26.
//


/*

P1

w zadaniu chodzi o znalezienie silnie
spojnych skladowych w griafie skierowanym

puszczamy dla kazdego wierzcholka
co nie byl jeszcze przegladany dfs
mamy jakies drzewa przegladu grafu
w sensie drzewo rozpinajace silnie spojnej skladowej
kazde z drzew przegladu sklada sie z silnie spojnych skladowych
zeby ten graf wreszcie podzielisc na te skladowe
to zaczynamy od roota ostatniego drzewa ktore dfs widzial
i przegladam graf G^op
i wtedy dostaje pierwsza spojna skladowa

aby bylo prosciej podczas wykonywania pierwszego dfsa
robie sobie vector wierzcholkow w postorderze
potem po zrobieniu pierwszej skladowej
patrze na ostatni nieodwiedzony wierzcholek w tym porzadku
i wywoluje sie na nim

moge sobie stworzyc tablice counter gidze przy odwiedzeniu wierzcholka
przy robieniu dfs2 licze ile odwiedzilem w konkretnej i-tej skladowej

no i to jest wynik


*/

//
// Created by tomek on 5/22/26.
//

#include<algorithm>
#include<iostream>
#include <queue>
using namespace std;

constexpr int max_vertices = 50000;


int next_edge[max_vertices]{};
bool visited[max_vertices]{};

int component_number[max_vertices];

int current_component = 0;

vector<int> graph[max_vertices];
vector<int> graph_op[max_vertices];
vector<int> vertices;
vector<int> component_size;




void dfs(const int vertex) {
    for (int i = next_edge[vertex]; i < graph[vertex].size(); ++i) {
        if (next_edge[vertex] == i) {
            next_edge[vertex]++;
            dfs(graph[vertex][i]);
        }
    }
    if (!visited[vertex]) {
        visited[vertex]= true;
        vertices.push_back(vertex);

    }
}


void dfs2(const int vertex) {
    for (int i = next_edge[vertex]; i < graph_op[vertex].size(); ++i) {
        if (next_edge[vertex] == i) {
            next_edge[vertex]++;
            dfs2(graph_op[vertex][i]);
        }
    }
    if (!visited[vertex]) {
        visited[vertex] = true;
        component_number[vertex] = current_component;
        component_size[current_component]++;
    }
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, m, a, b, s;
    cin>>z;
    while(z--) {
        cin>>n>>m;
        vertices.clear();
        component_size.clear();
        current_component = 0;
        for (int i = 0; i < n; ++i) {
            next_edge[i] = 0;
            visited[i] = false;
            graph[i].clear();
            graph_op[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            cin>>a>>b>>s;
            a--;
            b--;
            graph[a].push_back(b);
            graph_op[b].push_back(a);
        }


        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        reverse(vertices.begin(),vertices.end());
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
            next_edge[i] = 0;
        }

        for (int vertex : vertices) {
            if (!visited[vertex]) {
                component_size.push_back(0);
                dfs2(vertex);
                current_component++;
            }
        }

        for (int i = 0; i < n; ++i) {
            cout<<component_size[component_number[i]]-1<<' ';
        }

        cout<<'\n';

    }
}

