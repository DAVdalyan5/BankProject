

#include "Bank.h"
#include <gtest/gtest.h>

class BankSystemTests : public ::testing::Test {
protected:
    Bank* bank;

    void SetUp() override {
        bank = new Bank(5, 1000);
    }

    void TearDown() override {
        delete bank;
    }
};

TEST_F(BankSystemTests, TransferFunds) {
    bank->modifyAllBalances(500); 
    ASSERT_NO_THROW(bank->transfer(0, 1, 200));
    ASSERT_EQ(bank->getAccountBalance(0), 300);
    ASSERT_EQ(bank->getAccountBalance(1), 700);
}

TEST_F(BankSystemTests, FreezeAccount) {
    bank->setAccountFrozen(0, true);
    ASSERT_THROW(bank->transfer(0, 1, 100), std::runtime_error);
}

TEST_F(BankSystemTests, SetLimits) {
    bank->setAccountLimits(0, -100, 900);
    ASSERT_NO_THROW(bank->modifyAllBalances(-200));
    ASSERT_EQ(bank->getAccountBalance(0), -200);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
