#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Files.h"
#include "Commands.h"

#include <string>
#include <vector>

using namespace std;

class Environment {
private:
    vector<BaseCommand*> commandsHistory;
    FileSystem fs;

public:
    Environment();
    void start();
    FileSystem& getFileSystem(); // Get a reference to the file system
    void addToHistory(BaseCommand *command); // Add a new command to the history
    const vector<BaseCommand*>& getHistory() const; // Return a reference to the history of commands
    BaseCommand* detectCommand(string input);
    Environment(const Environment &other); //Copy Constructor
    Environment& operator=(const Environment& other);// Copy Assignment Operator
    Environment(Environment &&other);// Move Constructor
    Environment& operator=(Environment&& other);//Move assignment operator
    ~Environment();//Destructor
};

#endif