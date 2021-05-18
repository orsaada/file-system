#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"

MvCommand::MvCommand(string args):BaseCommand(args){

}
void MvCommand::execute(FileSystem & fs) {
    if (verbose == 2 || verbose == 3)
        cout << toString() + " " + getArgs() << endl;

    int whereSpace = getArgs().find_first_of(' ');
    string sourceDir = getArgs().substr(0, whereSpace);
    string destDir = getArgs().substr(whereSpace + 1);
    vector<string> *vSource = split(sourceDir);
    vector<string> *vDest = split(destDir);
    Directory *initDir = &fs.getWorkingDirectory();
    bool success = fs.changeDirectoryFromAddress(*vSource, 1, sourceDir.at(0) == '/', false);
    if (!success) {
        cout << "The system cannot find the path specified" << endl;
        goto endFunc;
    }
    else {
        BaseFile *copy;
        Directory* dirToRemoveFrom;
        bool isFound = false;
        for (int i = 0; !isFound && (unsigned) i < fs.getWorkingDirectory().getChildren().size(); i++) {
            if (fs.getWorkingDirectory().getChildren().at(i)->getName() == vSource->at(vSource->size() - 1)) {
                isFound = true;
                copy = fs.getWorkingDirectory().getChildren().at(i);
                dirToRemoveFrom=&fs.getWorkingDirectory();
                break;
            }
        }
        if (!isFound) {
            cout << "The system cannot find the path specified" << endl;
            goto endFunc;
        }
        fs.setWorkingDirectory(initDir);
        success = fs.changeDirectoryFromAddress(*vDest, 0, getArgs()[0] == '/', false);
        if (!success) {
            cout << "The system cannot find the path specified" << endl;
            goto endFunc;
        } else {
            if (fs.getWorkingDirectory().fileExists(copy->getName())) {
                cout << "File already exists" << endl;
                goto endFunc;
            }
            if (copy->getType() == "DIR") {
                Directory *copyDir = dynamic_cast<Directory *>(copy);
                fs.getWorkingDirectory().addFile(new Directory(*copyDir));
                dirToRemoveFrom->removeFile(copy);
                copyDir = nullptr;
            } else {
                File *copyFile = dynamic_cast<File *>(copy);
                fs.getWorkingDirectory().addFile(new File(*copyFile));
                dirToRemoveFrom->removeFile(copy);
                copyFile = nullptr;
            }

        }
    }
    endFunc:
    delete vSource;
    delete vDest;
    fs.setWorkingDirectory(initDir);
    return;
}
string MvCommand::toString(){
    return "mv";
}