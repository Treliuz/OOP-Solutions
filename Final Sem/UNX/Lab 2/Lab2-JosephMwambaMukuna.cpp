#include <iostream>
#include <vector>
#include <string>
#include "pidUtil.h"

int main() {
    vector<int> pids;
    ErrStatus status = GetAllPids(pids);
    //TODO: Iterate over vector of pids with for of loop
    if (status != Err_OK) {
        cout << GetErrorMsg(status) << endl;
    } else {
        for (int pid : pids) {
            string name;
            ErrStatus nameStatus = GetNameByPid(pid, name);
            if (nameStatus == Err_OK)
                cout << "PID: " << pid << ": " << name << endl;
            else
                cout << "Unable to retrieve name for PID " << pid << ": " << GetErrorMsg(nameStatus) << endl;
        }
    }

    //TODO: Same thing but with specific name
    int pid = 1;
    string name;
    status = GetNameByPid(pid, name);
    if (status == Err_OK) 
        cout << "\nPID: " << pid << "is " << name << endl;
    else 
        cout << "\nUnable to retrieve name for PID: " << pid << ": " << GetErrorMsg(status) << endl;
    
    int pid;
    string name = "Lab2";
    status = GetPidByName(name, pid);
    if (status == Err_OK)
        cout << "\nPID of " << name << ": " << pid << endl;
    else
        cout << "\nUnable to retrieve PID for " << name << ": " << GetErrorMsg(status) << endl;

    //TODO: Non-excistent attempt
    name = "Lab22";
    status = GetPidByName(name, pid);
    if (status == Err_OK) 
        cout << "\nPID of \"" << name << "\": " << pid << endl;
    else
        cout << "\nError getting PID for " << name << ": " << GetErrorMsg(status) << endl;

    return 0;

}