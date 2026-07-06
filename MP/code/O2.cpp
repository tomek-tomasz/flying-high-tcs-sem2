//
// Created by tomek on 5/22/26.
//

#include <algorithm>
#include<iostream>
#include <queue>
#include <unordered_map>
using namespace std;

constexpr int max_vertices = 500000;
constexpr int max_edges = 600000;

vector<pair<int, int>> graph[max_vertices];
unordered_map<int, int> map[max_vertices];
vector<int> euler_cycle;

int in_degree[max_vertices]{};
int out_degree[max_vertices]{};
int next_edge[max_vertices]{};

int predecessor[max_edges];
int successor[max_edges];
bool visited[2 * max_edges]{};

int edge_u[max_edges];
int edge_v[max_edges];
bool in_h_path[max_edges];
vector<vector<int>> virtual_paths;



void dfs_edge(int vertex) {
    while (next_edge[vertex] < graph[vertex].size()) {
        auto edge_info = graph[vertex][next_edge[vertex]];
        int neighbour = edge_info.first;
        int edge_id = edge_info.second;
        next_edge[vertex]++;
        if (edge_id < max_edges && visited[edge_id]) {
            continue;
        }
        int next_vertex = neighbour;
        if (next_vertex >= max_vertices) {
            next_vertex -= max_vertices;
        }
        dfs_edge(next_vertex);
        euler_cycle.push_back(edge_id);
    }
}







int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, m, a, b, k, d, e, f;
    cin>>z;
    while(z--) {
        cin>>n>>m;
        euler_cycle.clear();
        for (int i = 0; i < n; ++i) {
            in_degree[i] = 0;
            out_degree[i] = 0;
            graph[i].clear();
            map[i].clear();
            next_edge[i] = 0;
        }
        for (int i = 0; i < m; ++i) {
            predecessor[i] = -1;
            successor[i] = -1;
            visited[i] = false;
            visited[i + max_edges] = false;
            in_h_path[i] = false;
        }
        for (int i = 0; i < m; ++i) {
            cin>>a>>b;
            a--;
            b--;
            graph[a].emplace_back(b,i);
            map[a][b] = i;
            edge_u[i] = a;
            edge_v[i] = b;
            out_degree[a]++;
            in_degree[b]++;
        }
        bool is_possible = true;


        cin>>k;
        for (int i = 0; i < k; ++i) {
            cin>>d>>e>>f;
            e--;
            f--;

            int last_edge = -1;
            if (is_possible && map[e].find(f) != map[e].end()) {
                last_edge = map[e][f];
            } else {
                is_possible = false;
            }

            for (int j = 0; j < d-2; ++j)   {
                cin>>e;
                e--;
                if (!is_possible) continue;
                if (map[f].find(e) == map[f].end()) {
                    is_possible = false;
                    continue;
                }
                int new_edge = map[f][e];
                if ((predecessor[new_edge] != -1 && predecessor[new_edge] != last_edge)
                    || (successor[last_edge] != -1 && successor[last_edge] != new_edge)) {
                    is_possible = false;
                    continue;
                    }
                successor[last_edge] = new_edge;
                predecessor[new_edge] = last_edge;
                last_edge = new_edge;
                f = e;
            }
        }

        for (int vertex = 0; vertex < n; ++vertex) {
            if (in_degree[vertex] != out_degree[vertex]) is_possible = false;
        }

        if (!is_possible) {
            cout<<"NIE\n";
            continue;
        }
        int edge_count = m;
        virtual_paths.clear();

        for (int i = 0; i < m; ++i) {
            if (predecessor[i] == -1 && successor[i] != -1) {
                vector<int> current_path;
                int curr = i;

                while (curr != -1) {
                    current_path.push_back(curr);
                    visited[curr] = true;
                    in_h_path[curr] = true;
                    edge_count--;
                    curr = successor[curr];
                }

                int start_vertex = edge_u[current_path.front()];
                int end_vertex = edge_v[current_path.back()];

                int virtual_edge_id = max_edges + static_cast<int>(virtual_paths.size());
                virtual_paths.push_back(current_path);

                graph[start_vertex].emplace_back(end_vertex + max_vertices, virtual_edge_id);
                edge_count++;
            }
        }

        for (int i = 0; i < m; ++i) {
            if (successor[i] != -1 && !in_h_path[i]) {
                is_possible = false;
            }
        }

        if (!is_possible) {
            cout << "NIE\n";
            continue;
        }


        int start_vertex = 0;
        for (int i = 0; i < n; ++i) {
            bool has_valid_edge = false;
            for (auto edge_info : graph[i]) {
                int edge_id = edge_info.second;
                if (edge_id >= max_edges || !visited[edge_id]) {
                    has_valid_edge = true;
                    break;
                }
            }
            if (has_valid_edge) {
                start_vertex = i;
                break;
            }
        }
        dfs_edge(start_vertex);

        if (euler_cycle.size() == edge_count) {
            cout<<"TAK ";
            reverse(euler_cycle.begin(), euler_cycle.end());
            for (int edge_id : euler_cycle) {
                if (edge_id < max_edges) {
                    cout<<edge_u[edge_id] + 1<<' ';
                }else {
                    for (auto edge: virtual_paths[edge_id - max_edges]) {
                        cout<<edge_u[edge] + 1<<' ';
                    }
                }

            }
        }
        else cout<<"NIE";
        cout<<'\n';
    }
}