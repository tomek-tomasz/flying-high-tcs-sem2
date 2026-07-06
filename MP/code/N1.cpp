//
// Created by tomek on 5/14/26.
//

#include <algorithm>
#include<iostream>
#include <climits>
#include <list>
#include <queue>
using namespace std;

constexpr int max_vertices = 1000000;

pmr::vector<list<int>> graph(max_vertices);
pmr::vector<vector<int>> year_courses(max_vertices);
int in_degree[max_vertices]{};
int year[max_vertices];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, m, a, b;
    char trash;
    cin>>z;
    while(z--) {
        int index = 0;
        int max_year = 1;
        cin>>n>>m;
        for (int i = 0; i < n; ++i) {
            in_degree[i] = 0;
            graph[i].clear();
            year_courses[i].clear();
            year[i] = 1;
        }
        year_courses[n].clear();
        for (int i = 0; i < m; ++i) {
            cin>>a>>trash>>b;
            a--;
            b--;
            graph[a].push_back(b);
            in_degree[b]++;
        }
        queue<int> queue;
        for (int v = 0; v < n; ++v) {
            if (in_degree[v] == 0) {
                year[v] = 1;
                year_courses[1].push_back(v);
                queue.push(v);
            }
        }
        while (!queue.empty()) {
            int w = queue.front();
            queue.pop();
            ++index;
            for (int c: graph[w]) {
                in_degree[c]--;
                if (in_degree[c] == 0) {
                    queue.push(c);
                    year[c] = year[w] + 1;
                    year_courses[year[c]].push_back(c);
                    if (year[c] > max_year) max_year = year[c];
                }
            }
        }
        if (index < n)    cout<<"NIE\n";
        else{
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

}