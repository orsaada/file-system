
#include "Commands.h"

BaseCommand::BaseCommand(string args):args(args){
}
string BaseCommand::getArgs(){
    return args;
}

vector<string> *BaseCommand::split(string s) {

    int count=0;
    vector<string> *path=new vector<string>();
    if(s.size() == 0)
        return path;
    for (int i=0;(unsigned) i<s.size();i++) {
        if (s.at(i) == '/')
            count++;
    }
    if (count==0) {
        path->push_back(s);
        return path;
    }
    else {
        for (int i = 0; i <= count; i++) {
            int whereSlash = s.find_first_of('/');
            if (whereSlash!=-1) {
                path->push_back(s.substr(0, whereSlash));
                s=s.substr(whereSlash+1);
            } else
                path->push_back(s);

        }
        return path;
    }

}

BaseCommand::~BaseCommand(){} //Destructor