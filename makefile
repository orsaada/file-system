 

all: fs

fs: bin/BaseCommand.o bin/CdCommand.o bin/CpCommand.o bin/ErrorCommand.o bin/ExecCommand.o bin/HistoryCommand.o bin/LsCommand.o  bin/MkdirCommand.o bin/MkfileCommand.o bin/mvCommand.o bin/PwdCommand.o bin/RenameCommand.o bin/RmCommand.o bin/VerboseCommand.o bin/Environment.o bin/Directory.o bin/File.o bin/BaseFile.o bin/FileSystem.o bin/Main.o





	g++ -o bin/fs bin/BaseCommand.o bin/CdCommand.o bin/CpCommand.o bin/ErrorCommand.o bin/ExecCommand.o bin/HistoryCommand.o bin/LsCommand.o  bin/MkdirCommand.o bin/MkfileCommand.o bin/mvCommand.o bin/PwdCommand.o bin/RenameCommand.o bin/RmCommand.o bin/VerboseCommand.o bin/Environment.o bin/Directory.o bin/BaseFile.o bin/File.o bin/FileSystem.o bin/Main.o


bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp

bin/BaseCommand.o: src/BaseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseCommand.o src/BaseCommand.cpp
bin/BaseFile.o: src/BaseFile.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/BaseFile.o src/BaseFile.cpp
bin/CdCommand.o: src/CdCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CdCommand.o src/CdCommand.cpp
bin/CpCommand.o: src/CpCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/CpCommand.o src/CpCommand.cpp
bin/ErrorCommand.o: src/ErrorCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ErrorCommand.o src/ErrorCommand.cpp
bin/ExecCommand.o: src/ExecCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/ExecCommand.o src/ExecCommand.cpp
bin/HistoryCommand.o: src/HistoryCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/HistoryCommand.o src/HistoryCommand.cpp
bin/LsCommand.o: src/LsCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/LsCommand.o src/LsCommand.cpp
bin/MkdirCommand.o: src/MkdirCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MkdirCommand.o src/MkdirCommand.cpp
bin/MkfileCommand.o: src/MkfileCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/MkfileCommand.o src/MkfileCommand.cpp
bin/mvCommand.o: src/mvCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/mvCommand.o src/mvCommand.cpp
bin/PwdCommand.o: src/PwdCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/PwdCommand.o src/PwdCommand.cpp
bin/RenameCommand.o: src/RenameCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RenameCommand.o src/RenameCommand.cpp
bin/RmCommand.o: src/RmCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/RmCommand.o src/RmCommand.cpp
bin/VerboseCommand.o: src/VerboseCommand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/VerboseCommand.o src/VerboseCommand.cpp
	
bin/Environment.o: src/Environment.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Environment.o src/Environment.cpp
bin/Directory.o: src/Directory.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Directory.o src/Directory.cpp

bin/File.o: src/File.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/File.o src/File.cpp

bin/FileSystem.o: src/FileSystem.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/FileSystem.o src/FileSystem.cpp








clean:
	rm -f bin/* 
