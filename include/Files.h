#ifndef FILES_H_
#define FILES_H_

#include <string>
#include <vector>
using namespace std;

class BaseFile {
private:
    string name;

public:
    BaseFile(string name);
    string getName() const;
    void setName(string newName);
    virtual int getSize() = 0;
    //todo added
    virtual string &getType() = 0;
    virtual ~BaseFile();
};

class File : public BaseFile {
private:
    int size;

    string strFile;
public:
    File(string name, int size); // Constructor
    int getSize(); // Return the size of the file
    string &getType();
};

class Directory : public BaseFile {
private:
    vector<BaseFile*> children;
    Directory *parent;
    bool sizeComp(File file1, File file2);
    bool nameComp(File file1, File file2);

    string strDir;
public:
    Directory(string name, Directory *parent); // Constructor
    Directory(const Directory &other); // Copy Constructor
    Directory& operator=(const Directory& other); // Copy Assignment Operator
    Directory(Directory &&other); // Move Constructor
    Directory& operator=(Directory&& other); // Move Assignment Operator
    ~Directory(); // Destructor
    Directory *getParent() const; // Return a pointer to the parent of this directory
    void setParent(Directory *newParent); // Change the parent of this directory
    void addFile(BaseFile* file); // Add the file to children
    void removeFile(string name); // Remove the file with the specified name from children
    void removeFile(BaseFile* file); // Remove the file from children
    void sortByName(); // Sort children by name alphabetically (not recursively)
    void sortBySize(); // Sort children by size (not recursively)
    vector<BaseFile*> getChildren() const; // Return children
    int getSize(); // Return the size of the directory (recursively)
    string getAbsolutePath() const;  //Return the path from the root to this
    //todo added
    bool fileExists(string fileName); //True/False if the name of the file exists
    BaseFile* getFile(string fileName); //Return a pointer for a sub BaseFile in the directory
    string &getType(); //Return dynamic type of baseFile
};

#endif