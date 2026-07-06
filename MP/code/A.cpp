#include<iostream>
using namespace std;

bool all_planks_nailed(pair<int,int> planks[], int nails[], int k, int m, int n){
    int l = 2*(m+n);
    int table[l] = {0,};
    for(int i=0; i<k; i++) table[nails[i]]=1;
    for(int i=1; i<l; i++) table[i] += table[i-1];
    for(int i=0; i<n; i++){
        if(planks[i].first==0){
            if(table[planks[i].second] == 0) return false;
        }
        else if(table[planks[i].second] - table[planks[i].first-1]==0) return false;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a1,a2;
    int z,n,m;
    cin>>z;
    while(z--){
        cin>>n>>m;
        pair<int,int> planks[n];
        for(int i=0; i<n; i++){
            cin>>planks[i].first>>planks[i].second;
            planks[i].first--;
            planks[i].second--;
        }
        int nails[m]; 
        for(int j=0; j<m; j++){
            cin>>nails[j];
            nails[j]--;
        }
        int l=0,r=m+1;
        bool is_legal;
        while(l<r){
            int k = (l+r)/2;
            is_legal = all_planks_nailed(planks, nails, k, m, n);
            if(is_legal) r = k;
            else l = k + 1;
        }
        if(r==m+1) cout<<"ERROR\n";
        else cout<<r<<"\n";

    }
}
