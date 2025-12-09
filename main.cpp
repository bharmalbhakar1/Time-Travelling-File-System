#include "File.h"
#include "HeapRecentFile.h"
#include "HeapBiggestFile.h"
#include <cstddef>
#include <iostream>
#include <sstream>
#include "FileMap.h"

using namespace std;

int main() {
    filemap files;
    heap_biggest_file biggest_files;
    heap_recent_file recent_files;
    string line;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string command;
        ss >> command;
        if (command == "CREATE") {
            string filename;
            ss >> filename;
            if(filename == ""){
                cout << "---Please enter valid filename" << endl << endl;
            } else if (files.get(filename) == nullptr) {
                File* f = new File(filename);
                files.put(filename, f);
                biggest_files.edit(f);
                recent_files.edit(f);
                cout << " ---File " << filename << " created successfully---" << endl;
                cout << endl;
            } else cout << "ERROR: File already exists." << endl << endl;
        }

        else if (command == "READ") {
            string filename; 
            ss >> filename;
            File* f = files.get(filename);
            if (f) f->READ(); else cout << "ERROR: File not found." << endl;
            cout << endl;
        }

        else if (command == "INSERT") {
            string filename; 
            ss >> filename;
            string content; 
            getline(ss, content);
            if (!content.empty() && content[0] == ' ') content = content.substr(1);
            File* f = files.get(filename);
            if (f) { 
                f->INSERT(content); biggest_files.edit(f); recent_files.edit(f); cout << "---Content inserted ---" << endl; }
            else cout << "ERROR: File not found." << endl;
            cout << endl;
        }

        else if (command == "UPDATE") {
            string filename; 
            ss >> filename;
            string content; 
            getline(ss, content);
            if (!content.empty() && content[0] == ' ') content = content.substr(1);
            File* f = files.get(filename);
            if (f) { 
                f->UPDATE(content); biggest_files.edit(f); recent_files.edit(f); 
                cout << "---Content updated ---" << endl; 
            }
            else cout << "ERROR: File not found." << endl;
            cout << endl;
        }

        else if (command == "SNAPSHOT") {
            string filename, msg;
            ss >> filename;
            getline(ss, msg);
            if (!msg.empty() && msg[0] == ' ') msg = msg.substr(1);
            File* f = files.get(filename);
            if (f) { f->SNAPSHOT(msg); recent_files.edit(f); cout << "---Snapshotted active version---" << endl;}
            else cout << "ERROR: File not found." << endl;
            cout << endl;
        }

        else if (command == "ROLLBACK") {
            string filename; ss >> filename; 
            int version_id;
            File* f = files.get(filename);
            if (f) {
                if (ss >> version_id) f->ROLLBACK(version_id);
                else f->ROLLBACK(-1);
            } else cout << "ERROR: File not found." << endl;
            cout << endl;
        }

        else if (command == "HISTORY") {
            string filename; 
            ss >> filename;
            File* f = files.get(filename);
            if (f) f->HISTORY(); 
            else cout << "ERROR: File not found." << endl;
            cout << endl;
        }

        else if (command == "RECENT_FILES") {
            int num; if (ss >> num) {
                if (num < 0) cout << "ERROR: Invalid input." << endl;
                else recent_files.give(num);
            } else recent_files.give(-1);
            cout << endl;
        }

        else if (command == "BIGGEST_TREES") {
            int num; if (ss >> num) {
                if (num < 0) cout << "ERROR: Invalid input." << endl;
                else biggest_files.give(num);
            } else biggest_files.give(-1);
            cout << endl;
        }

        else if (command == "EXIT"){
            cout << "---Program ends---" << endl;
            break;
        }
        else cout << "INVALID COMMAND: " << command << endl << endl;
    }
    return 0;
}