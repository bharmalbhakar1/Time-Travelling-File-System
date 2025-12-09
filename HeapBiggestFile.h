#ifndef HEAPBIGGESTFILE_H
#define HEAPBIGGESTFILE_H

#include "File.h"
#include <vector>
using namespace std;

class heap_biggest_file {
private:
    vector<File*> biggest_files;
public:
    heap_biggest_file();
    void heapify_up(int pos);
    void heapify_down(int pos);
    void edit(File* newfile);
    void give(int num);
};
#endif