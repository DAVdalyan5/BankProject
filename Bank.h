#ifndef BANK_H
#define BANK_H

#include <vector>
#include <mutex>
#include <stdexcept>

// Структура, представляющая счет в банке
struct Account {
    int balance;        // Текущий баланс
    int min_balance;    // Минимальный возможный баланс
    int max_balance;    // Максимальный возможный баланс
    bool frozen;        // Статус заморозки счета

    Account(int min_bal = 0, int max_bal = 1000)
        : balance(0), min_balance(min_bal), max_balance(max_bal), frozen(false) {}
};

// Класс банка
class Bank {
private:
    std::vector<Account> accounts;
    mutable std::mutex mutex;  // Мьютекс для синхронизации доступа к счетам

public:
    Bank(int n, int max_balance);
    void printAccountInfo(int account_id) const;
    void setAccountFrozen(int account_id, bool freeze);
    void transfer(int from_id, int to_id, int amount);
    void modifyAllBalances(int amount);
    void setAccountLimits(int account_id, int min_balance, int max_balance);
};

#endif // BANK_H
