/** Interpreta argumentos da linha de comando.

@author Wanderley Caloni <caloni@bitforge.com.br>
@date 2015-06
*/
#pragma once
#include <map>
#include <string>

typedef std::map<std::string, std::string> Args;

void ParseCommandLine(int argc, char* argv[], Args& args);
