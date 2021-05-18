#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"

MkfileCommand::MkfileCommand(string args):BaseCommand(args){

}
void MkfileCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    int whereSpace=getArgs().find_first_of(' ');
    Directory* initDir = &fs.getWorkingDirectory();
    if (whereSpace==-1){
        cout <<"The system cannot find the path specified"<<endl;
        return;
    }
    vector<string> *dirs = split(getArgs().substr(0,whereSpace));
    int size;
    try {
        size=stoi(getArgs().substr(whereSpace+1));
    }
    catch(...){
        cout<<"The system cannot find the path specified"<<endl;
        return;
    }
    char first=getArgs().at(0);
    if (fs.changeDirectoryFromAddress(*dirs,1,first=='/', false)) {
        for (int i=0;(unsigned)i<fs.getWorkingDirectory().getChildren().size();i++)
            if (dirs->at((dirs->size()-1))==fs.getWorkingDirectory().getChildren().at(i)->getName()
                &&fs.getWorkingDirectory().getChildren().at(i)->getType()=="FILE") {
                cout << "File already exists" << endl;
                goto endFunc;
            }
        fs.getWorkingDirectory().addFile(new File(dirs->at(dirs->size()-1), size));
    }
    endFunc:
    fs.setWorkingDirectory(initDir);
    delete dirs;
    return;
}
string MkfileCommand::toString(){
    return "mkfile";
}