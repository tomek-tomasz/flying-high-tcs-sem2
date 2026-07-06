//
// Created by tomek on 5/7/26.
//

#include <iostream>
#include <vector>

using namespace std;

struct road {
    int to;
    bool permit;
    road(int n, bool p): to(n), permit(p) { }
};


constexpr int Max = 50000;
vector<road> graph[Max];
bool visited[Max];
bool changed[Max];




bool test(int v) {
    visited[v] = true;
    for (auto neighbour_road : graph[v]) {
        int w = neighbour_road.to;
        if (!visited[w]) {
            if (neighbour_road.permit && changed[v]) changed[w] = true;
            if (!neighbour_road.permit && !changed[v]) changed[w] = true;
            if (!test(w)) return false;
        }
        else {
            if (!neighbour_road.permit && changed[v] == changed[w]) return false;
            if (neighbour_road.permit && changed[v] != changed[w]) return false;
        }
    }
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, m, a, b;
    char c;
    cin>>z;

    bool permitted;
    while(z--) {
        cin>>n>>m;
        for (int i = 0; i < n; i++) {
            visited[i] = false;
            changed[i] = false;
            graph[i].clear();
        }
        for (int i=0; i<m; i++) {
            cin>>a>>b>>c;
            a--;
            b--;
            if (c=='+') permitted = true;
            else permitted = false;
            graph[a].emplace_back(b, permitted);
            graph[b].emplace_back(a, permitted);
        }
        if (!test(0)) cout<<"NIE";
        else {
            for (int i = 0; i < n; ++i) {
                if (changed[i]) cout<<i+1<<' ';
            }
        }
        cout<<'\n';
    }
}