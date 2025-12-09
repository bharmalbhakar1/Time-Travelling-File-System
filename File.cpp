#include "File.h"
#include <iostream>
using namespace std;

// constructor creates file with given file name
File::File(string filename) {
    this->filename = filename;
    root = new Treenode(0, "", "ROOT SNAPSHOTTED");
    map.put(root->version_id, root);
    active_version = root;
    total_versions = 0;
}

// insert the content in the file
void File::INSERT(string content) {
    if (active_version == root || active_version->snapshot_timestamp != 0) {
        total_versions++;
        string new_content = active_version->content + content;
        Treenode* newnode = new Treenode(total_versions, new_content, "");
        root->children.push_back(newnode);
        map.put(total_versions, newnode);
        newnode->parent = active_version;
        active_version = newnode;
    } else {
        active_version->content += content;
        active_version->modified_timestamp = time(0);
    }
}

//update the content of the file
void File::UPDATE(string content) {
    if (active_version == root || active_version->snapshot_timestamp != 0) {
        total_versions++;
        Treenode* newnode = new Treenode(total_versions, content, "");
        root->children.push_back(newnode);
        map.put(total_versions, newnode);
        newnode->parent = active_version;
        active_version = newnode;
    } else {
        active_version->content = content;
        active_version->modified_timestamp = time(0);
    }
}

void File::ROLLBACK(int version_id) {
    if(version_id > total_versions){
        cout << total_versions << endl;
        cout << "ERROR: Version_ID not found." << endl;
        return;
    }
    if (active_version == root) {
        if (version_id > 0) {
            active_version = map.get(version_id);
            cout << "---Active version ID: " << active_version->version_id << endl;
        }
        else cout << "ALERT: Reached root, Can't roll back beyond root." << endl;
    } else {
        if (version_id == -1) {
            active_version = active_version->parent;
            cout << "---Active version ID: " << active_version->version_id << endl;
        }
        else {
            active_version = map.get(version_id);
            cout << "---Active version ID: " << active_version->version_id << endl;
        }
    }
}

void File::READ() {
    cout << "--- VERSION ID: " << active_version->version_id << ", " << "CONTENT: " << active_version->content << " ---" << endl;
}

//this is for snapshot
void File::SNAPSHOT(string message) {
    if (active_version->snapshot_timestamp == 0) {
        active_version->message = message;
        active_version->snapshot_timestamp = time(0);
    } else {
        cout << "ALERT: Already snapshotted." << endl;
        cout << endl;
    }
}

void File::created_timestamp() {
    cout << "--- CREATED TIMESTAMP " << ctime(&active_version->created_timestamp) << "---" << endl;
    cout << endl;
}

//this is for history. we start from active version and go till root 
void File::HISTORY() {
    Treenode* temp = active_version;
    if (!(active_version == root || active_version->snapshot_timestamp != 0)) {
        temp = active_version->parent;
    }
    while (temp != root) {
        cout << "---VERSION ID: " <<  temp->version_id << ", " << "MESSAGE: " << temp->message << ", " << "SNAPSHOT_TIME: " << ctime(&temp->snapshot_timestamp);
        temp = temp->parent;
    }
    cout << "---VERSION ID: " << temp->version_id << ", " << "MESSAGE: " <<  temp->message << ", " << "SNAPSHOT_TIME: " << ctime(&temp->created_timestamp);
}