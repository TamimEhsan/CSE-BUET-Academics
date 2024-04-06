package com.tamimehsan;

abstract public class Account {

    private int age = 0;
    private final double LOAN_INTEREST_RATE = 0.1;
    private double SERVICE_CHARGE = 500.0;
    private String user_name;
    private double deposit_amount;
    private double loan_amount;
    private double requested_loan;

    Account() { }

    public void setUser_name(String user_name) {
        this.user_name = user_name;
    }

    public void setDeposit_amount(double deposit_amount) { this.deposit_amount = deposit_amount; }

    public void setRequested_loan(double requested_loan) { this.requested_loan = requested_loan; }

    public void setLoan_amount(double loan_amount) { this.loan_amount = loan_amount; }

    public int getAge(){ return this.age; }

    public double getDeposit_amount() {
        return deposit_amount;
    }

    public double getRequested_loan() {
        return requested_loan;
    }

    public double getLoan_amount() { return loan_amount; }

    public String getName() {
        return user_name;
    }

    public double getLOAN_INTEREST_RATE() { return LOAN_INTEREST_RATE; }

    public double getSERVICE_CHARGE() { return SERVICE_CHARGE; }

    public void increamentAge() { this.age += 1; }

    public boolean hasRequestedLoan() { return this.requested_loan > 0; }

    public boolean approveLoan() {
        this.deposit_amount += this.requested_loan;
        this.loan_amount += this.requested_loan;
        this.requested_loan = 0;
        return true;
    }

    public boolean resolveLoan(double amount) {
        if (loan_amount > amount) {
            loan_amount -= amount;
            return true;
        } else if (loan_amount <= amount) {
            amount -= loan_amount;
            // we will use this extra money for some coffee
        }
        return true;
    }


    public void query() {
        System.out.println("Current balance, " + this.deposit_amount + "$, loan " + this.loan_amount + "$");
    }

    public void lookup() {
        System.out.println(this.getName() + "’s current balance " + this.deposit_amount + "$");
    }


    abstract public boolean createAccount(String name, double initial_amount,int creation_time);

    abstract public boolean deposit(double amount);

    abstract public boolean withdraw(double amount);

    abstract public boolean requestLoan(double amount);

    abstract public void increament();

}