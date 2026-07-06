//
// Created by tomek on 3/31/26.
//

/*
dla kazdego wierzcholka liczymy size tzn ile jest wierzcholkow w jego poddrzewie
jak dodaje i usuwam element to musze utrzymywac te wartosc

szukajac k-tego elementu zaczynam od roota i porownuje k do size dzieci
jesli po lewej jest wiecej niz k to ide tam
w przeciwnym wypadku zmniejszam k=k-size-1

test - szukamy wspolnego przodka i idziemy od niego w dol do a po lewej potem
liczymy size prawych dzieci lewych potomkow a potem
liczymy size lewych dzieci prawych potomkow

jesli nie ma a to szukamy z pierwszy ze z>a
to jest praktycznie wyszukiwanie binarne tylko
ze jesli rodzic jest wiekszy od a to nie interesuje nas prawe poddrzewo
a w przeciwnym wypadku nie interesuje nas rodzic i lewe poddrzewo
trzymaj sobie kandydata w zmiennej to se mozesz to zrobic iteracyjnie po prostu i lecisz

ciekawoskta mozna tez skracanym inorderem ze jak to nie ma sensu to znikam
*/
#pragma once


#include <iostream>
#include <iomanip>
using namespace std;

template<class T1, class T2>
class node {
public:
    node* parent = nullptr;
    node* left = nullptr;
    node* right = nullptr;
    int size = 1;
    int depth = 0;
    T1 key;
    T2 name;
    node()= default;
    node(T1 k, T2 n) {
        key = k;
        name = n;
    }
    T2 GetName(){return name;}

};
template<class T1, class T2>
ostream& operator<<(ostream& st, node<T1, T2>& a) {
    st<< setfill('0') << setw(9)<<a.key<<' '<<a.name<<'\n';
    return st;
}

template<class T1, class T2>
class map {
private:
    int count;
    node<T1, T2>* root = nullptr;
    void print_recursive(node<T1, T2>* vertex) {
        if (vertex->left != nullptr)
            print_recursive(vertex->left);
        cout<<*vertex;
        if (vertex->right != nullptr)
            print_recursive(vertex->right);
    }

    void update_size(node<T1, T2>* parent, bool subtract) {
        if (parent == nullptr) return;
        if (subtract) --parent->size;
        else ++parent->size;
        if (parent->parent != nullptr)  update_size(parent->parent, subtract);
    }

    void update_depth(node<T1, T2>* vertex) {
        --vertex->depth;
        if (vertex->left != nullptr) update_depth(vertex->left);
        if (vertex->right != nullptr) update_depth(vertex->right);
    }

    bool delet(node<T1, T2>* vertex) {
        if (vertex == nullptr) return false;

        if (vertex->left == nullptr && vertex->right == nullptr) {
            if (vertex->parent != nullptr) {
                if (vertex->parent->left == vertex) vertex->parent->left = nullptr;
                else vertex->parent->right = nullptr;
            } else root = nullptr;
            update_size(vertex->parent, true);
            delete vertex;
            count--;
            return true;
        }
        if (vertex->left != nullptr && vertex->right != nullptr) {
            node<T1, T2>* replacement = vertex;
            if (vertex->parent == nullptr || vertex->parent->left == vertex) {
                replacement = replacement->right;
                while (replacement->left != nullptr)   replacement = replacement->left;
            }
            else {
                replacement = replacement->left;
                while (replacement->right != nullptr)   replacement = replacement->right;
            }
            T1 key_pom = vertex->key;
            vertex->key = replacement->key;
            vertex->name = replacement->name;
            replacement->key = key_pom;
            return delet(replacement);
        }
        node<T1, T2>* replacement;
        if (vertex->left != nullptr && vertex->right == nullptr)    replacement = vertex->left;
        else replacement = vertex->right;
        if (vertex->parent != nullptr) {
            if (vertex->parent->left == vertex) vertex->parent->left = replacement;
            else vertex->parent->right = replacement;
        } else root = replacement;
        replacement->parent = vertex->parent;
        update_size(vertex->parent, true);
        update_depth(replacement);
        delete vertex;
        return true;
    }

    /*
    InsertR (link &p, Item x)
    // istotne jest przekazanie pierwszego parametru
    // przez referencję
    if p = NULL then
        p := new node;
        info(p) := x;
        left(p) := right(p) := NULL;
        return;
    if x < info(p) then
        InsertR (left(p), x);
        else
        InsertR (right(p), x);
    end.
    */

    T2& insert(T1 key) {
        count++;
        if (root == nullptr) {
            root = new node<T1, T2>;
            root->key = key;
            root->left = nullptr;
            root->right = nullptr;
            root->parent = nullptr;
            root->size = 1;
            root->depth = 0;
            return root->name;
        }
        return insert_recursive(root, key);
    }

    T2& insert_recursive(node<T1, T2>* vertex, T1 key) {
        node<T1, T2>* new_vertex;
        if (key < vertex->key) {
            if (vertex->left != nullptr)    return insert_recursive(vertex->left, key);
            new_vertex = new node<T1, T2>;
            vertex->left = new_vertex;
            update_size(vertex, false);
        }else {
            if (vertex->right != nullptr)   return insert_recursive(vertex->right, key);
            new_vertex = new node<T1, T2>;
            vertex->right = new_vertex;
            update_size(vertex, false);
        }
        new_vertex->key = key;
        new_vertex->left = nullptr;
        new_vertex->right = nullptr;
        new_vertex->parent = vertex;
        new_vertex->depth = vertex->depth + 1;
        return new_vertex->name;
    }

    void clean_recursive(node<T1, T2>* vertex) {
        if (vertex->left != nullptr)
            clean_recursive(vertex->left);
        if (vertex->right != nullptr)
            clean_recursive(vertex->right);
        delete vertex;
    }

    node<T1, T2>* select_recursive(node<T1, T2>* vertex, int k) {
        if (vertex == nullptr) return nullptr;

        int left_size = 0;
        if (vertex->left != nullptr) left_size = vertex->left->size;

        if (left_size == k - 1) return vertex;

        if (left_size >= k) return select_recursive(vertex->left, k);
        if (vertex->right == nullptr) return nullptr;
        return select_recursive(vertex->right, k - left_size - 1);
    }

    int test_value(node<T1, T2>* a, node<T1, T2>* b, T1 key_a, T1 key_b) {
        if (a->key > b->key) return 0;
        node<T1, T2>* vertex_left = a;
        node<T1, T2>* vertex_right = b;
        bool left;
        if (vertex_left->depth < vertex_right->depth) left = false;
        else left = true;
        int result = 0;
        while (vertex_left->depth != vertex_right->depth) {
            if (left) {
                if (vertex_left->key > key_a) {
                    if (vertex_left->right != nullptr) result += vertex_left->right->size;
                    result++;
                }
                vertex_left = vertex_left->parent;
            }else {
                if (vertex_right->key < key_b) {
                    if (vertex_right->left != nullptr) result += vertex_right->left->size;
                    result++;
                }
                vertex_right = vertex_right->parent;
            }
        }
        while (vertex_left != vertex_right) {
            if (vertex_right->key < key_b) {
                if (vertex_right->left != nullptr) result += vertex_right->left->size;
                result++;
            }
            if (vertex_left->key > key_a) {
                if (vertex_left->right != nullptr) result += vertex_left->right->size;
                result++;
            }
            vertex_left = vertex_left->parent;
            vertex_right = vertex_right->parent;
        }
        result++;
        return result;
    }

public:
    map()= default;

    T2& operator [](T1 key) {
        node<T1, T2>* vertex = find(key);
        if (vertex == nullptr) return insert(key);
        return vertex->name;
    }

    node<T1, T2>* find(T1 key) {
        auto vertex = root;
        while (vertex != nullptr && vertex->key != key) {
            if (key < vertex->key) vertex = vertex->left;
            else vertex = vertex->right;
        }
        return vertex;
    }

    node<T1, T2>* first_bigger(T1 key) {
        auto vertex = root;
        while (true) {
            if (vertex->key <= key) {
                if (vertex->right == nullptr) return nullptr;
                vertex = vertex->right;
            }
            else {
                if (vertex->left != nullptr) {
                    node<T1, T2>* left_node = vertex->left;
                    while (left_node->right != nullptr) left_node = left_node->right;
                    if (left_node->key <= key) return vertex;
                    vertex = vertex->left;
                }else return vertex;
            }
        }
    }

    node<T1, T2>* last_smaller(T1 key) {
        auto vertex = root;
        while (true) {
            if (key <= vertex->key) {
                if (vertex->left == nullptr) return nullptr;
                vertex = vertex->left;
            }
            else {
                if (vertex->right != nullptr) {
                    node<T1, T2>* right_node = vertex->right;
                    while (right_node->left != nullptr) right_node = right_node->left;
                    if (right_node->key >= key) return vertex;
                    vertex = vertex->right;
                }else return vertex;
            }
        }
    }

    bool delet(T1 key) {
        auto vertex = find(key);
        return delet(vertex);
    }

    void print() {
        if (root == nullptr) {
            cout<<"EMPTY\n";
            return;
        }
        print_recursive(root);
    }

    void clean() {
        if (root == nullptr) return;
        clean_recursive(root);
        root = nullptr;
        count = 0;
    }

    node<T1, T2>* select(int k) {
        if (k > count) return nullptr;
        return select_recursive(root, k);
    }

    int test(T1 a, T1 b) {
        if (root == nullptr) return 0;
        node<T1, T2>* a_node = first_bigger(a);
        node<T1, T2>* b_node = last_smaller(b);
        if (a_node == nullptr) return 0;
        if (b_node == nullptr) return 0;
        return test_value(a_node, b_node, a, b);
    }

    ~map() {
        clean();
    }
};


