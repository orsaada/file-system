cmake_minimum_required(VERSION 3.8)
project(project1_cpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        BaseCommand.cpp
        BaseFile.cpp
        CdCommand.cpp
        Commands.h
        CpCommand.cpp
        Directory.cpp
        Environment.cpp
        Environment.h
        ErrorCommand.cpp
        ExecCommand.cpp
        File.cpp
        Files.h
        FileSystem.cpp
        FileSystem.h
        GlobalVariables.h
        HistoryCommand.cpp
        LsCommand.cpp
        Main.cpp
        MkdirCommand.cpp
        MkfileCommand.cpp
        mvCommand.cpp
        PwdCommand.cpp
        RenameCommand.cpp
        RmCommand.cpp
        VerboseCommand.cpp)

add_executable(project1_cpp ${SOURCE_FILES})