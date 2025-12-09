#ifndef HASHMAP_H
#define HASHMAP_H

#include "Treenode.h"
#include <vector>
#include <utility>
using namespace std;

class hashmap {
private:
    static const int size = 100;
    vector<vector<pair<int, Treenode*>>> map;
public:
    hashmap();
    int hasfunction(int key);
    void put(int key, Treenode* location);
    Treenode* get(int key);
    void remove(int key);
};
#endif