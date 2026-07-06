//
// Created by tomek on 5/12/26.
//


/*
posortowane slizgacze


jak najmniejszy nasz jest lepszy
niz najmniejszy ich to wygrywam

jak najmniejszy nasz jest gorszy niz
najmniejszy ich to wtedy przegrywamy z ich najlepszym

jesli zaczynamy z remisem albo spotykamy remis
kiedy wczesniej nie bylo remisow lub juz wszystkie
wykorzystalismy to zapisujemy ile remisow

jesli przegrywamy lub mamy remis i wczesniej byl remis to
robimy "na skos" to znaczy nowy wygrywa z tym poprzednim
ktory remisowal z naszym
a naszego wykorzystujemy na najlepszego ktory jest


Quicksort
wybieram pivota
chce miec tablice taka zeby
wszystkie elementy mniejsze byly po lewej
od pivota a wszystkie wieksze od niego
byly po prawej

potem rekurencyjnie robie to samo dla tych
pozostalych segmentow

metoda chora (hoara)

najpierw pivota daje na koniec a potem
mam dwa wskazniki od poczatku i konca
i jak sa zle to je zamieniam
dopoki sie nie spotkaja te wskazniki

jak jest rowne pivotowi no to jakos losowo wstawiamy
raz tu raz tu


metoda zdrowa mniej bledotworcza lomuto

analizujemy i-ty element
mamy drugi wskaznik j
j ma taka wlasnosc ze przed j sa mniejsze od pivota
a pomiedzy i a j sa wieksze lub rowne od pivota
no i teraz iterujemy sie z i
no i jesli napotkany element jest wiekszy lub rowny
pivotowi to nic nie robimy
a jesli jest mniejszy od pivota to zamieniamy
z nastepnikiem j i iterujemy j


mozna to rozbudowac jednym wiecej wskaznikiem k
takim ze przed k sa elementy mniejsze od pivota
pomiedyz k a j mamy rowne pivotowi
a pomiedzy j a i mamy wikesze od pivota
no i teraz robie swap analogicznie
ale teraz gdy natrafiam na mniejszego robie rotacyjny
swap to znaczy mniejszy idzie na nastepnik k
nastepnik k idzie na nastepnik j
a nastepnik j idzie na miejsce ktore napotkalismy

na wiekszego to nic nie robie
a na rownego to zamieniamy
z nastepnikiem j i iterujemy j
potem iteruje i
*/


#include <iostream>
#include <random>
using namespace std;

constexpr int max_n = 1000000;
int H[max_n];
int J[max_n];

unsigned int get_random_number(unsigned int start, unsigned int end) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<unsigned int> distribution(start, end);
    return distribution(gen);
}


pair<int, int> partition(int start, int end, int* T, int pivot) {

    int i = start;
    int j = start;
    int k = end;

    while (j <= k) {
        if (T[j] < pivot) {
            swap(T[i], T[j]);
            i++;
            j++;
        } else if (T[j] > pivot) {
            swap(T[j], T[k]);
            k--;
        } else {
            j++;
        }
    }

    return {i,k};
}

void quicksort(int start, int end, int* T) {
    if (start >= end) return;

    unsigned int pivot_index = get_random_number(start, end);
    int pivot = T[pivot_index];

    auto indexes = partition(start, end, T, pivot);
    int i = indexes.first;
    int k = indexes.second;
    quicksort(start, i - 1, T);
    quicksort(k + 1, end, T);
}



/*
posortowane slizgacze


jak najmniejszy nasz jest lepszy
niz najmniejszy ich to wygrywam

jak najmniejszy nasz jest gorszy niz
najmniejszy ich to wtedy przegrywamy z ich najlepszym

jesli zaczynamy z remisem albo spotykamy remis
kiedy wczesniej nie bylo remisow lub juz wszystkie
wykorzystalismy to zapisujemy ile remisow

jesli przegrywamy lub mamy remis i wczesniej byl remis to
robimy "na skos" to znaczy nowy wygrywa z tym poprzednim
ktory remisowal z naszym
a naszego wykorzystujemy na najlepszego ktory jest
*/

long long profit(int n) {
    long long profit = 0;

    int h_start = 0, h_end = n - 1;
    int j_start = 0, j_end = n - 1;

    while (h_start <= h_end) {
        if (H[h_start] > J[j_start]) {
            profit++;
            h_start++;
            j_start++;
        }
        else if (H[h_end] > J[j_end]) {
            profit++;
            h_end--;
            j_end--;
        }
        else {
            if (H[h_start] < J[j_end]) {
                profit--;
            }

            h_start++;
            j_end--;
        }
    }
    return profit;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int z, n;
    cin>>z;
    while(z--) {
        cin>>n;
        for (int i = 0; i < n; ++i) {
            cin>>H[i];
        }

        for (int i = 0; i < n; ++i) {
            cin>>J[i];
        }

        quicksort(0, n-1, H);
        quicksort(0, n-1, J);

        for (int i = 0; i < n; ++i) {
            cout<<H[i]<<' ';
        }
        cout<<'\n';
        for (int i = 0; i < n; ++i) {
            cout<<J[i]<<' ';
        }
        cout<<'\n';


        cout<<20ll*profit(n)<<'\n';


    }
}



