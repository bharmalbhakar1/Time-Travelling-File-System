#ifndef FILE_H
#define FILE_H

#include "Treenode.h"
#include "Hashmap.h"
#include <map>
#include <string>
using namespace std;

class File {
public:
    string filename;
    Treenode* root;
    Treenode* active_version;
    map<int, Treenode*> version_map;
    int index_recent = -1;
    int index_biggest = -1;
    int total_versions;
    hashmap map;

    File(string filename);
    void INSERT(string content);
    void UPDATE(string content);
    void ROLLBACK(int version_id);
    void READ();
    void SNAPSHOT(string message);
    void created_timestamp();
    void HISTORY();
};
#endif