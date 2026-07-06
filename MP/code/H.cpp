//
// Created by tomek on 3/24/26.
//
/*
dyskretna bijekcja drzewa narysowane -->> binarne

licze rekursywnie dla kazdego wierzcholka od lisci do korzenia
mam policzona dla dzieci najlepsza sciezke
ktora nie konczy sie w dziecku
i najlepsza sciezke co sie w nim konczy
zwracam najlepsza sciezke w poddrzewie
i najlepsza sciezke konczanca sie na tym dla ktorego licze

najlepsza sciezka to maksimum z tych co sa wewnetrzne
oraz tych co przechodza przez ten dla ktorego liczymy

glebokosci wierzcholkow policz aby wypisac sciezke pomiedzy a i b

zacyznam w tym ktory jest glebszy i lece po jego parentach
az nie beda tak glebocy jak ten drugi
od tego momentu ide jednoczesnie raz tak raz tak
az nie spotykam lowest common ancestor
*/


#include <algorithm>
#include<iostream>
#include <vector>

struct node {
    int parent;
    int child;
    int brother;
    int depth;
    int degree;
};

struct path {
    int start;
    int end;
    int weight;
};

using namespace std;

node tree[1000000];
path paths[1000000];
path best_current_path{};


void recursive_traversal(int vertex, int depth) {
    tree[vertex].depth = depth;
    if (tree[vertex].child != -1)
        recursive_traversal(tree[vertex].child, depth+1);
    if (tree[vertex].brother != -1)
        recursive_traversal(tree[vertex].brother, depth);
}


void best_path(int vertex) {
    if (tree[vertex].child != -1)
        best_path(tree[vertex].child);
    if (tree[vertex].brother != -1)
        best_path(tree[vertex].brother);
    int current_child = tree[vertex].child;
    vector<path> child_paths;
    while (current_child != -1) {
        child_paths.push_back(paths[current_child]);
        current_child = tree[current_child].brother;
    }
    path my_path{};
    if (tree[vertex].degree == 0) {
        my_path.start = vertex;
        my_path.end = vertex;
        my_path.weight = tree[vertex].degree+1;
    }
    else if (tree[vertex].degree == 1) {
        my_path.start = child_paths.front().start;
        my_path.end = vertex;
        my_path.weight = child_paths.front().weight;
    }
    else {
        path max_path = child_paths.front();
        int best_weight=0;
        for (path child_path : child_paths) {
            if (best_weight < child_path.weight) {
                best_weight = child_path.weight;
                max_path = child_path;
            }
        }
        path second_max_path{};
        best_weight = 0;
        for (path child_path : child_paths) {
            if (best_weight < child_path.weight && child_path.start != max_path.start && child_path.end != max_path.end) {
                best_weight = child_path.weight;
                second_max_path = child_path;
            }
        }
        int only_me_weight = tree[vertex].degree + 1;
        if (vertex == 0) only_me_weight--;
        int lengthened_weight = max_path.weight + tree[vertex].degree - 1;
        if (vertex == 0) lengthened_weight--;
        if ( lengthened_weight > only_me_weight) {
            my_path.start = max_path.start;
            my_path.end = vertex;
            my_path.weight = lengthened_weight;
        }else {
            my_path.start = vertex;
            my_path.end = vertex;
            my_path.weight = only_me_weight;
        }
        path real_max_path{};
        int connected_weight = max_path.weight + second_max_path.weight + tree[vertex].degree-3;
        if (vertex == 0) connected_weight--;
        if (my_path.weight < connected_weight) {
            real_max_path.start = max_path.start;
            real_max_path.end = second_max_path.start;
            real_max_path.weight = connected_weight;
        } else {
            real_max_path = my_path;
        }
        if (best_current_path.weight < real_max_path.weight) {
            best_current_path = real_max_path;
        }
    }
    paths[vertex].start = my_path.start;
    paths[vertex].end = my_path.end;
    paths[vertex].weight = my_path.weight;
}


void print_path(int start, int end) {
    vector<int> right_path;
    vector<int> left_path;
    int left_vertex = start;
    int right_vertex = end;
    if (tree[start].depth>tree[end].depth) {
        while (tree[left_vertex].depth != tree[right_vertex].depth) {
            left_path.push_back(left_vertex);
            left_vertex = tree[left_vertex].parent;
        }
    }else if (tree[start].depth<tree[end].depth) {
        while (tree[left_vertex].depth != tree[right_vertex].depth) {
            right_path.push_back(right_vertex);
            right_vertex = tree[right_vertex].parent;
        }
    }
    while (left_vertex != right_vertex) {
        left_path.push_back(left_vertex);
        right_path.push_back(right_vertex);
        left_vertex = tree[left_vertex].parent;
        right_vertex = tree[right_vertex].parent;
    }
    left_path.push_back(left_vertex);
    reverse(right_path.begin(), right_path.end());
    cout<<left_path.size()+right_path.size()<<' ';
    for (int element : left_path) cout<<element<<' ';
    for (int element : right_path) cout<<element<<' ';


}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z,n;
    cin>>z;
    tree[0].parent=-1;
    best_current_path.weight = 0;
    vector<int> order;
    order.reserve(1000000);
    while(z--) {
        best_current_path = {};
        cin>>n;
        for (int i = 0; i < n; i++) {
            cin >> tree[i].child >> tree[i].brother;
            tree[i].degree = 0;
            tree[i].parent = -1;
        }
        for (int i = 0; i < n; i++) {
            int c = tree[i].child;
            while (c != -1) {
                tree[c].parent = i;
                tree[i].degree++;
                c = tree[c].brother;
            }
        }
        tree[0].parent = -1;
        order.clear();
        order.push_back(0);
        tree[0].depth = 0;
        int head = 0;
        while (head < order.size()) {
            int u = order[head++];
            if (tree[u].child != -1) {
                tree[tree[u].child].depth = tree[u].depth + 1;
                order.push_back(tree[u].child);
            }
            if (tree[u].brother != -1) {
                tree[tree[u].brother].depth = tree[u].depth;
                order.push_back(tree[u].brother);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            int vertex = order[i];

            path max_path = {vertex, vertex, -1};
            path second_max_path = {vertex, vertex, -1};

            int current_child = tree[vertex].child;
            while (current_child != -1) {
                path cp = paths[current_child];
                if (cp.weight > max_path.weight) {
                    second_max_path = max_path;
                    max_path = cp;
                } else if (cp.weight > second_max_path.weight) {
                    second_max_path = cp;
                }
                current_child = tree[current_child].brother;
            }

            path my_path{};

            if (tree[vertex].degree == 0) {
                my_path.start = vertex;
                my_path.end = vertex;
                my_path.weight = 1;
            }
            else if (tree[vertex].degree == 1) {
                int only_me_weight = tree[vertex].degree + 1;
                if (vertex == 0) only_me_weight--;

                int lengthened_weight = max_path.weight + tree[vertex].degree - 1;

                if (lengthened_weight > only_me_weight) {
                    my_path.start = max_path.start;
                    my_path.end = vertex;
                    my_path.weight = lengthened_weight;
                } else {
                    my_path.start = vertex;
                    my_path.end = vertex;
                    my_path.weight = only_me_weight;
                }
                if (best_current_path.weight < my_path.weight) {
                    best_current_path = my_path;
                }
            }
            else {
                int only_me_weight = tree[vertex].degree + 1;
                if (vertex == 0) only_me_weight--;

                int lengthened_weight = max_path.weight + tree[vertex].degree - 1;
                if (vertex == 0) lengthened_weight--;

                if (lengthened_weight > only_me_weight) {
                    my_path.start = max_path.start;
                    my_path.end = vertex;
                    my_path.weight = lengthened_weight;
                } else {
                    my_path.start = vertex;
                    my_path.end = vertex;
                    my_path.weight = only_me_weight;
                }

                path real_max_path{};
                int connected_weight = max_path.weight + second_max_path.weight + tree[vertex].degree - 3;
                if (vertex == 0) connected_weight--;

                if (my_path.weight < connected_weight) {
                    real_max_path.start = max_path.start;
                    real_max_path.end = second_max_path.start;
                    real_max_path.weight = connected_weight;
                } else {
                    real_max_path = my_path;
                }

                if (best_current_path.weight < real_max_path.weight) {
                    best_current_path = real_max_path;
                }
            }
            paths[vertex] = my_path;
        }

        cout << best_current_path.weight << '\n';
        print_path(best_current_path.start, best_current_path.end);
        cout << '\n';
    }
}





