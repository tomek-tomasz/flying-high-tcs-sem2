#include<iostream>
using namespace std;


int H[2000][2000];
bool B[2000][2000] = {0,};


int area_ij(int i, int j, int k, int age, int m, int n){
    B[i][j] = 1;
    if(H[i][j]>age) return 0;
    int area = 1;
    if(i+1<n && !B[i+1][j] && H[i+1][j]<= age) area += area_ij(i+1, j, k-area, age, m, n);
    if(area>=k) return k;
    if(i-1>=0 && !B[i-1][j] && H[i-1][j]<= age) area += area_ij(i-1, j, k-area, age, m, n);
    if(area>=k) return k;
    if(j+1<m && !B[i][j+1] && H[i][j+1]<= age) area += area_ij(i, j+1, k-area, age, m, n);
    if(area>=k) return k;
    if(j-1>=0 && !B[i][j-1] && H[i][j-1]<= age) area += area_ij(i, j-1, k-area, age, m, n);
    if(area>=k) return k;
    return area;
}

bool check(int k, int age, int m, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(B[i][j]) continue;
            else if(area_ij(i,j,k,age,m,n)>=k){
                return true;
            }
        }
    }
    return false;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string a1,a2;
    int z, n, m, k;
    cin>>z;
    while(z--){
        cin>>n>>m>>k;
        //cout<<n<<m<<k<<"\n";
        int age=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin>>H[i][j];
                //cout<<H[i][j]<<" ";
                if(age < H[i][j]) age = H[i][j];
            }
            //cout<<"\n";
        }
        //cout<<age<<"\n";
        int l=0,r=age;
        // for(int i=0; i<n; i++){
        //     for(int j=0; j<m; j++){
        //         cout<<B[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        while(l<r){
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    B[i][j]=0;
                }
            }
            int guess = (l+r)/2;
            if(check(k, guess, m ,n)) r = guess;
            else l = guess + 1; 
        }
        cout<<r<<"\n";
    }
}
