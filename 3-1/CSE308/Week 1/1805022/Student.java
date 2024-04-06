package com.tamimehsan;

public class Student extends Account{

    private static final double MAX_WITHDRAW = 10000;
    private static final double MAX_LOAN = 1000;
    private static double DEPOSIT_INTEREST_RATE = 0.05;
    @Override
    public boolean createAccount(String name, double initial_amount,int creation_time) {
        setUser_name(name);
        setDeposit_amount(initial_amount);

        System.out.println("Student account for "+name+" Created; initial balance "+initial_amount+"$");
        return true;
    }

    @Override
    public boolean deposit(double amount) {
        setDeposit_amount(getDeposit_amount()+amount);
        System.out.println(amount+"$ deposited; current balance "+getDeposit_amount()+"$");
        return true;
    }

    @Override
    public boolean withdraw(double amount) {
        if( amount>MAX_WITHDRAW || amount>getDeposit_amount() ) {
            System.out.println("Invalid transaction; current balance "+getDeposit_amount()+"$");
            return false;
        }

        setDeposit_amount(getDeposit_amount()-amount);
        System.out.println(amount+"$ withdrawn; current balance "+getDeposit_amount()+"$");
        return true;
    }

    @Override
    public boolean requestLoan(double amount) {
        if( getLoan_amount()+amount>MAX_LOAN ){
            System.out.println("Loan request unsuccessful");
            return false;
        }
        setRequested_loan(getRequested_loan()+amount);
        System.out.println("Loan request successful, sent for approval");
        return true;
    }
    public static void setDEPOSIT_INTEREST_RATE(double DEPOSIT_INTEREST_RATE) {
        Student.DEPOSIT_INTEREST_RATE = DEPOSIT_INTEREST_RATE;
    }
    public void increament() {
        increamentAge();
        double loan = getLoan_amount();
        double deposit = getDeposit_amount();
        double deposit_amount = deposit +  Student.DEPOSIT_INTEREST_RATE * deposit - loan * getLOAN_INTEREST_RATE() - getSERVICE_CHARGE()  ;
        setDeposit_amount(deposit_amount);
    }
}