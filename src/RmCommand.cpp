#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"

RmCommand::RmCommand(string args):BaseCommand(args){

}
void RmCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;

    if (getArgs()==fs.getWorkingDirectory().getAbsolutePath()||getArgs()=="/"){ //todo need to fix condition
        cout<<"Can't remove directory"<<endl;
        return;
    }
    Directory* init=&fs.getWorkingDirectory();
    vector<string> *dirs=split(getArgs());
    if (fs.changeDirectoryFromAddress(*dirs,1,getArgs()[0]=='/', false)){
        bool isFound=false;
        for (int i=0;!isFound&&(unsigned) i<fs.getWorkingDirectory().getChildren().size();i++){
            if (fs.getWorkingDirectory().getChildren().at(i)->getName()==dirs->at(dirs->size()-1)){
                isFound=true;
                fs.getWorkingDirectory().removeFile(dirs->at(dirs->size()-1));
            }

        }
        if (!isFound)
            cout<<"No such file or directory"<<endl;
    }
    else {
        cout<<"The system cannot find the path specified" <<endl;
    }
    fs.setWorkingDirectory(init);
    delete dirs;
}

string RmCommand::toString(){
    return "rm";
}