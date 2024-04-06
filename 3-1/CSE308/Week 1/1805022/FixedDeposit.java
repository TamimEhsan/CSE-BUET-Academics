package com.tamimehsan;

public class FixedDeposit extends Account{

    private static final double MIN_FIRST_DEPOSIT = 100000;
    private static final double MIN_DEPOSIT = 50000;
    private static final double MAX_LOAN = 100000;
    private static double DEPOSIT_INTEREST_RATE = 0.05;

    @Override
    public boolean createAccount(String name, double initial_amount,int creation_time) {
        if( initial_amount<MIN_FIRST_DEPOSIT ) {
            System.out.println("Initial amount less than minimum requirement, which is "+FixedDeposit.MIN_FIRST_DEPOSIT+"$");
            return false;
        }
        setUser_name(name);
        setDeposit_amount(initial_amount);
        System.out.println("Fixed Deposit account for "+name+" Created; initial balance "+initial_amount+"$");
        return true;
    }

    @Override
    public boolean deposit(double amount) {
        if( amount<MIN_DEPOSIT ){
            System.out.println("Deposit amount less than minimum requirement, which is "+FixedDeposit.MIN_DEPOSIT+"$");
            return false;
        }
        setDeposit_amount(getDeposit_amount()+amount);
        System.out.println(amount+"$ deposited; current balance "+getDeposit_amount()+"$");
        return true;
    }

    @Override
    public boolean withdraw(double amount) {
        if(  getAge()<1 || getDeposit_amount()<amount ){
            System.out.println("Invalid transaction; current balance "+getDeposit_amount()+"$");
            return false;
        }

        setDeposit_amount(getDeposit_amount()-amount);
        System.out.println(amount+"$ withdrawn; current balance "+getDeposit_amount()+"$");
        return true;
    }

    @Override
    public boolean requestLoan(double amount) {
        if( getLoan_amount()+getRequested_loan()+amount>MAX_LOAN ) {
            System.out.println("Loan request unsuccessful");
            return false;
        }
        setRequested_loan(getRequested_loan()+amount);
        System.out.println("Loan request successful, sent for approval");
        return true;
    }
    public void increament() {
        increamentAge();
        double loan = getLoan_amount();
        double deposit = getDeposit_amount();
        double deposit_amount = deposit +  FixedDeposit.DEPOSIT_INTEREST_RATE * deposit - loan * getLOAN_INTEREST_RATE() - getSERVICE_CHARGE()  ;
        setDeposit_amount(deposit_amount);
    }
    public static void setDEPOSIT_INTEREST_RATE(double DEPOSIT_INTEREST_RATE) {
        FixedDeposit.DEPOSIT_INTEREST_RATE = DEPOSIT_INTEREST_RATE;
    }
}
