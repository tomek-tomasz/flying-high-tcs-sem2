//
// Created by tomek on 5/22/26.
//

#include <algorithm>
#include<iostream>
#include <queue>
using namespace std;

constexpr int max_vertices = 500000;

vector<int> graph[max_vertices];
int in_degree[max_vertices]{};
int out_degree[max_vertices]{};
int next_edge[max_vertices]{};
bool visited[max_vertices]{};
vector<int> euler_cycle;


void dfs(const int vertex) {
    for (int i = next_edge[vertex]; i < graph[vertex].size(); ++i) {
        if (next_edge[vertex] == i) {
            next_edge[vertex]++;
            dfs(graph[vertex][i]);
            euler_cycle.push_back(vertex);
        }
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, m, a, b;
    cin>>z;
    while(z--) {
        cin>>n>>m;
        euler_cycle.clear();
        for (int i = 0; i < n; ++i) {
            in_degree[i] = 0;
            out_degree[i] = 0;
            next_edge[i] = 0;
            visited[i] = false;
            graph[i].clear();

        }
        for (int i = 0; i < m; ++i) {
            cin>>a>>b;
            a--;
            b--;
            graph[a].push_back(b);
            out_degree[a]++;
            in_degree[b]++;
        }
        bool is_possible = true;
        for (int vertex = 0; vertex < n; ++vertex) {
            if (in_degree[vertex] != out_degree[vertex]) is_possible = false;
        }
        dfs(0);
        if (euler_cycle.size() != m) is_possible = false;

        if (is_possible) {
            cout<<"TAK ";
            reverse(euler_cycle.begin(), euler_cycle.end());
            for (int vertex: euler_cycle) {
                cout<<vertex + 1<<' ';
            }
        }
        else cout<<"NIE";
        cout<<'\n';
    }
}