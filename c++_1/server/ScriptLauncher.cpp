//
// Created by andung on 2019-05-06.
//
// Accepting command of "usec#crawl#url#keyword"
//

#include "ScriptLauncher.h"
#include <regex>
#include <iostream>

#define SCRIPT_LOCATION "/home/andung/programming-test/bash_1/crawl.sh"


void ScriptLauncher::Tokenize(std::string const &str, const char* delim,
			  std::vector<std::string> &out)
{
	char *token = strtok(const_cast<char*>(str.c_str()), delim);
	while (token != nullptr)
	{
		out.push_back(std::string(token));
		token = strtok(nullptr, delim);
	}
}


int ScriptLauncher::Execute(std::string command, std::string& output) {

	std::regex commandRegex("usec#crawl#.+#.+");

	if (std::regex_match(command, commandRegex)) {

		std::vector<std::string> commandParams;
		Tokenize(command, "#", commandParams);

		std::ostringstream finalCommand;
		finalCommand << SCRIPT_LOCATION << " " << commandParams.at(2) << " " << commandParams.at(3);

		std::array<char, 128> buffer;
		std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(finalCommand.str().c_str(), "r"), pclose);

		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			output += buffer.data();
		}

		return 0;

	} else {
		return -1;
	}

}