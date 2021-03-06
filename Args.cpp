#include "Args.h"
#include "Using.h"
#include <map>
#include <string>

USING_FILE("0.0.1");


void ParseCommandLine(int argc, char* argv[], Args& args)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string cmd = argv[i];
		std::string arg;
		if (i < argc - 1 && argv[i + 1][0] != '-')
		{
			arg = argv[i + 1];
			++i;
		}
		std::string oldArg = args[cmd];
		args[cmd] = arg;
		if (oldArg.size())
		{
			oldArg = oldArg + "\n" + arg;
			args[cmd] = oldArg;
		}
	}
}
