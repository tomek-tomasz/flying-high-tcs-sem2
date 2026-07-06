//
// Created by tomek on 4/14/26.
//


/*
hashujemy wirusy i sprawdzamy jak beda takie
same wartosci np na dwoch funkcjach hashujacych
to wtedy im wierzymy i zwracamy ze sa takie same
jesli tak nie jest to sprawdzamy rekurencyjnie
w polowie liczymy tak samo funkcje hashujace odpowiednich przedzialow
jesli ciagle bedzie sie roznic tylko na jednym z nich to zwracamy
ze jest dokladnie jedna roznica
jesli kiedykolwiek pojawia sie dwie roznice to
wtedy na obu sie wywolujemy reukurencyjnie (split)
i mamy cztery przedzialy na raz
jesli kiedykolwiek w ktorymkowiek miejscu znowu beda dwie roznice
to wtedy wiemy ze mamy co najmniej 3 roznice zatem konczymy program
jesli nie to wiemy ze mamy dokladnie 2 roznice



jak sprawdzic o ile sie znakow rozni?

licze sobie hashe prefiksow i zapamietuje w tablicy
dla kazdego wirusa i tego co przychodzi
potem dzialam rekurencyjnie
sprawdzam w polowie prefiks i sufiks
jesli mam po obu stronach
hash sufiksu licze tak ze mam caly hash i odejmuje hash do pewnego elementu

*/

#include<iostream>
using namespace std;

int N = 49157;
int p = 37;
unsigned int P[10000];


void polynomial_hash(int k, const string &virus, unsigned int* hash) {
    hash[0] = virus[0];
    for (int i = 1; i < k; ++i) hash[i] = (hash[i-1] * p + virus[i]);
}

unsigned int hash_value( unsigned int* hash, int a, int b) {   // c_a * p^(b-a) + c_(a+1) * p^(b-a-1) + ... + c_(b-1) * p + c_b
    if (a == 0) return hash[b];
    unsigned int to_subtract = hash[a-1];                   // c_0 * p^(a-1) + ... + c_(a-1)
    unsigned int result = hash[b];                          // c_0 * p^b + ...+ c_(a-1) * p^(b-a+1) + ... + c_b
    to_subtract *= P[b-a+1];                                // c_0 * p^b + ... + c_(a-1) * p^(b-a+1)
    //to_subtract %= N;
    result = (result - to_subtract);                                  // c_a * p^(b-a) + ... + c_b
    return result;
}

int compare_recursive( int start, int end, unsigned int* lab_hash, unsigned int* hash, int current_difference) {
    if (hash_value(hash, start, end) == hash_value( lab_hash, start, end)) return 0;
    if (start == end) return 1;
    int middle = (start + end) / 2;
    int left_start = start, left_end = middle, right_start = middle + 1, right_end = end;
    unsigned int hash_left = hash_value( hash, left_start, left_end);
    unsigned int lab_hash_left = hash_value( lab_hash, left_start, left_end);
    unsigned int hash_right = hash_value(hash, right_start, right_end);
    unsigned int lab_hash_right = hash_value(lab_hash, right_start, right_end);
    if (hash_left == lab_hash_left) return compare_recursive(middle+1, end, lab_hash, hash, current_difference);
    if (hash_right == lab_hash_right)   return compare_recursive(start, middle, lab_hash, hash, current_difference);
    if (current_difference > 0) return 3;
    int left_difference = compare_recursive(left_start, left_end, lab_hash, hash, current_difference + 1);
    int right_difference = compare_recursive(right_start, right_end, lab_hash, hash, current_difference + 1);
    if (left_difference + right_difference == 2) return 2;
    return 3;
}

int compare(int k, unsigned int* lab_hash, unsigned int* hash) {
    return compare_recursive(0, k-1, lab_hash, hash, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    P[0] = 1;
    for (int i=1; i<10000 ; i++)    P[i] = p*P[i-1];

    int z, n, k, m;
    cin>>z;
    while(z--) {
        cin>>n>>k;
        string virus_to_add;
        unsigned int lab_hash[n][k];
        for (int i = 0; i < n; ++i) {
            cin>>virus_to_add;
            polynomial_hash(k, virus_to_add, lab_hash[i]);
        }

        cin>>m;
        string virus;
        unsigned int hash[k];
        unsigned int lab_added_hash[m][k];
        int add_counter = 0;
        int the_same, off_by_one, off_by_two;
        for (int i = 0; i < m; ++i) {
            the_same = 0, off_by_one = 0, off_by_two = 0;
            cin>>virus;
            polynomial_hash(k, virus, hash);
            for (int j = 0; j < n; ++j) {
                int difference = compare(k, lab_hash[j], hash);
                if (difference == 0) the_same++;
                else if (difference == 1) off_by_one++;
                else if (difference == 2) off_by_two++;
            }
            for (int j = 0; j < add_counter; ++j) {
                int difference = compare(k, lab_added_hash[j], hash);
                if (difference == 0) the_same++;
                else if (difference == 1) off_by_one++;
                else if (difference == 2) off_by_two++;

            }
            if (the_same == 0 && off_by_one == 0 && off_by_two == 0) {
                for (int l = 0; l < k; ++l) lab_added_hash[add_counter][l] = hash[l];
                add_counter++;
            }
            cout<<the_same<<' '<<off_by_one<<' '<<off_by_two<<'\n';
        }
    }
}










