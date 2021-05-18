
#include <iostream>
#include "Commands.h"
#include "GlobalVariables.h"
using namespace std;

CdCommand::CdCommand(string args):BaseCommand(args){

}
void CdCommand::execute(FileSystem & fs){
   if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    if(getArgs()=="/")
        fs.setWorkingDirectory(&fs.getRootDirectory());
    else
    {
        vector<string> *dirs = split(getArgs());
        if (!fs.changeDirectoryFromAddress(*dirs, 0, getArgs()[0] == '/', false)) {
            cout << "The system cannot find the path specified" << endl;
        }

        delete dirs;
    }
    return;
}
string CdCommand::toString(){ //todo
    return "cd";
};
