#include "HeapRecentFile.h"
#include "File.h"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm> 

using namespace std;

heap_recent_file::heap_recent_file() {
    recent_files = {};
}

void heap_recent_file::heapify_up(int pos) {
    int child = pos;
    int parent = (child - 1) / 2;

    while (child > 0 && recent_files[parent]->active_version->modified_timestamp < recent_files[child]->active_version->modified_timestamp) {
        int ind = recent_files[parent]->index_recent;
        recent_files[parent]->index_recent = recent_files[child]->index_recent;
        recent_files[child]->index_recent = ind;
        swap(recent_files[parent], recent_files[child]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

void heap_recent_file::heapify_down(int pos) {
    int parent = pos;
    int size = recent_files.size();

    while (true) {
        int lchild = 2 * parent + 1;
        int rchild = 2 * parent + 2;
        int largest = parent;

        if (lchild < size && 
            recent_files[lchild]->active_version->modified_timestamp > recent_files[largest]->active_version->modified_timestamp) {
            largest = lchild;
        }
        if (rchild < size &&
            recent_files[rchild]->active_version->modified_timestamp > recent_files[largest]->active_version->modified_timestamp) {
            largest = rchild;
        }

        if (largest != parent) {
            int ind = recent_files[parent]->index_recent;
            recent_files[parent]->index_recent = recent_files[largest]->index_recent;
            recent_files[largest]->index_recent = ind;
            swap(recent_files[parent], recent_files[largest]);
            parent = largest;
        } else {
            break; 
        }
    }
}

void heap_recent_file::edit(File* newfile) {
    if(newfile->index_recent == -1){
        newfile->index_recent = recent_files.size();
        recent_files.push_back(newfile);
        heapify_up(recent_files.size() - 1);
    } else {
        heapify_up(newfile->index_recent);
        heapify_down(newfile->index_recent);
    }
}

void heap_recent_file::give(int num) {
    int size = recent_files.size();
    if (num > size || num == -1) {
        num = size;
    }

    vector<File*> temp = recent_files;
    vector<File*> result;

    cout << "---RECENT FILES: ";
    while (num > 0 && !temp.empty()) {
        result.push_back(temp[0]);
        cout << temp[0]->filename << " ";

        swap(temp[0], temp.back());
        temp.pop_back();

        int parent = 0;
        int size = temp.size();
        while (true) {
            int lchild = 2 * parent + 1;
            int rchild = 2 * parent + 2;
            int largest = parent;

            if (lchild < size && temp[lchild]->active_version->modified_timestamp > temp[largest]->active_version->modified_timestamp) {
                largest = lchild;
            }
            if (rchild < size && temp[rchild]->active_version->modified_timestamp > temp[largest]->active_version->modified_timestamp) {
                largest = rchild;
            }

            if (largest != parent) {
                swap(temp[parent], temp[largest]);
                parent = largest;
            } else {
                break;
            }
        }
        num--;
    }
    cout << endl;
}