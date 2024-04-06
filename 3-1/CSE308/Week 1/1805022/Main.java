package com.tamimehsan;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        // write your code here
        Scanner scanner = new Scanner(System.in);
        Bank bank = new Bank();
        int option = 1;
        while (option != 0) {
            String command = scanner.nextLine();
            String[] commands = command.split(" ", 0);

            switch (commands[0]) {
                case "create":
                    bank.createAccount(commands[1], commands[2], Integer.parseInt(commands[3]));
                    break;
                case "deposit":
                    bank.deposit(Double.parseDouble(commands[1]));
                    break;
                case "withdraw":
                    bank.withdraw(Double.parseDouble(commands[1]));
                    break;
                case "query":
                    bank.query();
                    break;
                case "request":
                    bank.requestLoan(Double.parseDouble(commands[1]));
                    break;
                case "close":
                    bank.closeAccount();
                    break;
                case "open":
                    bank.openAccount(commands[1]);
                    break;
                case "approve":
                    bank.approveLoans();
                    break;
                case "change":
                    bank.changeDepositInterst(commands[1],Double.parseDouble(commands[2]));
                    break;
                case "lookup":
                    bank.lookup(commands[1]);
                    break;
                case "see":
                    bank.seeInternalFund();
                    break;
                case "inc":
                    bank.incrementTime();
                    break;
                case "end":
                default:
                    option = 0;
                    break;
            }

        }
    }
}


/*
create alice student 1000
deposit 20000
withdraw 12000
query
request 500
close
open s1
approve loan
change student 7.5
lookup alice
see
close
open alice
query
close
inc
open alice
query
close
end

 */