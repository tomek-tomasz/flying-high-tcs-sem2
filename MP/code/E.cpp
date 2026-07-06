/*
Smerfetka to korzeń.
odległość od korzenia możemy liczyc rekurencyjnie:
odleglosc od korzenia to
odleglosc rodzica od korzenia + odleglosc moja od rodzica
wypisujemy w odpowiednim porzadku preorder postorder i inorder
znaczy no czas a nie odleglosc tak naprawde xd


f(v){
    policz dystans (z rodzica)
    ->PREORDER
    f(v->left)
    ->INORDER
    f(v->right)
    ->POSTORDER
}



ile smerfow mija moj dom idac do smerfetki
licze sume krawedzi w poddrzewie ukorzenionym we mnie



f(v){
    
    ->PREORDER
    f(v->left)
    ->INORDER
    f(v->right)
    
    policz dystans (z dzieci)
}

wypisz(){
    ->PREORDER
    wypisz(v->left)
    ->INORDER
    wypisz(v->right)   
    -POSTORDER
}

przy wyborze domku dla papa smerfa sprawdzam ktory jest dobry
uzywajac tych danych ktore juz mam
ja moge policzyc dla poddrzewa ile jest w nim smerfow sumujac
sume i mieszkanow
dla dwoch poddrzew moge tak a potem licze dopelnienie
przy wczytywaniu policz sobie sume wszystkich smerfow dla tego kroku

sprawdz(v){
    if(v->left.suma + v->left.mieszkancy > polowa smerfow){
        return zle
    }
    if(v->right.suma + v->right.mieszkancy > polowa smerfow){
        return zle
    }
    if(reszta > polowa smerfow){
        return zle
    }
    return dobrze
}




technicznie tablica node gdzie node ma 4 liczby
i lecisz
*/

#include<iostream>

struct node {
    int parent;
    int left;
    int right;
    short edge_weight;
    short weight;
};

using namespace std;

void solve(char order);


node tree[2000000];
int dist[2000000] = {0,};
int subtree[2000000] = {0,};




int measure(const int vertex) {
    if (tree[vertex].parent == -1) return tree[vertex].edge_weight;
    if (dist[vertex]>0) return dist[vertex];
    int my_dist = tree[vertex].edge_weight;
    my_dist += measure(tree[vertex].parent);
    return my_dist;
}

int count_subtree(const int vertex) {
    int left_subtree = 0;
    if (tree[vertex].left != -1)  left_subtree = count_subtree(tree[vertex].left) + tree[tree[vertex].left].weight;
    int right_subtree = 0;
    if (tree[vertex].right != -1)  right_subtree = count_subtree(tree[vertex].right) + tree[tree[vertex].right].weight;
    int my_subtree = left_subtree + right_subtree;
    subtree[vertex] = my_subtree;
    return my_subtree;
}

bool check_centroid(const int vertex, const int weight_sum) {
    int half = weight_sum/2;
    int left_sum = 0;
    if (tree[vertex].left != -1) left_sum = subtree[tree[vertex].left] + tree[tree[vertex].left].weight;
    if (left_sum > half) return false;
    int right_sum = 0;
    if (tree[vertex].right != -1) right_sum = subtree[tree[vertex].right] + tree[tree[vertex].right].weight;
    if (right_sum > half) return false;
    if (weight_sum - left_sum - right_sum - tree[vertex].weight > half) return false;
    return true;

}


void orderly_print_dist(const char order, const int vertex) {
    int my_dist = measure(vertex);
    if (order == 'R')   cout<<my_dist<<' ';
    if (tree[vertex].left != -1)   orderly_print_dist(order, tree[vertex].left);
    if (order == 'N')   cout<<my_dist<<' ';
    if (tree[vertex].right != -1)   orderly_print_dist(order, tree[vertex].right);
    if (order == 'O')   cout<<my_dist<<' ';
}

void orderly_print_subtree(const char order, const int vertex) {
    int my_subtree = subtree[vertex];
    if (order == 'R')   cout<<my_subtree<<' ';
    if (tree[vertex].left != -1)   orderly_print_subtree(order, tree[vertex].left);
    if (order == 'N')   cout<<my_subtree<<' ';
    if (tree[vertex].right != -1)   orderly_print_subtree(order, tree[vertex].right);
    if (order == 'O')   cout<<my_subtree<<' ';
}

bool orderly_centroid(const char order, const int vertex, const int weight_sum) {
    bool i_am_centroid = check_centroid(vertex, weight_sum);
    if (order == 'R' && i_am_centroid) {
        cout<<vertex+1;
        return true;
    }
    if (tree[vertex].left != -1 && orderly_centroid(order, tree[vertex].left, weight_sum)) return true;
    if (order == 'N' && i_am_centroid) {
        cout<<vertex+1;
        return true;
    }
    if (tree[vertex].right != -1 && orderly_centroid(order, tree[vertex].right, weight_sum)) return true;
    if (order == 'O' && i_am_centroid) {
        cout<<vertex+1;
        return true;
    }
    return false;

}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z,n;
    string order;
    cin>>z;
    tree[0].parent=-1;
    while(z--) {
        cin>>n;
        int weight_sum=0;
        for (int i=0; i<n; i++) {
            cin>>tree[i].left>>tree[i].right>>tree[i].weight>>tree[i].edge_weight;
            tree[i].left--;
            tree[i].right--;
            if (tree[i].left >= 0)  tree[tree[i].left].parent = i;
            if (tree[i].right >= 0) tree[tree[i].right].parent = i;
            weight_sum+=tree[i].weight;
        }
        cin>>order;
        orderly_print_dist(order[1], 0);
        cout<<'\n';
        count_subtree(0);
        orderly_print_subtree(order[1], 0);
        cout<<'\n';
        orderly_centroid(order[1], 0, weight_sum);
        cout<<'\n';
    }
}




