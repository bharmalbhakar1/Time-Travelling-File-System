#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Treenode {
    int version_id;
    string content;
    string message;
    time_t created_timestamp;
    time_t modified_timestamp;
    time_t snapshot_timestamp;
    Treenode* parent;
    vector<Treenode*> children;

    Treenode(int version_id, string content, string message);
};
#endif