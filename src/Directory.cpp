#include "Files.h"
#include <algorithm>
#include "GlobalVariables.h"
#include <iostream>

using namespace std;

Directory::Directory(string name, Directory *parent):
        BaseFile(name),children(),parent(parent), strDir("DIR"){
} // Constructor

Directory* Directory::getParent() const{
    return parent;
} // Return a pointer to the parent of this directory

void Directory::setParent(Directory *newParent){
    parent=newParent;
} // Change the parent of this directory

void Directory::addFile(BaseFile* file){
    if (!fileExists(file->getName())){
        children.push_back(file);
    }
    else
        delete file;
} // Add the file to children

void Directory::removeFile(string name) {
    bool done = false;
    for(int i=0;!done && (unsigned)i<children.size();i++){
        if(children.at(i)->getName() == name){
            swap(children[i],children.back());
            delete children.back();
            children.pop_back();
            done=true;
        }
    }
} // Remove the file with the specified name from children

void Directory::removeFile(BaseFile* file){
    if (fileExists(file->getName())) {
        bool done = false;
        for(int i=0;!done && (unsigned)i<children.size();i++){
            if(children.at(i)->getName() == file->getName()){
                swap(children[i],children.back());
                delete children.back();
                children.pop_back();
                done=true;
            }
        }
    }
} // Remove the file from children

void Directory::sortByName() {
    int i;
    BaseFile* key;
    int j;
    for (i = 1; (unsigned)i < children.size(); i++)
    {
        key = children[i];
        j = i-1;
        while (j >= 0 && children[j]->getName() > key->getName())
        {
            children.at(j+1) = children.at(j);
            j = j-1;
        }
        children.at(j+1) = key;
    }
} // Sort children by name alphabetically (not recursively)

void Directory::sortBySize() {
    int i;
    BaseFile* key;
    int j;
    for (i = 1; (unsigned)i < children.size(); i++)
    {
        key = children[i];
        j = i-1;
        while (j >= 0 && children[j]->getSize() > key->getSize())
        {
            children.at(j+1) = children.at(j);
            j = j-1;
        }
        children.at(j+1) = key;
    }
} // Sort children by size (not recursively)

vector<BaseFile*> Directory::getChildren() const{
    return children;
} // Return children

int Directory::getSize(){
    int size = 0;
    for (int i=0;(unsigned)i<children.size();i++)
        size=size+children.at(i)->getSize();
    return size;
} // Return the size of the directory (recursively)

string Directory::getAbsolutePath() const {
    if(parent== nullptr)
        return getName();
    else{
        return parent->getAbsolutePath()+ "/" + getName();
    }
}  //Return the path from the root to this

Directory::Directory(const Directory &other) :
        BaseFile(other.getName()), children(), parent(other.parent),strDir("DIR") {
    if (verbose==1||verbose==3)
        cout<<"Directory::Directory(const Directory &other)"<<endl;
    if(!other.children.empty()) {
        for(int i = 0;(unsigned) i < other.children.size(); ++i) {
            if(other.children[i]->getType() == "FILE")
                children.push_back(new File(other.children[i]->getName(),other.children[i]->getSize()));
            else
            {
                Directory* x=(Directory*)other.children[i];
                BaseFile* toAdd = new Directory(*x);
                dynamic_cast<Directory*>(toAdd)->setParent(this);
                children.push_back(toAdd);
            }
        }
    }
} // Copy Constructor

Directory& Directory::operator=(const Directory& other) {  //todo should i also delete the old vector of children ?
    if (verbose==1||verbose==3)
        cout<<"Directory& Directory::operator=(const Directory& other)"<<endl;
    if (&other != this) {
        this->setName(other.getName());
        vector<BaseFile*> newChildren;
        for(int i = 0;(unsigned) i < other.children.size(); ++i) {
            if(other.children[i]->getType() == "FILE")
                children.push_back(
                        new File(other.children[i]->getName(),other.children[i]->getSize()));
            else
            {
                Directory* x=(Directory*)other.children[i];
                BaseFile* toAdd = new Directory(*x);
                children.push_back(toAdd);
            }
        }

        this->children = newChildren;
        this->parent = other.parent;
    }
    return * this;
}  // Copy Assignment Operator

Directory::Directory(Directory &&other) : BaseFile(other.getName()), children(),parent(),strDir("DIR") {
    if (verbose==1||verbose==3)
        cout<<"Directory::Directory(Directory &&other)"<<endl;
    for(int i=0;(unsigned)i<other.getChildren().size();i++){
        addFile(other.getChildren().at(i));
    }
} // Move Constructor

Directory& Directory::operator=(Directory&& other) {
    if (verbose==1||verbose==3)
        cout<<"Directory& Directory::operator=(Directory&& other)"<<endl;
    if (&other != this) {
        for(int i=0;(unsigned)i<other.getChildren().size();i++){
            addFile(other.getChildren().at(i));
        }
        delete parent;
        parent = other.parent;

        other.parent = nullptr;
    }
    return * this;
} // Move Assignment Operator

Directory::~Directory() {
    if (verbose==1||verbose==3)
        cout<<"Directory::~Directory()"<<endl;
    for (int i=0;(unsigned)i<children.size();i++)
        if (children.at(i)->getType()=="DIR"){
            swap(children.at(i), children.back());
            delete children.back();
            children.pop_back();
        }
} // Destructor

//todo added
string &Directory::getType(){
    return strDir;
}

bool Directory::fileExists(string fileName) {
    for (int i=0;(unsigned)i<children.size();i++)
        if (children.at(i)->getName()==fileName)
            return true;
    return false;
}

BaseFile* Directory::getFile(string fileName) {
    vector<BaseFile *>::iterator it = children.begin();
    for (int i=0;(unsigned)i<children.size();i++)
        if (children.at(i)->getName()==fileName)
            return children.at(i);
    return nullptr;
}