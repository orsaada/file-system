#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"
#include <string>
#include <iostream>

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> & history):
        BaseCommand(args),history(history)
{ }

void ExecCommand::execute(FileSystem & fs){
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    int index;
    try {
        index = stoi(getArgs());
    }
    catch(...) {
        cout << "Command not found"<<endl;
        return;
    }
    if((unsigned) index < history.size() && index >= 0)
        history.at(index)->execute(fs);
    else {
        cout << "Command not found"<<endl;
    }
}

string ExecCommand::toString(){ //todo
    return "exec";
}