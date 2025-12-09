#include "Treenode.h"
#include <cstddef>

Treenode::Treenode(int version_id, string content, string message) {
    this->version_id = version_id;
    this->content = content;
    this->message = message;
    created_timestamp = time(0);
    modified_timestamp = created_timestamp;
    snapshot_timestamp = 0;
    parent = nullptr;
}