#pragma once
#include <iostream>
#include <queue>
#include "clsDate.h"

using namespace std;

class clsQueueLine {
private:

    string _Pre;
    size_t _WaitingTime;

    static inline size_t _WaitingClients  = 0;
    static inline size_t _TotalTickets  = 0;
    static inline size_t _ServedClients = 0;

    struct stLineInfo {
        string _DateAndTime;
        size_t _WaitingClients;
        size_t _ServeTime;
    };

    
public:
    queue<stLineInfo> qu;

    clsQueueLine(const string &Pre, const size_t &TimeToWait) {
        _Pre = Pre;
        _WaitingTime = TimeToWait;
    }

    void IssueTicket() {
        stLineInfo stData;
        stData._WaitingClients = qu.size();
        stData._ServeTime = _WaitingTime * qu.size();
        stData._DateAndTime = clsDate::GetDateTimeNow();
        qu.push(stData);

        ++_WaitingClients, ++_TotalTickets;
    }

    void PrintInfo() {
        cout << "\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t            Queue Info                  \n";
        cout << "\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t     Prefix         =  " << _Pre << '\n';
        cout << "\t\t\t\t     TotalTickets   =  " << _TotalTickets <<'\n';
        cout << "\t\t\t\t     ServedClients  =  " << _ServedClients << '\n';
        cout << "\t\t\t\t     WaitingClients =  " << _WaitingClients << "\n";
        cout << "\t\t\t\t______________________________________\n\n";
    }

    void PrintTicketsLineRTL() {
        cout << "\t\t\tTickets: ";
        for(size_t i = 1; i <= _WaitingClients; ++i) {
            cout << _Pre << i;
            if(i != _WaitingClients) cout << " <-- ";
        } cout << "\n\n";
    }

    void PrintTicketsLineLTR() {
        cout << "\t\t\tTickets: ";
        for(size_t i = _WaitingClients; i > 0; --i) {
            cout << _Pre << i;
            if(i != 1) cout << " --> ";
        } cout << "\n\n";
    }

    void PrintAllTickets() {
        queue<stLineInfo> q = qu;
        cout << "\n\t\t\t\t\t    ***Tickets***\n\n";
        for(size_t i = 1; q.size(); ++i) {
            cout << "\t\t\t\t______________________________________\n\n";
            cout << "\t\t\t\t\t          " << _Pre << i << "\n\n";
            cout << "\t\t\t\t\t  " << q.front()._DateAndTime;
            cout << "\t\t\t\t\t  Waiting Cleints = " << q.front()._WaitingClients << '\n';
            cout << "\t\t\t\t\t  Serve Time in " << q.front()._ServeTime << " Minutes.\n\n";
            cout << "\t\t\t\t______________________________________\n\n";
            q.pop();
        }
    }

    void ServeNextClient() {
        if(!qu.empty()) {
            ++_ServedClients, --_WaitingClients;
            qu.pop(); size_t n = qu.size(); 
            while(n--) {
                stLineInfo stTemp = qu.front();
                qu.pop();
                stTemp._ServeTime -= _WaitingTime;
                qu.push(stTemp);
            }
        }
    }
};


