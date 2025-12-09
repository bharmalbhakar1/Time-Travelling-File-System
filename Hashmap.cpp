#include "Hashmap.h"
#include <algorithm>

hashmap::hashmap() {
    map.resize(size);
}
//this function converts key into index for map
int hashmap::hasfunction(int key) {
    return key % size;
}

void hashmap::put(int key, Treenode* location) {
    int idx = hasfunction(key);
    for (pair<int, Treenode*> &p : map[idx]) {
        if (p.first == key) {
            p.second = location;
            return;
        }
    }
    map[idx].push_back({key, location});
}

Treenode* hashmap::get(int key) {
    int idx = hasfunction(key);
    for (auto p : map[idx]) {
        if (p.first == key) return p.second;
    }
    return nullptr;
}

void hashmap::remove(int key) {
    int idx = hasfunction(key);
    for (auto &p : map[idx]) {
        if (p.first == key) {
            auto it = find(map[idx].begin(), map[idx].end(), p);
            map[idx].erase(it);
            return;
        }
    }
}

// As in this question our version ID's are Natural Number including 0 so we can directly use the vector in place of hashmap.
// hashmap::hashmap() {
//     vector<int> map;
// }

// void hashmap::put(int key, Treenode* location) {
//     map[key].push_back({key, location});
// }

// Treenode* hashmap::get(int key) {
//     if(key < hashmap.size()){
//          return map[key];
//     }
//     return nullptr;
// }
