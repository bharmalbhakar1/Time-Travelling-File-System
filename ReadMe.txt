LONG ASSIGNMENT COL-106
------
NAME - BHARMAL BHAKAR 
ENTRY NO - 2024CS10403

------
PROJECT NAME - Time-Travelling File System
    This project is an in-memory, simplified version control system, designed to manage the version history of multiple files. 
    It functions similarly to Git but is implemented using fundamental data structures like Trees, HashMaps, and Heaps from scratch.

------
WORKING
How the Program Works
    The program operates by reading commands from standard input (stdin) and performing the corresponding actions.
    Getline function is used to take input, which is a C++ function that reads a whole line of text from an input stream (like cin, a file, or a string stream).
    It maintains a collection of File objects in FileMap, each with its own version history tree.
    The core logic revolves around the File class, which handles all file-specific operations such as content modification, versioning, and rollback.
    System-wide analytics, like listing the most recent or largest files, are managed by separate Heap data structures.
    HashMaps are used to have fast access and lookups of versions by their version ID and files by their file names.

------
PROJECT STRUCTURE
     main.cpp                    # Entry point of the program (drives the logic, calls heaps/maps)
     File.h / File.cpp           # Defines the File class and its attributes (versions, timestamps, etc.)
     HeapRecentFile.h / .cpp     # Max-heap for managing most recently modified files
     HeapBiggestFile.h / .cpp.   # Max-heap for managing files with the largest number of versions
     FileMap.h / FileMap.cpp     # Manages mapping between filenames and File objects
     Hashmap.h / Hashmap.cpp     # Custom hashmap implementation for efficient file lookup
     Treenode.h / Treenode.cpp   # Tree-based structure for organizing versions
     run.sh                      # Shell script to compile and execute the project

How they are connected
main.cpp
    Calls functions from the heaps (HeapRecentFile, HeapBiggestFile) and file management classes (FileMap, Hashmap) to implement the required functionality.
File
    Represents a file and its versions; used as the fundamental object in heaps and maps.
HeapRecentFile
    Maintains the most recently modified files using a max-heap.
HeapBiggestFile
    Maintains files with the highest number of versions using a max-heap.
FileMap & Hashmap
    Provide efficient storage, retrieval, and mapping from filenames to file objects.
Treenode
    Organizes different versions of a file hierarchically.

This modular design makes the project easier to read, debug, and extend in the future.

------
IMPLEMENTED COMMANDS
    The program supports the following commands:

    CREATE <filename>: 
    Creates a new file with the specified name. Name should be single string should not contain spaces. If no name is given ERROR: Plesae enter valid filaname would be raised.
    Stores it the Filemap. Stores in recent_files. Stores in the biggest_file. And cout (File <filename> created succesfullly).
    If a file with this name already exits then raises a ERROR: File already exists.

    READ <filename>: 
    Takes input of any length with spaces.
    Displays the content of the currently active version of the file in the format VERSION ID: <int>, CONTENT: <string>
    Shows "ERROR: File not found." if file with the given filename does not exits.

    INSERT <filename> <content>: 
    Takes input of any length with spaces.
    Appends new content to the existing content of the activeversion. 
    Creates a new version if the current version is a snapshot, otherwise modifies the active version.
    Shows (---Content inserted---);
    Shows "ERROR: File not found." in case file with given filename does not exits.

    UPDATE <filename> <content>: 
    Takes input of any length with spaces.
    Replaces the content of the activeversion.
    Behaves the same as INSERT regarding versioning.
    Shows (---Content updated---);
    Shows "ERROR: File not found." in case file with given filename does not exits

    SNAPSHOT <filename> <message>: 
    Takes input of any length with spaces.
    Marks the current version as immutable and associates a message with it. 
    Shows (snapshotted succesfullly) when done.
    Shows "ERROR: File not found." in case file with given filename does not exits

    ROLLBACK <filename> [versionID]: 
    Reverts the active version to a previous state. 
    If versionID is omitted, it rolls back to the immediate parent version.
    Shows "ERROR: File not found." in case file with given filename does not exits.
    Shows "Active version_id" when rollbakc to that id or shows "can't rollback" when rollback is called from the root.

    HISTORY <filename>: 
    Lists the details of all snapshotted versions of the file in the chronological order (from active version to the root)
    Shows "ERROR: File not found." in case file with given filename does not exits

    RECENT_FILES [num]: 
    Lists the num most recently modified files. 
    If num is not provided, it lists all of them.
    If num is not a +ve integer it shows "ERROR: Invalid input."

    BIGGEST_TREES [num]: 
    Lists the num files with the largest number of versions. 
    If num is not provided, it lists all of them.
    If num is not a +ve integer it shows "ERROR: Invalid input."

    EXIT: Exits the program.
------

DATA STRUCTURES IMPLEMENTED AND USED IN THE PROGRAM
    This project was built without using C++ Standard Template Library (STL) data structures for the core components, as required by the assignment.
1. Tree (Treenode struct)

    Each file's version history is represented as a tree. The Treenode struct acts as a node in this tree.

    version_id: A unique ID for each version of a particular file.
    content: The file content at this version("Root Node" if version is a root).
    message: A message associated with a snapshot(empty if not snapshotted).
    created_timestamp: Timestamp of when this version was created.
    modified_timestamp: Timestamp of the last content modification(when file is created it is equal to the created_timestamp).
    snapshot_timestamp: Timestamp of when this version was snapshotted(it is 0 i.e. some garbage value, when the file, is created).
    parent: A pointer to the parent node, enabling easy rollback.
    children: A vector of pointers to child nodes, representing branches in the version history.

2. Hash Map (hashmap class)
 CORE IDEA:
    Implemented using an array of size hundread.(assumed that the files given input for this project are K*100 where K < 100)
    Given key are store in place of key%size index.
 2.1 FileMap(for storing various files).
    static const int size = 100(size capacity of hashmap)
    list (our haspmap in the form of vector<vector<pair<string, File*>>>);
    A custom hash map is used to store and retrieve File pointers using their filename as the key.
    Hashing Function: A simple modulo operation (key % size) is used to map keys to an index in the hash table.
        These keys are generated form the filename using polynomial rolling hash.
        This insures that no two Files with different Files names have the sam keys
    Get function: gives the File* pointer of the given filename.
    Remove function: Removes the pointer correspondgin to the given filename.
    Collision Handling: Collisions are handled using chaining. Each bucket in the hash table is a vector that stores pair<int, File*> objects.

 2.2 HashMap (for storing the version ID used for roll back)
    int size = 100 (size capacity of hashmap)
    map (our haspmap in the form of vector<vector<pair<string, File*>>>);
    A custom hash map is used to store and retrieve TreeNode pointers using their version ID as the key.
    Hashing Function: A simple modulo operation (key % size) is used to map keys to an index in the hash table.
        This insures that no two different version_id  have the same TreeNode.
    Collision Handling: Collisions are handled using chaining. Each bucket in the hash table is a vector that stores pair<int, TreeNode*> objects.

3. Heaps (heap_recent_file and heap_biggest_file classes)
    Two custom Max-Heaps are used to manage system-wide analytics. These heaps are implemented using a vector.
    Vector is used in place of dynamic array as it is easier to write the code for he vector ans the time complexity and the space complexity are almost same for both dynamic array and the vector.
    heap_recent_file: A Max-Heap that prioritizes files by their modified_timestamp.
    heap_biggest_file: A Max-Heap that prioritizes files by their total_versions.
    Operations: 
    The heaps support heapify_up and heapify_down operations to maintain the heap property after an element is added or modified. 
    In heap_recent_file modified_timestamp is used for comparison and in heap_biggest_file total_versions are used for the comparison.
    The edit function handles both insertion and updating of a file's position in the heap.
    For insert we just insert at the back of the heap and heapify it up and heapify it down.
    But for updating we use loaction of the heap_recent_file and heap_biggest_file which are stored in the files as index_recent and index_biggest and then heapify it up form the given position.
    The give function give the top of the heap and then remove it and store in a vector copy and then again heapify the heap using heapify down. 
    When the required files are given out the files which where deletd from the heap is stored again in the heap
    We used a copy temp here for the cout porpose so that our heap remain undestoryed.

------
ERROR HANDLING
    The program handles several invalid inputs and states, providing clear error messages to the user:
    File Not Found: An error is reported when a command is issued for a non-existent file.
    File Already Exists: An error is reported when trying to create a file that already exists.
    Already Snapshotted: The SNAPSHOT command alerts the user if the active version has already been snapshotted.
    Reaching Root: The ROLLBACK command alerts the user if they try to roll back beyond the root version.
    Invalid Input: The RECENT_FILES and BIGGEST_TREES commands handle negative integer inputs.

------
COMPILATION AND EXECUTION (with working shell subscript)
    This script will Compile all source files (main.cpp, HeapRecentFile.cpp, HeapBiggestFile.cpp, File.cpp, FileMap.cpp, Hashmap.cpp, Treenode.cpp) into an executable named program.
    If there are compilation errors, the script will stop immediately.
Compilation
    Give execute permission to the script (first time only): 
        chmod +x run.sh
Execution
    Compile and run the project:
        ./run.sh 
    The program will first complie (shows "Compiling...")
    Then after compling it will show(Running program... && ---Start---)
    The program will then wait for commands. An example session might look like this:
    CREATE <filename>
    INSERT <filename> <content>
    UPDATE <filename> <content>
    READ <filename>
    SNAPSHOT <filename> <message>
    HISTORY <filename> 
    ROLLBACK <filename> [version_id]
    RECENT_FILES [num]
    BIGGEST_TREES [num]
    EXIT 

------
COMPILATION AND EXECUTION (without using working shell subscript)
    To compile the program, use a C++ compiler such as g++.

Compilation
    g++ main.cpp Treenode.cpp Hashmap.cpp File.cpp HeapRecentFile.cpp HeapBiggestFile.cpp FileMap.cpp -o program

Execution
    Run the executable and provide commands through standard input.
    ./program
    The program will then wait for commands. An example session might look like this:
    CREATE <filename>
    INSERT <filename> <content>
    UPDATE <filename> <content>
    READ <filename>
    SNAPSHOT <filename> <message>
    HISTORY <filename> 
    ROLLBACK <filename> [version_id]
    RECENT_FILES [num]
    BIGGEST_TREES [num]
    EXIT 
------

