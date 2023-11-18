#ifndef DIVIDEANDRULE_HPP
#define DIVIDEANDRULE_HPP

#include <iostream>
#include <vector>
#include <map>



struct Bank
{
    //the bank must recieve 5% of each inflow on client accounts
    //the accounts ids should be unique 
    //attributes should be private
    //the bank must be able to create delete and modify accounts of custumers
    //it must be impossible to add money ti a client acount without going through the bank
    //the bank must be able to give loans to clients , within the limits of their funds
    //if it make sense the creation of a getter and a setter is mandatory , getters by copy will not be accepted
    //if it make sense the creation of a const getter is mandatory , const getters by copy will not be accepted



    public:

        struct Account
        {
            private:
                int           value;
                uint32_t      id;
                friend struct Bank;

                Account() : value(0) ,id(0) {}

                Account(int client_balance, int generated_id) : value(client_balance) ,id(generated_id) { }
            
            public:                
                const int& getBalance() const { return value; }
                const uint32_t& getId() const { return id; }

                friend std::ostream& operator << (std::ostream& p_os, const Account& p_account)
                {
                    p_os << "[" << p_account.id << "] - [" << p_account.value << "]";
                    return (p_os);
                }
        };

        Bank() :liquidity(0) , ids_counter(0) { }

        Account* createAccount() {
            Account *newAccount = new Account(0, ids_counter++);
            clientAccounts.insert(std::make_pair(newAccount->getId(), newAccount));
            return newAccount;
        }

        void deleteAccount(uint32_t clientId) {
            std::map<uint32_t, Account *>::iterator it = clientAccounts.find(clientId);
            if (it != clientAccounts.end())
                clientAccounts.erase(it);
            else
                throw std::out_of_range("Failed to delete account: No account with this id");
        }

        void addMoneytoAccount(uint32_t clientId, int money) {
            //take 5% of the money for the bank
            if (money >= 0){
                std::map<uint32_t, Account *>::iterator it = clientAccounts.find(clientId);
                if (it != clientAccounts.end()){
                    liquidity += money * 0.05;
                    it->second->value+=money*0.95;
                }
                else
                    throw std::out_of_range("Failed to add money to account: No account with this id");
            }
            else
                throw std::invalid_argument("Failed to add money to account: Money added argument must be positive");
        } 

        void giveLoan(uint32_t clientId, int loan) {
            //take 5% of the loan for the bank
            //
            std::map<uint32_t, Account *>::iterator it = clientAccounts.find(clientId);
            Account *account = it->second;
            if (it == clientAccounts.end())
                throw std::out_of_range("Failed to give loan: No account with this id");
            if (loan < 0)
                throw std::invalid_argument("Failed to give loan: Loan argument must be positive");
            else if (account->getBalance() < loan)
                throw std::invalid_argument("Failed to give loan: Loan argument must be inferior to account balance");
            else if (liquidity < loan)
                throw std::invalid_argument("Failed to give loan: Loan argument must be inferior to bank liquidity");
            else {
                liquidity -= loan * 0.95;
                account->value+= loan * 0.95;
            }
        }

        void addLiquidty(int money) {
            if (money < 0)
                throw std::invalid_argument("Failed to add liquidity: Money argument must be positive");
            else
                liquidity += money;
        }
        //
        const int& getLiquidity() const { return liquidity; }

        Account* getAccount(uint32_t clientId) {
            std::map<uint32_t, Account *>::iterator it = clientAccounts.find(clientId);
            if (it != clientAccounts.end())
                return it->second;
            else
                throw std::out_of_range("Failed to get account: No account with this id");
        }

        Account* operator[](uint32_t clientId) {
            return getAccount(clientId);
        }

        friend std::ostream& operator << (std::ostream& p_os, const Bank& p_bank)
        {
            p_os << "Bank informations : " << std::endl;
            p_os << "Liquidity : " << p_bank.liquidity << std::endl;
            for (std::map<uint32_t, Account*>::const_iterator it = p_bank.clientAccounts.begin(); it != p_bank.clientAccounts.end(); ++it)
                p_os << *(it->second) << std::endl;
            // p_os << *clientAccount << std::endl;
            return (p_os);
        }
    private:

        int                          liquidity;
        int                          ids_counter;
        std::map<uint32_t,Account *> clientAccounts;

};

#endif