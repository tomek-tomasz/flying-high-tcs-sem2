//
// Created by tomek on 5/5/26.
//


/*

P2

tworze dwa grafy G i G^op jesli wierzcholek v+n jest G^op to w G jest v
jeden ma normalne krawedzie drugi ma krawedzie odwrotne normalne
specjalne krawedzie lacza odpowiednie normalne wiercholki

i wywoluje algorytm z P1 na tym grafie


wtedy dla kazdego wierzcholka dla ktorego numer skladowej jest taki
sam dla v i v+n to zmniejszam size od v

wtedy zwracam wszystkie numery[v+n]

*/

#include<algorithm>
#include<iostream>
#include <queue>
using namespace std;

constexpr int max_vertices = 100000;


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
        for (int i = 0; i < 2 * n; ++i) {
            next_edge[i] = 0;
            visited[i] = false;
            graph[i].clear();
            graph_op[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            cin>>a>>b>>s;
            a--;
            b--;
            if (s) {
                graph[a].push_back(b + n);
                graph_op[b + n].push_back(a);
                graph[b + n].push_back(a);
                graph_op[a].push_back(b + n);
            }else {
                graph[a].push_back(b);
                graph_op[b].push_back(a);
                graph[b + n].push_back(a + n);
                graph_op[a + n].push_back(b + n);
            }

        }


        for (int i = 0; i < 2 * n; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        reverse(vertices.begin(),vertices.end());
        for (int i = 0; i < 2 * n; ++i) {
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
            if (component_number[i] == component_number[i + n]) {
                component_size[component_number[i]]--;
            }
        }

        for (int i = 0; i < n; ++i) {
            cout<<component_size[component_number[i + n]]-1<<' ';
        }

        cout<<'\n';

    }
}



