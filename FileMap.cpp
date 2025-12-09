#include "FileMap.h"

//constructor for filemap
filemap::filemap() {
    list.resize(size);
}

//this functions converts string in int values using polynmial rolling method
int filemap::hashfunction(const std::string& key) {
    unsigned long hash = 0;
    for (char c : key) {
        hash = hash * 31 + c;   
    }
    return hash % size;
}

// puts the file with name in the map 
void filemap::put(const std::string& key, File* file) {
    int idx = hashfunction(key);
    for (auto &p : list[idx]) {
        if (p.first == key) {
            p.second = file;
            return;
        }
    }
    list[idx].push_back({key, file});
}

//this gives the pointer related to the filename
File* filemap::get(const std::string& key) {
    int idx = hashfunction(key);
    for (auto &p : list[idx]) {
        if (p.first == key) {
            return p.second;
        }
    }
    return nullptr;
}

// remove the pointer corresponding to a particular filename
void filemap::remove(const std::string& key) {
    int idx = hashfunction(key);
    for (auto it = list[idx].begin(); it != list[idx].end(); it++) {
        if (it->first == key) {
            list[idx].erase(it);
            return;
        }
    }
}