// starthide.cpp: Start a process without windows.
#include "Process.h"
#include "Args.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	Args args;
	ParseCommandLine(argc, argv, args);

	if (args.)
	{
		string command = argv[1];

		for (int i = 2; i < argc; ++i)
			command = command + " " + argv[i];

		string input, output;

		if (CreateProcessAndGetOutput(command, output, input, true))
			return 0;

		return (int) GetLastError();
	}
	else cout << "Usage: starthide [--output <file-path>] <cmd> <args>\n";
}
