package com.tamimehsan;

abstract public class Employee{

    private String user_name;

    private boolean lookUpAccess;
    private boolean approveLoanAcess;
    private boolean changeInterestRateAccess;
    private boolean seeInternalFundAccess;

    public Employee(String name,boolean hasLookUpAccess, boolean hasApproveLoadAcess, boolean hasChangeInterestRateAccess, boolean hasSeeInternalFundAccess) {
        this.user_name = name;
        this.lookUpAccess = hasLookUpAccess;
        this.approveLoanAcess = hasApproveLoadAcess;
        this.changeInterestRateAccess = hasChangeInterestRateAccess;
        this.seeInternalFundAccess = hasSeeInternalFundAccess;
    }
    public String getName(){
        return this.user_name;
    }

    public boolean hasLookUpAccess() {
        return lookUpAccess;
    }

    public boolean hasApproveLoanAcess() {
        return approveLoanAcess;
    }

    public boolean hasChangeInterestRateAccess() {
        return changeInterestRateAccess;
    }

    public boolean hasSeeInternalFundAccess() {
        return seeInternalFundAccess;
    }
}
