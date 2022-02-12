#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

const wchar_t* creatorExePath = L"..\\Creator\\x64\\Release\\Creator.exe";
const wchar_t* reporterExePath = L"..\\Reporter\\x64\\Release\\Reporter.exe";
const wchar_t* sharedResourcesPath = L"..\\SharedResources\\";

int main()
{
    std::cout << "Hello!\nHere you can make files containing employees information and generate reports.\n" <<
        "_________________________________________________________________________________________________" <<
        "\n\nEnter source file name and records amount to make file with employee information.\n";

    wchar_t* source_filename = new wchar_t[256];
    wchar_t* recordsAmount=new wchar_t[20];

    STARTUPINFO si_creator;
    PROCESS_INFORMATION pi_creator;

    ZeroMemory(&si_creator, sizeof(si_creator));
    si_creator.cb = sizeof(si_creator);
    ZeroMemory(&pi_creator, sizeof(pi_creator));

    std::cout << "Source file name: ";

    std::wcin >> source_filename;

    std::cout << "Records amount: ";

    std::wcin >> recordsAmount;

    int sharedPathLength = wcslen(sharedResourcesPath);
    int cmd_line_creator_size = wcslen(creatorExePath) + wcslen(source_filename) + wcslen(recordsAmount) + 3 + sharedPathLength;
    wchar_t* cmd_line_creator = new wchar_t[cmd_line_creator_size]{};
    int filepath_size = sharedPathLength + 1 + wcslen(source_filename);
    wchar_t* filepath = new wchar_t[filepath_size];

    wcscpy_s(filepath, filepath_size, sharedResourcesPath);
    wcscpy_s(cmd_line_creator, cmd_line_creator_size, creatorExePath);
    wcscat_s(cmd_line_creator, cmd_line_creator_size, L" ");
    wcscat_s(cmd_line_creator, cmd_line_creator_size, recordsAmount);
    wcscat_s(cmd_line_creator, cmd_line_creator_size, L" ");
    wcscat_s(cmd_line_creator, cmd_line_creator_size, filepath);
    wcscat_s(cmd_line_creator, cmd_line_creator_size, source_filename);

    bool isSuccessfullyCtreated_creator = CreateProcess(creatorExePath,   // No module name (use command line)
        cmd_line_creator,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si_creator,            // Pointer to STARTUPINFO structure
        &pi_creator);         // Pointer to PROCESS_INFORMATION structure

    if (isSuccessfullyCtreated_creator) {
        WaitForSingleObject(pi_creator.hProcess, INFINITE);

        DWORD lpExitCode;
        //ZeroMemory(&lpExitCode, sizeof(LPDWORD));

        if (GetExitCodeProcess(
            pi_creator.hProcess,
            &lpExitCode
        )) {
            if (lpExitCode != 0) {
                std::cerr << "Creator process exited with non-zero code " << lpExitCode << std::endl << "Job aborted\n";
                return 1;
            }
            else {
                std::cout << "Creator process exited with code 0.\n";
            }
        }
        else {
            std::cerr << "Unknown error while trying to get Creator exit code. Job aborted\n";
            return 1;
        }



        // Close process and thread handles. 
        CloseHandle(pi_creator.hProcess);
        CloseHandle(pi_creator.hThread);

        std::cout << "Creator.exe - Done!\n";
    }
    else {
        std::cout << "Process for Creator failed to be created. Job aborted\n";
        return 1;
    }

    std::cout << "\n";
    
    std::ifstream fin;
    wcscat_s(filepath, filepath_size, source_filename);
    fin.open(filepath);

    if (!fin.is_open()) {
        std::cout << "Manager.exe failed to open source file. Job aborted\n";
        return 1;
    }
    std::cout << "************************************WRITTEN FILE******************************************\n";

    std::string strTemp;
    while (getline(fin, strTemp)) {
        std::cout << strTemp;
    }

    std::cout << "\n******************************************************************************************\n";

    wchar_t* report_filename = new wchar_t[100];
    wchar_t* hourlyWages = new wchar_t[20];

    std::cout << "\n";

    std::cout << "Please, enter report file name and hourly wage.\n";
    std::cout << "Report file name = ";

    std::wcin >> report_filename;
    std::cout << "Hourly wage = ";
    std::wcin >> hourlyWages;

    int cmd_line_reporter_size = wcslen(filepath) + wcslen(reporterExePath) + wcslen(report_filename) + wcslen(hourlyWages) + 4 + sharedPathLength;
    wchar_t* cmd_line_reporter = new wchar_t[cmd_line_reporter_size]{};
    int report_filepath_size = sharedPathLength + 1 + wcslen(report_filename);
    wchar_t* report_filepath = new wchar_t[report_filepath_size];

    wcscpy_s(report_filepath, report_filepath_size, sharedResourcesPath);
    wcscpy_s(cmd_line_reporter, cmd_line_reporter_size, reporterExePath);
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, L" ");
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, filepath);
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, L" ");
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, report_filepath);
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, report_filename);
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, L" ");
    wcscat_s(cmd_line_reporter, cmd_line_reporter_size, hourlyWages);

    STARTUPINFO si_reporter;
    PROCESS_INFORMATION pi_reporter;

    ZeroMemory(&si_reporter, sizeof(si_reporter));
    si_reporter.cb = sizeof(si_reporter);
    ZeroMemory(&pi_reporter, sizeof(pi_reporter));

    bool isSuccessfullyCtreated_reporter = CreateProcess(reporterExePath,   // No module name (use command line)
        cmd_line_reporter,        // Command line
        NULL,                     // Process handle not inheritable
        NULL,                     // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si_reporter,            // Pointer to STARTUPINFO structure
        &pi_reporter);         // Pointer to PROCESS_INFORMATION structure

    if (isSuccessfullyCtreated_reporter) {
        WaitForSingleObject(pi_reporter.hProcess, INFINITE);

        DWORD exitCode;

        if (GetExitCodeProcess(
            pi_reporter.hProcess,
            &exitCode
        )) {
            if (exitCode != 0) {
                std::cerr << "Reporter process exited with non-zero code " << exitCode << std::endl << "Job aborted\n";
                return 1;
            }
            else {
                std::cout << "Reporter process exited with code 0.\n";
            }
        }
        else {
            std::cerr << "Unknown error while trying to get Reporter exit code. Job aborted\n";
            return 1;
        }

        // Close process and thread handles. 
        CloseHandle(pi_reporter.hProcess);
        CloseHandle(pi_reporter.hThread);

        std::cout << "Reporter.exe - Done!\n";
    }
    else {
        std::cout << "Reporter.exe - Failed!\nManager.exe job aborted due to error in Reporter.exe\n";
        return 1;
    }

    std::ifstream finReport;
    wcscat_s(report_filepath, report_filepath_size, report_filename);
    finReport.open(report_filepath);
    std::cout << "\n";

    std::cout << "************************************GENERATED REPORT FILE******************************************\n";
    std::string str;
    while (getline(finReport, str)) {
        std::cout << str << "\n";
    }
    std::cout << "\n***************************************************************************************************\n\n\n";

    return 0;
}
