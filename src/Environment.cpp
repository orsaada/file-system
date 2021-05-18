#include "Files.h"
#include "Commands.h"
#include "Environment.h"
#include "GlobalVariables.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

Environment::Environment():commandsHistory(),fs() {
}

void Environment::start() {
    verbose=0;
    BaseCommand *command = nullptr;
    char input[100];
    while (true) {
        string str;
        if (fs.getWorkingDirectory().getAbsolutePath().length()>=2)//solves problem where directory was "//"
            cout<< fs.getWorkingDirectory().getAbsolutePath().substr(1) + ">";
        else
            cout<< fs.getWorkingDirectory().getAbsolutePath() + ">" ;
        cin.getline(input,sizeof(input));
        command = detectCommand(input);
        if (command != nullptr) {
            command->execute(fs);
            addToHistory(command);
        }
        else {
            return;
        }
    }
}

FileSystem& Environment::getFileSystem() {
    return fs;
} // Get a reference to the file system

void Environment::addToHistory(BaseCommand *command) {
    commandsHistory.push_back(command);
}// Add a new command to the history

const vector<BaseCommand*>& Environment::getHistory() const{
    return commandsHistory;
} // Return a reference to the history of commands

BaseCommand *Environment::detectCommand(string input) {
    int firstSpace = input.find_first_of(' ');
    BaseCommand *command = nullptr;
    string commandString;
    if (firstSpace!=-1)
        commandString = input.substr(0, firstSpace);
    else
        commandString=input;
    if (commandString == "cd")
        command = new CdCommand(input.substr(firstSpace+1));
    else if (commandString == "cp")
        command = new CpCommand(input.substr(firstSpace+1));
    else if (commandString == "exec")
        command = new ExecCommand(input.substr(firstSpace+1), commandsHistory);
    else if (commandString == "history")
        command = new HistoryCommand("", commandsHistory);
    else if (commandString == "ls") {
        int startArgs = 2;
        if (input.length() > 2)
            startArgs = firstSpace + 1;
        command = new LsCommand(input.substr(startArgs));
    }
    else if (commandString == "mkdir")
        command = new MkdirCommand(input.substr(firstSpace+1));
    else if (commandString == "mkfile")
        command = new MkfileCommand(input.substr(firstSpace+1));
    else if (commandString == "mv")
        command = new MvCommand(input.substr(firstSpace+1));
    else if (commandString == "pwd")
        command = new PwdCommand("");
    else if (commandString == "rename")
        command = new RenameCommand(input.substr(firstSpace+1));
    else if (commandString == "rm")
        command = new RmCommand(input.substr(firstSpace+1));
    else if (commandString == "verbose")
        command = new VerboseCommand(input.substr(firstSpace+1));
    else if (commandString == "exit")
        return nullptr;
    else
        command = new ErrorCommand(input);
    return command;
}

Environment::Environment(const Environment &other):
        commandsHistory(),fs(other.fs) {
    if (verbose==1||verbose==3)
        cout<<"Environment::Environment(const Environment &other)"<<endl;
    vector<BaseCommand*>::const_iterator it=other.commandsHistory.begin();
    for (int i=0;(unsigned) i<other.commandsHistory.size();i++){
        BaseCommand* command=other.commandsHistory.at(i);
        commandsHistory.push_back(command);
    }
}// Copy Constructor

Environment& Environment::operator=(const Environment& other) {
    if (verbose==1||verbose==3)
        cout<<"Environment& Environment::operator=(const Environment& other)"<<endl;
    if(&other!=this){
        fs=other.fs; //todo is it ok? to call the copy assignment of fs?
        vector<BaseCommand*>::const_iterator it=other.commandsHistory.begin();
        for (int i=0;(unsigned) i<other.commandsHistory.size();i++) {
            BaseCommand* command=other.commandsHistory.at(i);
            commandsHistory.push_back(command);
        }

    }
    return *this;
}// Copy Assignment Operator


Environment::Environment(Environment &&other):commandsHistory(),fs(other.fs) {
    if (verbose==1||verbose==3)
        cout<<"Environment::Environment(Environment &&other)"<<endl;
    vector<BaseCommand*>::iterator it=other.commandsHistory.begin();
    for (int i=0;(unsigned) i<other.commandsHistory.size();i++) {
        BaseCommand* command=other.commandsHistory.at(i);
        addToHistory(command);
    }

    fs=other.fs;//todo need it or should it be in the intilization list
} // Move Constructor

Environment& Environment::operator=(Environment&& other) {
    if (verbose==1||verbose==3)
        cout<<"Environment& Environment::operator=(Environment&& other"<<endl;
    if(this!=&other){
        fs=other.fs;
        for (int i=0;(unsigned) i<other.commandsHistory.size();i++) {
            BaseCommand* c=other.commandsHistory.at(i);
            commandsHistory.push_back(c);
        }
        fs= other.fs;
    }
    return *this;
}//Move assignment operator

Environment::~Environment(){
    if (verbose==1||verbose==3)
        cout<<"Environment::~Environment()"<<endl;
    for (int i=0;(unsigned)i<commandsHistory.size();i++)
        delete commandsHistory.at(i);
}//Destructor

