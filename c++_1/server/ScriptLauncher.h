//
// Created by andung on 2019-05-06.
//

#ifndef SERVER_SCRIPTLAUNCHER_H
#define SERVER_SCRIPTLAUNCHER_H

#include <string>
#include <vector>

class ScriptLauncher {

public:
	static int Execute(std::string command, std::string& output);

private:
	static void Tokenize(std::string const &str, const char* delim,
						 std::vector<std::string> &out);
};


#endif //SERVER_SCRIPTLAUNCHER_H
