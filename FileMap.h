#ifndef FILEMAP_H
#define FILEMAP_H

#include "File.h"
#include <vector>
#include <string>
#include <utility>

class filemap {
private:
    static const int size = 100;
    vector<vector<pair<string, File*>>> list;
public:
    filemap();
    int hashfunction(const std::string& key);
    void put(const std::string& key, File* file);
    File* get(const std::string& key);
    void remove(const std::string& key);
};

#endif