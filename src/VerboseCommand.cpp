#include <string>
#include <iostream>
#include "FileSystem.h"
#include "Commands.h"
#include "GlobalVariables.h"

using namespace std;

VerboseCommand::VerboseCommand(string args):BaseCommand(args){

    };
void VerboseCommand::execute(FileSystem & fs) { // Every derived class should implement this function according to the document (pdf)
    if (verbose == 2 || verbose == 3)
        cout << toString() + " " + getArgs() << endl;
    if (!(getArgs() == "0" || getArgs() == "1" || getArgs() == "2" || getArgs() == "3"))
        cout << "Wrong verbose input" << endl;
    else {
        int verNum = stoi(getArgs());
        verbose = verNum;
    }
}

string VerboseCommand::toString(){
	return "verbose";
}



