#include "Bank.h"
#include <gtest/gtest.h>

TEST(BankTest, TestTransfer) {
    Bank bank(2, 1000);
    bank.modifyAllBalances(500); 
    bank.transfer(0, 1, 300);
    ASSERT_EQ(bank.getAccountBalance(0), 200);
    ASSERT_EQ(bank.getAccountBalance(1), 800);
}

TEST(BankTest, TestFreezeAccount) {
    Bank bank(1, 500);
    bank.setAccountFrozen(0, true);
    ASSERT_THROW(bank.modifyAllBalances(100), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
