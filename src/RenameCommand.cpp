#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"

RenameCommand::RenameCommand(string args):BaseCommand(args){

}
void RenameCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    int whereSpace=getArgs().find_first_of(' ');
    if (whereSpace==-1){
        cout <<"No such file or directory"<<endl;
        return;
    }
    Directory* initDir=&fs.getWorkingDirectory();
    string path=getArgs().substr(0,whereSpace);
    string newName=getArgs().substr(whereSpace+1);
    if (path==fs.getWorkingDirectory().getAbsolutePath()||path=="/"){
        cout<<"Can't rename the working directory"<<endl;
        return;
    }
    vector<string> *dirs=split(path);
    if (fs.changeDirectoryFromAddress(*dirs,1,getArgs()[0]=='/', false)){
        bool isFound=false;
        for (int i=0;!isFound&&(unsigned) i<fs.getWorkingDirectory().getChildren().size();i++){
            if (fs.getWorkingDirectory().getChildren().at(i)->getName()==dirs->at(dirs->size()-1)){
                isFound=true;
                fs.getWorkingDirectory().getChildren().at(i)->setName(newName);

            }

        }
        if (!isFound)
            cout<<"No such file or directory"<<endl;

    }
    else {
        cout<<"The system cannot find the path specified" <<endl;
    }
    fs.setWorkingDirectory(initDir);
    delete dirs;
}
string RenameCommand::toString(){
    return "rename";
}