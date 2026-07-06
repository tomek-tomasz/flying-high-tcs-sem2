/*
nawiasowaniaaa
INORDER 
PREORDER
najpierw znam w PREORDERZE korzen
wiec szukam go w inorderze i mam dwie czesci
znam zatem ich dlugosc i wtedy moge rekurencyjnie
rozbijac i wywolywac sie od tych czesci

INORDER
POSTORDER
dokladnie tak samo tylko korzen jest na koncu


PREORDER
POSTORDER
root znamy
ale znamy tez dziecko roota ktory 
tez jest gdzies i oddziela nam
fragmenty przez ktore mozemy przeprowadzac
rekurencje
i jazda 

trzeba myslec o tym czy postawic przecinek czy nie
jesli ktorakolwiek dlugosc fragmentu na ktory dzielimy 
jest 0 to nie stawiamy przecinka


zeby zlozonosc poprawic z kwadratowej 
to nie szukamy normalnie po kolei 
tylko szukamy raz od poczatku raz z konca
pierwszy - ostatni - drugi - przedostatni...

54312


12345
21534

12345
21453

*/

#include<iostream>

using namespace std;
int preorder[100000];
int inorder[100000];
int postorder[100000];


void load_order(const int n, const char order) {
    switch (order) {
        case 'R'    : {
            for (int i=0; i<n; i++) cin>>preorder[i];
            break;
        }
        case 'N'    : {
            for (int i=0; i<n; i++) cin>>inorder[i];
            break;
        }
        case 'O'    : {
            for (int i=0; i<n; i++) cin>>postorder[i];
            break;
        }
    }
}

int find_index(const int order[], const int value, const int start, const int end) {
    int i = start;
    int j = end;
    while (i<=j) {
        if (order[i] == value) return i;
        i++;
        if (order[j] == value) return j;
        j--;
    }
}

void preorder_inorder(const int pre_start, const int pre_end, const int in_start, const int in_end) {
    if (pre_start == pre_end) {
        cout<<"()";
        return;
    }
    bool has_child = false;
    const int parent = preorder[pre_start];
    const int index = find_index(inorder, parent, in_start, in_end);
    cout<<'(';
    if (in_start <= index - 1) {
        has_child = true;
        preorder_inorder(pre_start + 1, pre_start + index - in_start, in_start, index-1);
    }
    if (index + 1 <= in_end) {
        if (has_child)  cout<<',';
        preorder_inorder(pre_start + index - in_start + 1,pre_end,index+1, in_end);
    }
    cout<<')';
}

void postorder_inorder(const int post_start, const int post_end, int in_start, int in_end) {
    if (post_start == post_end) {
        cout<<"()";
        return;
    }
    bool has_child = false;
    const int parent = postorder[post_end];
    const int index = find_index(inorder, parent, in_start, in_end);
    cout<<'(';
    if (in_start <= index - 1) {
        has_child = true;
        postorder_inorder(post_start, post_start + index - in_start - 1, in_start, index - 1);
    }
    if (index + 1 <= in_end) {
        if (has_child)  cout<<',';
        postorder_inorder(post_start + index - in_start, post_end - 1,index + 1, in_end);
    }
    cout<<')';
}

void preorder_postorder(const int pre_start, const int pre_end, const int post_start, const int post_end) {
    if (pre_start == pre_end) {
        cout<<"()";
        return;
    }
    bool has_child = false;
    const int parent = preorder[pre_start + 1];
    const int index = find_index(postorder, parent, post_start, post_end);
    cout<<'(';
    if (post_start <= index) {
        has_child = true;
        preorder_postorder(pre_start + 1, pre_start + index - post_start + 1, post_start, index);
    }
    if (index + 1 <= post_end - 1) {
        if (has_child)  cout<<',';
        preorder_postorder(pre_start + index - post_start + 2, pre_end, index + 1, post_end - 1);
    }
    cout<<')';
}

void solve(const int n) {
    string first_order, second_order;
    cin>>first_order;
    load_order(n, first_order[1]);
    cin>>second_order;
    load_order(n, second_order[1]);

    if ((first_order[1] == 'R' && second_order[1] == 'N') || (first_order[1] == 'N' && second_order[1] == 'R'))
        preorder_inorder(0, n-1, 0, n-1);
    if ((first_order[1] == 'O' && second_order[1] == 'N') || (first_order[1] == 'N' && second_order[1] == 'O'))
        postorder_inorder(0, n-1, 0, n-1);
    if ((first_order[1] == 'R' && second_order[1] == 'O') || (first_order[1] == 'O' && second_order[1] == 'R'))
        preorder_postorder(0, n-1, 0, n-1);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z,n;
    cin>>z;
    while(z--) {
        cin>>n;
        solve(n);
        cout<<'\n';
    }
}

















