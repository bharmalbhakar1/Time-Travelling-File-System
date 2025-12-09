#ifndef HEAPRECENTFILE_H
#define HEAPRECENTFILE_H

#include "File.h"
#include <vector>
using namespace std;

class heap_recent_file {
private:
    vector<File*> recent_files;
public:
    heap_recent_file();
    void heapify_up(int pos);
    void heapify_down(int pos);
    void edit(File* newfile);
    void give(int num);
};
#endif