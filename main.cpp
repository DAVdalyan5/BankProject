#include "Bank.h"
#include <iostream>
#include <sstream>
#include <string>

void displayHelp() {
    std::cout << "Commands:\n"
              << "  info [account_id] - Display account details\n"
              << "  freeze [account_id] - Freeze account\n"
              << "  unfreeze [account_id] - Unfreeze account\n"
              << "  transfer [from_id] [to_id] [amount] - Transfer funds between accounts\n"
              << "  modify [amount] - Modify balance for all unfrozen accounts\n"
              << "  setlimits [account_id] [min_balance] [max_balance] - Set account limits\n"
              << "  exit - Exit the program\n";
}

int main() {
    int num_accounts, max_balance;
    std::cout << "Enter the number of accounts and maximum balance: ";
    std::cin >> num_accounts >> max_balance;
    Bank bank(num_accounts, max_balance);

    std::string input, command;
    int id, id2, amount;

    displayHelp();

    std::cin.ignore(); // Ignore the newline left in the input buffer.
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> command;

        try {
            if (command == "exit") {
                break;
            } else if (command == "info") {
                iss >> id;
                bank.printAccountInfo(id);
            } else if (command == "freeze") {
                iss >> id;
                bank.setAccountFrozen(id, true);
            } else if (command == "unfreeze") {
                iss >> id;
                bank.setAccountFrozen(id, false);
            } else if (command == "transfer") {
                iss >> id >> id2 >> amount;
                bank.transfer(id, id2, amount);
            } else if (command == "modify") {
                iss >> amount;
                bank.modifyAllBalances(amount);
            } else if (command == "setlimits") {
                iss >> id >> id2 >> amount; // Here id2 is min_balance and amount is max_balance
                bank.setAccountLimits(id, id2, amount);
            } else {
                std::cout << "Unknown command. Please try again.\n";
                displayHelp();
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
