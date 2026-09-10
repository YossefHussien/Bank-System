# Bank & User Management System

A C++ console-based application designed to manage bank clients, user accounts, and financial transactions. This project was developed as a hands-on training application to master core C++ programming concepts, file handling, and system design.

## Features

*   **Authentication System:** Secure login screen for users.
*   **User Management:** Full CRUD operations (Create, Read, Update, Delete) for system users.
*   **Role-Based Access Control (RBAC):** Advanced permission management using bitwise operations to grant or deny access to specific screens and functionalities.
*   **Client Management:** Manage bank clients' data including account numbers, pin codes, names, and phone numbers.
*   **Transaction System:** Perform financial operations like deposits, withdrawals, and viewing total bank balances with validation checks.
*   **Data Persistence:** All user and client data are persistently saved and loaded using text files (`Users.txt` and `Clients.txt`).

## Technologies & Concepts Applied

*   **Language:** C++
*   **Data Structures:** `std::vector`, `struct`, `enum`.
*   **File I/O:** Reading from and writing to external `.txt` files using `<fstream>`.
*   **Bitwise Operations:** Used efficiently for handling user permissions.
*   **Modular Design:** Utilizing custom header files (`MyLibrary/`) for input validation, math functions, and output formatting.

## How to Run the Project

1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/YossefHussien/BankSystem.git](https://github.com/YossefHussien/BankSystem.git)
