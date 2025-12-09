#include "HeapBiggestFile.h"
#include "File.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

heap_biggest_file::heap_biggest_file() {
    biggest_files = {};
}

void heap_biggest_file::heapify_up(int pos) {
    int child = pos;
    int parent = (child - 1) / 2;

    while (child > 0 && biggest_files[parent]->total_versions < biggest_files[child]->total_versions) {
        int ind = biggest_files[parent]->index_biggest;
        biggest_files[parent]->index_biggest = biggest_files[child]->index_biggest;
        biggest_files[child]->index_biggest = ind;
        swap(biggest_files[parent], biggest_files[child]);
        child = parent;
        parent = (child - 1) / 2;
    }
}

void heap_biggest_file::heapify_down(int pos) {
    int parent = pos;
    int size = biggest_files.size();
    while (true) {
        int lchild = 2 * parent + 1;
        int rchild = 2 * parent + 2;
        int largest = parent;
        if (lchild < size && biggest_files[lchild]->total_versions > biggest_files[largest]->total_versions) {
            largest = lchild;
        }
        if (rchild < size && biggest_files[rchild]->total_versions > biggest_files[largest]->total_versions) {
            largest = rchild;
        }
        if (largest != parent) {
            int ind = biggest_files[parent]->index_biggest;
            biggest_files[parent]->index_biggest = biggest_files[largest]->index_biggest;
            biggest_files[largest]->index_biggest = ind;
            swap(biggest_files[parent], biggest_files[largest]);
            parent = largest;
        } else {
            break;
        }
    }
}

void heap_biggest_file::edit(File* newfile) {
    if (newfile->index_biggest == -1) {
        newfile->index_biggest = biggest_files.size(); 
        biggest_files.push_back(newfile);
        heapify_up(biggest_files.size() - 1);
    } else {
        heapify_up(newfile->index_biggest);
        heapify_down(newfile->index_biggest);
    }
}

void heap_biggest_file::give(int num) {
    int size = biggest_files.size();
    if (num > size || num == -1) {
        num = size;
    }
    vector<File*> temp = biggest_files;
    cout << "---BIGGEST FILES: ";
    while (num > 0 && !temp.empty()) {
        cout << temp[0]->filename << " ";
        swap(temp[0], temp.back());
        temp.pop_back();
        int parent = 0;
        int size = temp.size();
        while (true) {
            int lchild = 2 * parent + 1;
            int rchild = 2 * parent + 2;
            int largest = parent;
            if (lchild < size && temp[lchild]->total_versions > temp[largest]->total_versions) {
                largest = lchild;
            }
            if (rchild < size && temp[rchild]->total_versions > temp[largest]->total_versions) {
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