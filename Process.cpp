#define _CRT_SECURE_NO_WARNINGS
#include "Process.h"
#include <windows.h>
#include <fstream>

using namespace std;

bool CreateProcessAndGetOutput(const std::string& path, std::string& output, const std::string& input, bool hide)
{
	DWORD ret = ERROR_SUCCESS;
	SECURITY_ATTRIBUTES sa = { 0, NULL, TRUE };
	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	CHAR tempPath[MAX_PATH] = "";
	CHAR inputTempFilePath[MAX_PATH] = "";
	CHAR outputTempFilePath[MAX_PATH] = "";
	CHAR cmd[500] = "";
	DWORD creationFlags = 0;

	GetTempPathA(MAX_PATH, tempPath);
	GetTempFileNameA(tempPath, "fwb", 0, inputTempFilePath);
	GetTempFileNameA(tempPath, "fwb", 0, outputTempFilePath);
	sprintf(cmd, "%s", path.c_str());

	si.dwFlags = STARTF_USESTDHANDLES;
	{
		ofstream ofs(inputTempFilePath);
		ofs << input;
	}
	si.hStdInput = CreateFileA(inputTempFilePath,
		GENERIC_READ, 0, &sa, OPEN_EXISTING, 0, NULL);
	si.hStdOutput = CreateFileA(outputTempFilePath,
		GENERIC_WRITE, 0, &sa, CREATE_ALWAYS, 0, NULL);

	if (hide)
		creationFlags |= CREATE_NO_WINDOW;

	if( CreateProcessA(NULL, cmd, NULL, NULL, TRUE, creationFlags,
		NULL, NULL, &si, &pi) )
	{
		DWORD wait = WaitForSingleObject(pi.hProcess, INFINITE);

		if( wait == WAIT_OBJECT_0 )
		{
			if( ! GetExitCodeProcess(pi.hProcess, &ret) )
				ret = GetLastError();
		}
		else ret = GetLastError();

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	CloseHandle(si.hStdOutput);

	if( ret == ERROR_SUCCESS )
	{
        HANDLE fileH = CreateFileA(outputTempFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

        if( fileH != INVALID_HANDLE_VALUE )
        {
            DWORD sz = GetFileSize(fileH, NULL);
            char* buffer = new char[sz];
            ZeroMemory(buffer, sz);
            ReadFile(fileH, buffer, sz, NULL, NULL);
            output = std::string(buffer, sz);
            delete buffer;
            CloseHandle(fileH);
			ret = ERROR_SUCCESS;
        }
	}

	DeleteFileA(outputTempFilePath);

	SetLastError(ret);
	return ret == ERROR_SUCCESS;
}
