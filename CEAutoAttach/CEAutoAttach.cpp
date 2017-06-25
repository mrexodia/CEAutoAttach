#include <windows.h>
#include <shellapi.h>

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    //Extract the LUA autorun script.
    HANDLE hFile = CreateFileW(L"autorun\\CEAutoAttach.lua", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile != INVALID_HANDLE_VALUE)
    {
        DWORD NumberOfBytesWritten = 0;
        char szAutorunScript[] = "openProcess(tonumber(os.getenv('CEAutoAttach')))";
        WriteFile(hFile, szAutorunScript, sizeof(szAutorunScript) - 1, &NumberOfBytesWritten, NULL);
        CloseHandle(hFile);
    }

    //Check the commandline for the PID to attach to.
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if(argc > 1)
        SetEnvironmentVariableW(L"CEAutoAttach", argv[1]);
    LocalFree(argv);
    
    //Execute Cheat Engine.
    ShellExecuteW(NULL, L"open", L"Cheat Engine.exe", NULL, NULL, SW_SHOWDEFAULT);

    return 0;
}