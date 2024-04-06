package com.tamimehsan;

import java.util.ArrayList;

public class Bank {


    private Employee MD, S1, S2, C1, C2, C3, C4, C5;
    private ArrayList<Employee> employeeArrayList;
    private ArrayList<Account> accountArrayList;
    private int internalFund;
    private int clock;

    private Employee activeEmployee;
    private Account activeAccount;

    Bank() {
        Employee MD = new ManagingDirector();
        Employee O1 = new Officer(1);
        Employee O2 = new Officer(2);
        Employee C1 = new Officer(1);
        Employee C2 = new Officer(2);
        Employee C3 = new Officer(3);
        Employee C4 = new Officer(4);
        Employee C5 = new Officer(5);

        employeeArrayList = new ArrayList<Employee>();
        accountArrayList = new ArrayList<Account>();
        employeeArrayList.add(MD);
        employeeArrayList.add(O1);
        employeeArrayList.add(O2);
        employeeArrayList.add(C1);
        employeeArrayList.add(C2);
        employeeArrayList.add(C3);
        employeeArrayList.add(C4);
        employeeArrayList.add(C5);

        clock = 0;
        internalFund = 1000000;
        System.out.println("Bank Created; M D, S1, S2, C1, C2, C3, C4, C5 created");
    }

    private boolean checkPrimaryKeyConstraint(String name) {
        for (Employee employee : employeeArrayList)
            if (employee.getName().equalsIgnoreCase(name)){
                System.out.println("Can't open account under provided name");
                return false;
            }

        for (Account account : accountArrayList)
            if (account.getName().equalsIgnoreCase(name)){
                System.out.println("Can't open account under provided name");
                return false;
            }

        return true;
    }

    public boolean createAccount(String name,String type,double amount){
        activeEmployee = null;
        activeAccount = null;
        if( !checkPrimaryKeyConstraint(name) ){
            return false;
        }
        if( type.equalsIgnoreCase("savings") ){
            Account account = new Savings();
            if( account.createAccount(name,amount,clock) ){
                accountArrayList.add(account);
                activeAccount = account;
                return true;
            }
        }else if( type.equalsIgnoreCase("student") ){
            Account account = new Student();
            if( account.createAccount(name,amount,clock) ){
                accountArrayList.add(account);
                activeAccount = account;
                return true;
            }
        }else if( type.equalsIgnoreCase("loan") ){
            Account account = new Loan();
            if( account.createAccount(name,amount,clock) ){
                accountArrayList.add(account);
                activeAccount = account;
                return true;
            }
        }else if( type.equalsIgnoreCase("fixed_deposit") ){
            Account account = new FixedDeposit();
            if( account.createAccount(name,amount,clock) ){
                accountArrayList.add(account);
                activeAccount = account;
                return true;
            }
        }
        return false;
    }

    public void closeAccount() {
        if (activeEmployee != null) {
            System.out.println("Operations for " + activeEmployee.getName() + " closed");
        } else if (activeAccount != null) {
            System.out.println("Transaction Closed for " + activeAccount.getName());
        } else {
            System.out.println("No Active Operations!");
        }
        activeEmployee = null;
        activeAccount = null;
    }

    public void openAccount(String name) {
        if (activeAccount != null || activeEmployee != null) {
            System.out.println("Already account open, Close current to open new account");
            return;
        }
        for (Employee employee : employeeArrayList)
            if (employee.getName().equalsIgnoreCase(name)) {
                activeEmployee = employee;
                System.out.print(activeEmployee.getName()+" active");
                boolean hasLoanRequest = false;
                if (activeEmployee.hasApproveLoanAcess()) {
                    for (Account account : accountArrayList) {
                        if (account.hasRequestedLoan())
                            hasLoanRequest = true;

                    }
                    if(hasLoanRequest) System.out.println(", there are loan approvals pending");
                    else System.out.println(", there are no loan approvals pending");
                }

                return;
            }

        for (Account account : accountArrayList)
            if (account.getName().equalsIgnoreCase(name)) {
                activeAccount = account;
                System.out.println("Welcome back, "+activeAccount.getName());
                return;
            }
    }

    public void query(){
        if (activeAccount != null) {
            activeAccount.query();
        }
    }

    public void deposit(double amount) {
        if (activeAccount != null) {
            activeAccount.deposit(amount);
        }
    }

    public void withdraw(double amount) {
        if (activeAccount != null) {
            activeAccount.withdraw(amount);
        }
    }

    public void requestLoan(double amount) {
        if (activeAccount != null) {
            activeAccount.requestLoan(amount);
        }
    }

    public void approveLoans() {
        if (activeEmployee != null && activeEmployee.hasApproveLoanAcess()) {
            for (Account account : accountArrayList) {
                if (account.hasRequestedLoan())
                    account.approveLoan();
                System.out.println("Loan for "+account.getName()+" approved");
            }
        }else{
            System.out.println("You don’t have permission for this operation");
        }
    }

    private Account getAccountByName(String name) {
        for (Account account : accountArrayList)
            if (account.getName().equalsIgnoreCase(name))
                return account;
        return null;
    }

    public void lookup(String name) {
        Account account = getAccountByName(name);
        if (activeEmployee != null && activeEmployee.hasLookUpAccess() && account != null ) {
            account.lookup();
        }else{
            System.out.println("You don’t have permission for this operation");
        }
    }
    public void seeInternalFund(){
        if (activeEmployee != null && activeEmployee.hasSeeInternalFundAccess() ) {
            System.out.println("Internal Fund is "+this.internalFund+"$");
        }else{
            System.out.println("You don’t have permission for this operation");
        }
    }
    public void changeDepositInterst(String type,double amount){

        if( activeEmployee==null || !activeEmployee.hasChangeInterestRateAccess() ){
            System.out.println("You don’t have permission for this operation");
            return;
        }

        if( type.equalsIgnoreCase("student") ){
            Student.setDEPOSIT_INTEREST_RATE(amount);
        }else if(type.equalsIgnoreCase("savings")){
            Savings.setDEPOSIT_INTEREST_RATE(amount);
        }else if(type.equalsIgnoreCase("fixed_deposit")){
            FixedDeposit.setDEPOSIT_INTEREST_RATE(amount);
        }
    }
    public void incrementTime(){
        clock = clock+1;
        for(Account account:accountArrayList){
            account.increament();
        }
        System.out.println(clock+" year passed");
    }

    public int getClock() {
        return clock;
    }
}
