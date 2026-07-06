//
// Created by tomek on 3/24/26.
//



/*
Algorytm dwayera jak na wykladzie mam pseudokod
robimy rotacje i przegladamy w petli cale drzewo
*/


/*
while (p  head) do
if (p = NULL) then // wróć do poprzednika
p := q;
q := NULL;
else
zbadaj(p);
// idziemy dalej ZAWSZE wzdłuż p->left,
// ale wychodząc rotujemy linki
tmp := left(p);
left(p) := right(p);
right(p) := q;
q := p;
p := tmp;
end.

*/




#include<iostream>
using namespace std;
struct node {
    int left;
    int right;
};


void Dwyer(node tree[], int n, int r) {
    int last_out = n;
    int p = r;
    int q = n;
    while (p != n) {
        if (p == -1) {
            p = q;
            q = -1;
        }else {
            if (p != last_out) {
                cout<<p+1<<' ';
                last_out = p;
            }

            //cout<<"\nleft: "<<tree[p].left;
            //cout<<"\nright: "<<tree[p].right;
            int temp = tree[p].left;
            tree[p].left = tree[p].right;
            tree[p].right = q;
            q = p;
            p = temp;
        }
    }
    cout<<'\n';

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n, r;
    cin>>z;
    while(z--) {
        cin>>n>>r;
        r--;
        auto tree = new node[n];
        for (int i=0; i<n; i++) {
            cin>>tree[i].left>>tree[i].right;
            tree[i].left--;
            tree[i].right--;

        }
        Dwyer(tree, n, r);
        delete[] tree;
    }
}

