
#include "Files.h"


File::File(string name, int size):BaseFile(name),size(size), strFile("FILE"){
} // Constructor
int File::getSize(){
    return size;
} // Return the size of the file
//todo added
string &File::getType(){
    return strFile;
}