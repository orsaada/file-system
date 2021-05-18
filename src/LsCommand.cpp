
#include "Commands.h"
#include "iostream"
#include "GlobalVariables.h"

LsCommand::LsCommand(string args):BaseCommand(args){

}
void LsCommand::execute(FileSystem & fs) {
    if (verbose==2||verbose==3)
        cout<<toString()+" "+getArgs()<<endl;
    string input=getArgs();
    bool sort=false;
    if(input.substr(0,2) == "-s")
    {
        sort = true;
        input = input.substr(2);
    }
    Directory* curDir=&fs.getWorkingDirectory();
    if(input[0]== '/')
    {
        curDir = &fs.getRootDirectory();
        input=input.substr(1);
    }
    auto strings=split(input);
    if(strings->size() == 0)
    {
        print(curDir,sort);
        delete strings;
        return;
    }
    vector<string>::iterator it=strings->begin();
    while(it != strings->end())
    {
        if(*it == ".." && curDir->getParent() != NULL )
            curDir=curDir->getParent();
        else if(curDir->fileExists(*it)) {
            BaseFile *file = curDir->getFile(*it);
            if (file->getType() == "DIR")
                curDir=(Directory*)file;
            else
            {
                cout<<"The system cannot find the path specified"<<endl;
                delete strings;
                return;
            }
        }
        else
        {
            cout<<"The system cannot find the path specified"<<endl;
            delete strings;
            return;
        }
        it++;
    }
    print(curDir,sort);
    delete strings;
}

void LsCommand::print(Directory* curDir,bool sort){
    if(sort)
        curDir->sortBySize();
    else
        curDir->sortByName();
    auto child=curDir->getChildren();
    for (int i=0;(unsigned) i<child.size(); i++) {
        cout<<child.at(i)->getType()+"  ";
        cout<<child.at(i)->getName()+" ";
        cout<<child.at(i)->getSize()<<endl;
    }
}

string LsCommand::toString(){
    return "ls";
}
