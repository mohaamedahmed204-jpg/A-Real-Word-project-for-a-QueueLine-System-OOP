# 🎟️ QueueLine System.           

A lightweight, robust, and clean C++ Object-Oriented implementation of a multi-queue ticketing system. This system simulates real-world queue line operations (such as banks, customer service centers, or hospitals), tracking client waiting times, dynamic queue positions, and ticket generation with precise metrics.

## 📌 Overview

The `clsQueueLine` class manages independent customer service lines by abstracting ticket issuance, dynamic service time recalculation, and queue visualization. It leverages C++ Standard Template Library (`std::queue`) and modern C++17 inline static features to maintain global queue metrics alongside instance-specific ticket lifecycles.

Key highlights:

  1. Dynamic waiting time recalculation for remaining clients upon serving a ticket.

  2. Bi-directional visual printing of the queue (Right-to-Left and Left-to-Right).

  3. Encapsulated state tracking for total tickets issued, currently waiting clients, and served clients.

## 🏗 Architecture & Design

### Data Structures

`stLineInfo` (Internal Ticket Payload)

    struct stLineInfo {
        string _DateAndTime;     // Timestamp of ticket generation
        size_t _WaitingClients;  // Number of clients ahead at generation time
        size_t _ServeTime;       // Total estimated waiting time in minutes
    };

### Class Attributes

Instance Scope: `_Pre` (Line prefix e.g., "A", "B"), `_WaitingTime` (Average serve time per client in minutes), `qu` (Queue of `stLineInfo`).

Static Scope: `_WaitingClients`, `_TotalTickets`, `_ServedClients` (C++17 `static inline` counters).

## ⚡ Core Operations

### 1. IssueTicket()

Captures current snapshot data: `_WaitingClients` ahead of the client, total estimated serve time, and a timestamp via `clsDate::GetDateTimeNow()`.

Pushes a structured ticket payload (`stLineInfo`) into the client processing queue (`qu`).

Increments global line statistics (`_WaitingClients` and `_TotalTickets`).

### 2. ServeNextClient()

Pops the front client from the queue.

Updates status counters by incrementing `_ServedClients` and decrementing `_WaitingClients`.

Dynamic Recalculation: Iterates through remaining queue items to decrease each client's remaining serve time (`_ServeTime`) by `_WaitingTime` units, ensuring accurate real-time queue states.

### 3. PrintInfo()

Renders a clean formatted panel displaying operational metrics for the current queue line instance:

  Line Prefix (`_Pre`)

  Total Tickets Issued (`_TotalTickets`)

  Total Served Clients (`_ServedClients`)

  Active Waiting Clients (`_WaitingClients`)


### 4. PrintTicketsLineRTL() & PrintTicketsLineLTR()

RTL (Right-to-Left): Visualizes client progression into the service desk (`A1 <-- A2 <-- A3`).

LTR (Left-to-Right): Visualizes the queue from head to tail (`A3 --> A2 --> A1`).

### 5. PrintAllTickets()

Creates an isolated pass-by-value copy of the client queue.

Sequentially prints formatted physical-style tickets including Ticket ID, Timestamp, Waiting Clients ahead, and Estimated Serve Time without modifying the live queue state.

## 💻 Quick Usage Example

    #include <iostream>
    #include "DS/clsQueueLine.h"
    
    using namespace std;
    
    int main() {
        clsQueueLine PayBillsQueue("A0", 10);
        clsQueueLine SubscriptionsQueue("B0", 5);
    
        PayBillsQueue.IssueTicket();
        PayBillsQueue.IssueTicket();
        PayBillsQueue.IssueTicket();
        PayBillsQueue.IssueTicket();
        PayBillsQueue.IssueTicket();
    
        cout << "\nPay Bills Queue Info:\n";
        PayBillsQueue.PrintInfo();
    
        PayBillsQueue.PrintTicketsLineRTL();
        PayBillsQueue.PrintTicketsLineLTR();
    
    
        PayBillsQueue.PrintAllTickets();
     
        PayBillsQueue.ServeNextClient();
        cout << "\nPay Bills Queue After Serving One client\n";
        PayBillsQueue.PrintInfo();
    
        cout << "\nSubscriptions Queue Info:\n";
    
        SubscriptionsQueue.IssueTicket();
        SubscriptionsQueue.IssueTicket();
        SubscriptionsQueue.IssueTicket();
       
      
        SubscriptionsQueue.PrintInfo();
    
        SubscriptionsQueue.PrintTicketsLineRTL();
        SubscriptionsQueue.PrintTicketsLineLTR();
     
        SubscriptionsQueue.PrintAllTickets();
        
        SubscriptionsQueue.ServeNextClient();
        cout << "\nSubscriptions Queue After Serving One client\n";
        SubscriptionsQueue.PrintInfo();
    
    
        return 0;
    }

### Output

Pay Bills Queue Info:
                                
                                ______________________________________

                                            Queue Info                  
                                ______________________________________

                                     Prefix         =  A0
                                     TotalTickets   =  5
                                     ServedClients  =  0
                                     WaitingClients =  5
                                ______________________________________

                        Tickets: A01 <-- A02 <-- A03 <-- A04 <-- A05

                        Tickets: A05 --> A04 --> A03 --> A02 --> A01


                                            ***Tickets***

                                ______________________________________

                                                  A01

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 0
                                          Serve Time in 0 Minutes.

                                ______________________________________

                                ______________________________________

                                                  A02

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 1
                                          Serve Time in 10 Minutes.

                                ______________________________________

                                ______________________________________

                                                  A03

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 2
                                          Serve Time in 20 Minutes.

                                ______________________________________

                                ______________________________________

                                                  A04

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 3
                                          Serve Time in 30 Minutes.

                                ______________________________________

                                ______________________________________

                                                  A05

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 4
                                          Serve Time in 40 Minutes.

                                ______________________________________


Pay Bills Queue After Serving One client
                                
                                ______________________________________

                                            Queue Info                  
                                ______________________________________

                                     Prefix         =  A0
                                     TotalTickets   =  5
                                     ServedClients  =  1
                                     WaitingClients =  4
                                ______________________________________


Subscriptions Queue Info:
                                
                                ______________________________________

                                            Queue Info                  
                                ______________________________________

                                     Prefix         =  B0
                                     TotalTickets   =  8
                                     ServedClients  =  1
                                     WaitingClients =  7
                                ______________________________________

                        Tickets: B01 <-- B02 <-- B03 <-- B04 <-- B05 <-- B06 <-- B07

                        Tickets: B07 --> B06 --> B05 --> B04 --> B03 --> B02 --> B01


                                            ***Tickets***

                                ______________________________________

                                                  B01

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 0
                                          Serve Time in 0 Minutes.

                                ______________________________________

                                ______________________________________

                                                  B02

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 1
                                          Serve Time in 5 Minutes.

                                ______________________________________

                                ______________________________________

                                                  B03

                                          12/8/2026 - 3:20:12
                                          Waiting Cleints = 2
                                          Serve Time in 10 Minutes.

                                ______________________________________


Subscriptions Queue After Serving One client
                                
                                ______________________________________

                                            Queue Info                  
                                ______________________________________

                                     Prefix         =  B0
                                     TotalTickets   =  8
                                     ServedClients  =  2
                                     WaitingClients =  6
                                ______________________________________

## 💡 Key Concepts Demonstrated

Object-Oriented Programming (`OOP`): Deep usage of encapsulation, constructor initialization, access specifiers (`private` / `public`), and modular design.

Dynamic State Management: Real-time queue traversal to adjust ticket parameters (`_ServeTime`) dynamically upon popping.

Non-Destructive Iteration: Copying container states (`queue<stLineInfo> q = qu;`) for read-only visualization operations to preserve runtime data integrity.

Static Class Members: Efficient memory utilization using static inline class attributes to share state across operations.

## 🛠 Technologies

Language: C++17 or higher (utilizes `static inline` member variable initialization).

STL Components: <`queue`>, <`iostream`>, <`string`>.

Custom Dependencies: `clsDate.h` (Used for date and timestamp generation).

## 🙏 Gratitude

Programming Advices Platform
Dr. Mohammed Abu-Hadhoud

[ https://programmingadvices.com ]

He was not just an instructor.

He was:

    A mentor
    A coach
    A guide
    A motivator
    A teacher who understands timing

Because the real secret of success in programming is:

    Proper progression
    Correct guidance
    The right timing to learn each concept

And that is exactly what we experienced
