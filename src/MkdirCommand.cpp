#include <sstream>
#include <algorithm>
#include <iostream>
#include "Commands.h"
#include "GlobalVariables.h"

using namespace std;


MkdirCommand::MkdirCommand(string args) :BaseCommand(args) {}

void MkdirCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    vector<string> *dirs = split(getArgs());
    char first=getArgs().at(0);
    Directory* initDir=&fs.getWorkingDirectory();
    if (fs.changeDirectoryFromAddress(*dirs,1,first=='/', true)) {
        for (int i=0;(unsigned) i<fs.getWorkingDirectory().getChildren().size();i++)
            if (dirs->at((dirs->size()-1))==fs.getWorkingDirectory().getChildren().at(i)->getName()
                    &&fs.getWorkingDirectory().getChildren().at(i)->getType()=="DIR") {
                cout << "Directory already exists" << endl;
                goto endFunc;
            }
        Directory *d = new Directory(dirs->at(dirs->size() - 1), &fs.getWorkingDirectory());
        fs.getWorkingDirectory().addFile(d);
        fs.setWorkingDirectory(initDir);
    }
    endFunc:
    fs.setWorkingDirectory(initDir);
    delete dirs;
    return;
}

string MkdirCommand::toString(){
    return "mkdir";
}