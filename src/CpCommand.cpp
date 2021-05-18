#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"
CpCommand::CpCommand(string args):BaseCommand(args){}
void CpCommand::execute(FileSystem & fs) {
    if (verbose == 2 || verbose == 3)
        cout << toString() + " " + getArgs() << endl;
    int whereSpace = getArgs().find_first_of(' ');
    if (whereSpace == -1)
        cout << "No such file or directory" << endl;
    string sourceDir = getArgs().substr(0, whereSpace);
    string destDir = getArgs().substr(whereSpace + 1);
    //todo take care /
    vector<string> *vSource = split(sourceDir);
    vector<string> *vDest = split(destDir);
    Directory *initDir = &fs.getWorkingDirectory();
    bool success = fs.changeDirectoryFromAddress(*vSource, 1, getArgs()[0] == '/', false);
    if (!success) {
        cout << "The system cannot find the path specified" << endl;
        goto endFunc;
    }
    else {
        BaseFile *copy;
        bool isFound = false;
        for (int i = 0; !isFound &&(unsigned) i < fs.getWorkingDirectory().getChildren().size(); i++) {
            if (fs.getWorkingDirectory().getChildren().at(i)->getName() == vSource->at(vSource->size() - 1)) {
                isFound = true;
                copy = fs.getWorkingDirectory().getChildren().at(i);
                break;
            }
        }
        if (!isFound) {
            cout << "The system cannot find the path specified" << endl;
            fs.setWorkingDirectory(initDir);
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
            } else {
                File *copyFile = dynamic_cast<File *>(copy);
                fs.getWorkingDirectory().addFile(new File(*copyFile));
            }
        }
    }
    endFunc:
    delete vSource;
    delete vDest;
    fs.setWorkingDirectory(initDir);
    return;
}
string CpCommand::toString(){
    return "cp";
}