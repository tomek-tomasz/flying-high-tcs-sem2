//
// Created by tomek on 5/15/26.
//

#include <algorithm>
#include<iostream>
#include <list>
#include <queue>
using namespace std;

constexpr int max_vertices = 1000000;

pmr::vector<list<int>> graph(max_vertices);
int state[max_vertices]{};
vector<int> top_order(max_vertices);

bool dfs(int v) {
    state[v] = 1;
    for (auto a: graph[v]) {
        if (state[a] == 1) return false;
        if (state[a] == 0) {
            if (!dfs(a)) return false;
        }
    }
    state[v] = 2;
    top_order.push_back(v);
    return true;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, m, a, b;
    char trash;
    cin>>z;
    while(z--) {

        cin>>n>>m;


        for (int i = 0; i < n; ++i) {
            graph[i].clear();
            state[i] = 0;
        }
        top_order.clear();


        for (int i = 0; i < m; ++i) {
            cin>>a>>trash>>b;
            a--;
            b--;
            graph[a].push_back(b);
        }

        bool possible = true;
        for (int v = 0; v < n; ++v) {
            if (state[v] == 0) {
                if (!dfs(v)) {
                    possible = false;
                    break;
                }
            }
        }
        if (!possible) {
            cout<<"NIE\n";
            continue;
        }


        reverse(top_order.begin(), top_order.end());


        vector<int> year(n, 1);
        int max_year = 1;

        for (int v : top_order) {
            for (int c : graph[v]) {
                if (year[v] + 1 > year[c]) {
                    year[c] = year[v] + 1;
                    if (year[c] > max_year) {
                        max_year = year[c];
                    }
                }
            }
        }

        vector<vector<int>> year_courses(max_year + 1);
        for (int i = 0; i < n; ++i) {
            year_courses[year[i]].push_back(i);
        }

        cout<<"TAK "<<max_year<<'\n';
        for (int i = 1; i <= max_year; ++i) {
            cout<<year_courses[i].size()<<' ';
            for (int j : year_courses[i]) {
                cout<<j + 1<<' ';
            }
            cout<<'\n';
        }



    }

}