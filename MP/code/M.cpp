//
// Created by tomek on 5/8/26.
//


#include <algorithm>
#include<iostream>
#include <climits>
#include <queue>
using namespace std;

constexpr int max_vertices = 1000000;

int parent[max_vertices];
int dist[max_vertices];
int dist_c[max_vertices];
int dist_banned[max_vertices];
bool visited[max_vertices]{};
bool banned[max_vertices]{};
vector<int> graph[max_vertices];

int d[max_vertices];
int dc[max_vertices];
int p[max_vertices];
int pc[max_vertices];


void bfs(int v) {
    queue<int> queue;
    queue.push(v);
    dist[v] = 0;
    parent[v] = -1;
    visited[v] = true;
    dist_banned[v] = dist_c[v];
    while (!queue.empty()) {
        auto w = queue.front();
        queue.pop();
        for (auto a : graph[w]) {
            if (!visited[a] && !banned[a]) {
                queue.push(a);
                dist[a] = dist[w] + 1;
                dist_banned[a] = min(dist_banned[w], dist_c[a]);
                parent[a] = w;
                visited[a] = true;
            }
            else if (!banned[a] && visited[a] && dist[a] == dist[w] + 1) {
                int x = min(dist_banned[w], dist_c[a]);
                if (x > dist_banned[a]) {
                    dist_banned[a] = x;
                    parent[a] = w;
                }
            }
        }
    }
}

void bfs_multiple(int n) {
    queue<int> queue;
    for (int v = 0; v < n; ++v) {
        if (banned[v]) {
            queue.push(v);
            dist_c[v] = 0;
            visited[v] = true;
        }
    }
    while (!queue.empty()) {
        auto w = queue.front();
        queue.pop();
        for (auto a : graph[w]) {
            if (!visited[a]) {
                queue.push(a);
                dist_c[a] = dist_c[w] + 1;
                visited[a] = true;
            }
        }
    }
}


void bfs_last(int v) {
    queue<int> queue;
    queue.push(v);
    d[v] = 0;
    p[v] = -1;
    visited[v] = true;

    while (!queue.empty()) {
        auto w = queue.front();
        queue.pop();

        for (auto a : graph[w]) {
            if (d[a] == INT_MAX && d[w] != INT_MAX && !banned[a]) {
                queue.push(a);
                d[a] = d[w] + 1;
                p[a] = w;
                visited[a] = true;
            }
            if (banned[a]) {
                if (d[w] != INT_MAX && dc[a] == INT_MAX) {
                    dc[a] = d[w] + 1;
                    pc[a] = w;
                    queue.push(a);
                    visited[a] = true;
                }
            }
            else {
                if (dc[w] != INT_MAX && dc[a] == INT_MAX) {
                    dc[a] = dc[w] + 1;
                    pc[a] = w;
                    if (!visited[a]) {
                        visited[a] = true;
                        queue.push(a);
                    }

                }
            }

        }
    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, m, x, y, k, a, b, v;
    int n = 0;
    cin>>z;
    while(z--) {
        cin>>n>>m>>x>>y>>k;
        for (int i = 0; i < n; ++i) {
            graph[i].clear();
            banned[i] = false;
            visited[i] = false;
            dist_c[i] = INT_MAX;
            dist_banned[i] = INT_MAX;
            dist[i] = INT_MAX;
        }
        --x;
        --y;
        for (int i = 0; i < k; ++i) {
            cin>>v;
            banned[v-1] = true;
        }
        for (int i = 0; i < m; ++i) {
            cin>>a>>b;
            --a;
            --b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        bfs_multiple(n);
        for (int i = 0; i < n; ++i) visited[i] = false;
        bfs(x);
        if (visited[y]) {
            cout<<"TAK "<<dist_banned[y]<<'\n';
            int pom = y;
            vector<int> path;

            while (pom != x) {
                path.push_back(pom);
                pom = parent[pom];
            }
            path.push_back(x);
            reverse(path.begin(),path.end());
            cout<<path.size()<<' ';
            for (int vertex: path)  cout<<vertex + 1<<' ';
            cout<<'\n';
        }else {
            for (int i = 0; i < n; ++i) {
                visited[i] = false;
                d[i] = INT_MAX;
                dc[i] = INT_MAX;
            }
            bfs_last(x);
            if (dc[y] != INT_MAX) {
                cout<<"TAK 0\n";
                int pom = y;
                vector<int> path;
                bool use_clean_path = false;
                while (pom != x) {
                    path.push_back(pom);
                    bool current_is_banned = banned[pom];
                    if (use_clean_path) {
                        pom = p[pom];
                    } else {
                        pom = pc[pom];
                    }
                    if (current_is_banned) {
                        use_clean_path = true;
                    }
                }
                path.push_back(x);
                reverse(path.begin(),path.end());
                cout<<path.size()<<' ';
                for (int vertex : path)  cout<<vertex + 1<<' ';
                cout<<'\n';
            }else cout<<"NIE\n";
        }
    }
}