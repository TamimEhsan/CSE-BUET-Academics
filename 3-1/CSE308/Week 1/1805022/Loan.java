package com.tamimehsan;

public class Loan extends Account {

    private boolean takenSecondLoan = false;

    @Override
    public boolean createAccount(String name, double initial_amount,int creation_time) {
        setUser_name(name);
        setRequested_loan(initial_amount);

        System.out.println("Loan account for "+name+" Created; initial loan "+initial_amount+"$");
        return true;
    }

    @Override
    public boolean deposit(double amount) {
        if( resolveLoan(amount) ) {
            System.out.println("Repayed loan of "+amount+"$");
            return true;
        }
        return false;
    }

    @Override
    public boolean withdraw(double amount) {
        return false;
    }

    @Override
    public boolean requestLoan(double amount) {
        if( takenSecondLoan ) {
            System.out.println("Loan request unsuccessful");
            return false;
        }
        double totalLoan = getRequested_loan()+getLoan_amount();
        double max_allowable = totalLoan*5/100;
        if( amount>max_allowable ) {
            System.out.println("Loan request unsuccessful");
            return false;
        }
        setRequested_loan( getRequested_loan()+amount );
        if( amount == max_allowable )
            takenSecondLoan = true;
        System.out.println("Loan request successful, sent for approval");
        return true;

    }

    @Override
    public void increament() {
        increamentAge();
        double loan = getLoan_amount();
        double new_loan = loan + loan * getLOAN_INTEREST_RATE() - getSERVICE_CHARGE()  ;
        setLoan_amount(new_loan);
    }
}
