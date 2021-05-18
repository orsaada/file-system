
#include "FileSystem.h"
#include "GlobalVariables.h"
#include <iostream>
using namespace std;

FileSystem::FileSystem():rootDirectory(), workingDirectory(){
    rootDirectory=new Directory("/", nullptr);
    workingDirectory=rootDirectory;
}
Directory& FileSystem::getRootDirectory() const{
    return *rootDirectory;
} // Return reference to the root directory
Directory& FileSystem::getWorkingDirectory() const{
    return *workingDirectory;
} // Return reference to the working directory
void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory){
    workingDirectory=newWorkingDirectory;
} // Change the working directory of the file system

//todo eran did

bool FileSystem::changeDirectoryFromAddress(vector<string> &dirs, int dirOrFile, bool isFromRoot, bool canMakeDir) {
    //gets vector string and boolean if starting from working or root
    //int dirOrFile - will be 0 if the expression we expect after te last '/' will be directory
    //and will be 1 if we expect the last expression to be a file, or a new directory there
    //for example, in cd - we should get 0, and in mkfile and mkdir, we should get 1
    //returns true if the path was OK and getWorkingDirectory will be changed
    //otherwise it returns false and getWorkingDirectory will not be changed
    //which should be handled in execute
    Directory* cur;
    if (isFromRoot)//directory will start from working or root, according to bool
        cur = &getRootDirectory();
    else
        cur = &getWorkingDirectory();
    bool isOk = true;
    for (int i = 0; isOk &&(unsigned) i < dirs.size() - dirOrFile; i++) {
        if (dirs.at(i) == "..")
            if (cur->getParent()!= nullptr)
                cur = cur->getParent();
            else
                isOk=false;
        else{
            bool isFound=false;
            for (int j=0;!isFound&& (unsigned) j<cur->getChildren().size();j++){
                if (cur->getChildren().at(j)->getType()=="DIR"&&cur->getChildren().at(j)->getName()==dirs.at(i)){
                    isFound = true;
                    cur = dynamic_cast<Directory *>(cur->getChildren().at(j));
                    }
            }
            if (!isFound) {
                if (canMakeDir) {
                    Directory *newDir = new Directory(dirs.at(i), cur);
                    cur->addFile(dynamic_cast<BaseFile*>(newDir));
                    setWorkingDirectory(newDir);
                    cur=&getWorkingDirectory();
                }
                else
                    isOk=false;
            }
        }
    }
    if (isOk) {
        setWorkingDirectory(cur);
        return true;
    }
    return false;
}

FileSystem::FileSystem(const FileSystem& other)
        : rootDirectory{new Directory{*(other.rootDirectory)}},
          workingDirectory{new Directory{*(other.workingDirectory)}}
{
    if (verbose==1||verbose==3)
        cout<<"FileSystem::FileSystem(const FileSystem& other)"<<endl;
}//Copy Constructor

FileSystem& FileSystem::operator=(const FileSystem& other){
    if (verbose==1||verbose==3)
        cout<<"FileSystem& FileSystem::operator=(const FileSystem& other)"<<endl;
    if(this!=&other){
        delete rootDirectory;
        delete workingDirectory;
        rootDirectory = nullptr;
        workingDirectory = nullptr;
        rootDirectory = new Directory{*(other.rootDirectory)};
        workingDirectory = new Directory{*(other.workingDirectory)};
    }

    return *this;
}// Copy Assignment Operator

FileSystem::FileSystem(FileSystem &&other)
        :rootDirectory{other.rootDirectory},
         workingDirectory{other.workingDirectory}
{
    if (verbose==1||verbose==3)
        cout<<"FileSystem::FileSystem(FileSystem &&other)"<<endl;
    other.workingDirectory= nullptr;
    other.rootDirectory= nullptr;
} // Move Constructor

FileSystem& FileSystem::operator=(FileSystem&& other) {
    if (verbose==1||verbose==3)
        cout<<"FileSystem& FileSystem::operator=(FileSystem&& other)"<<endl;
    if(this!=&other){
        delete rootDirectory;
        delete workingDirectory;
        rootDirectory=other.rootDirectory;
        workingDirectory=other.workingDirectory;

        other.workingDirectory= nullptr;
        other.rootDirectory= nullptr;
    }
    return *this;
}//Move assignment operator

FileSystem::~FileSystem(){
    if (verbose==1||verbose==3)
        cout<<"FileSystem::~FileSystem()"<<endl;
    delete rootDirectory;
}//Destructor