#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"

ErrorCommand::ErrorCommand(string args):BaseCommand(args){

}
void ErrorCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<getArgs()<<endl;
    int whereSpace=getArgs().find_first_of(' ');
    if (whereSpace==-1||(unsigned) whereSpace==getArgs().length()-1)
        cout << getArgs()+": Unknown command"<<endl;
    else
        cout << getArgs().substr(0,whereSpace)+": Unknown command"<<endl;
}

string ErrorCommand::toString(){ //todo
    return "error";
}