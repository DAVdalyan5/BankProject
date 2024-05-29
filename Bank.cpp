#include "Bank.h"

Bank::Bank(int n, int max_balance) {
    accounts.resize(n, Account(0, max_balance));
}

void Bank::printAccountInfo(int account_id) const {
    std::lock_guard<std::mutex> lock(mutex);
    if (account_id < 0 || account_id >= accounts.size()) {
        throw std::out_of_range("Invalid account number.");
    }
    const Account& acc = accounts[account_id];
    std::cout << "Account " << account_id << ": Balance=" << acc.balance
              << ", MinBalance=" << acc.min_balance << ", MaxBalance=" << acc.max_balance
              << ", Frozen=" << (acc.frozen ? "Yes" : "No") << std::endl;
}

void Bank::setAccountFrozen(int account_id, bool freeze) {
    std::lock_guard<std::mutex> lock(mutex);
    if (account_id < 0 || account_id >= accounts.size()) {
        throw std::out_of_range("Invalid account number.");
    }
    accounts[account_id].frozen = freeze;
}

void Bank::transfer(int from_id, int to_id, int amount) {
    std::lock_guard<std::mutex> lock(mutex);
    if (from_id < 0 || from_id >= accounts.size() || to_id < 0 || to_id >= accounts.size()) {
        throw std::out_of_range("Invalid account number.");
    }
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive.");
    }
    Account& from_acc = accounts[from_id];
    Account& to_acc = accounts[to_id];
    if (from_acc.frozen || to_acc.frozen) {
        throw std::runtime_error("One of the accounts is frozen.");
    }
    if (from_acc.balance - amount < from_acc.min_balance || to_acc.balance + amount > to_acc.max_balance) {
        throw std::runtime_error("Transfer would exceed balance limits.");
    }
    from_acc.balance -= amount;
    to_acc.balance += amount;
}

void Bank::modifyAllBalances(int amount) {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& acc : accounts) {
        if (!acc.frozen && (acc.balance + amount >= acc.min_balance) && (acc.balance + amount <= acc.max_balance)) {
            acc.balance += amount;
        }
    }
}

void Bank::setAccountLimits(int account_id, int min_balance, int max_balance) {
    std::lock_guard<std::mutex> lock(mutex);
    if (account_id < 0 || account_id >= accounts.size()) {
        throw std::out_of_range("Invalid account number.");
    }
    Account& acc = accounts[account_id];
    if (min_balance > max_balance) {
        throw std::invalid_argument("Minimum balance cannot exceed maximum balance.");
    }
    acc.min_balance = min_balance;
    acc.max_balance = max_balance;
}
