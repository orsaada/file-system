#include <type_traits>
#include <iostream>
#include "Commands.h"
#include "GlobalVariables.h"

using namespace std;

PwdCommand::PwdCommand(string args):BaseCommand(args){
}
void PwdCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    std::cout<<fs.getWorkingDirectory().getAbsolutePath()<<endl;
} // Every derived class should implement this function according to the document (pdf)
string PwdCommand::toString(){
    return "pwd";
}