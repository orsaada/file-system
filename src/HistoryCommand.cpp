#include <string>
#include <iostream>
#include "FileSystem.h"
#include "Commands.h"
#include "GlobalVariables.h"

using namespace std;

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> & history):BaseCommand(args), history(history){

}
void HistoryCommand::execute(FileSystem & fs) {
    if (verbose==2||verbose==3)
        cout<<"history"+getArgs()<<endl;
    for (int i=0;(unsigned) i<history.size(); i++) {
        cout << i << " " << history.at(i)->toString() << " "<<history.at(i)->getArgs()<<endl;
    }
}
string HistoryCommand::toString(){
    return "history";
}




