
set -e
OUTPUT="program"
SRC="main.cpp HeapRecentFile.cpp HeapBiggestFile.cpp File.cpp FileMap.cpp Hashmap.cpp Treenode.cpp"
echo "Compiling..."
g++ -std=c++17 -Wall -Wextra -O2 $SRC -o $OUTPUT
echo "Running program..."
echo "---Start---" 
./$OUTPUT