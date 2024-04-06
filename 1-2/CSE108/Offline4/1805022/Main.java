import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Employee e [] = new Employee[6];
        Random r = new Random();
        for (int i = 0; i < 6; i++)
        {
            // creating new employee
            e[i] = new Employee(i+1, "E" + (i+1), 10000 * r.nextDouble());
        }
        Department d [] = new Department[2];
        for (int i = 0; i < 2; i++) {
            // creating new department
            d[i] = new Department(i+1, "D" + (i+1));
        }
        d[0].addEmployee(e[0]); // add the employee to this department
        d[0].addEmployee(e[1]); // add the employee to this department
        d[1].addEmployee(e[2]); // add the employee to this department
        d[1].addEmployee(e[3]); // add the employee to this department
        d[1].addEmployee(e[4]); // add the employee to this department
        d[1].addEmployee(e[5]); // add the employee to this department
        System.out.println(d[0].getDepartmentSalary()); // prints the total salary of this department
        System.out.println(d[1].getDepartmentSalary()); // prints the total salary of this department
        System.out.println(d[0].getMaxSalaryEmployee().getName()); // prints the name of the employee with highest salary in this department
        System.out.println(d[1].getMaxSalaryEmployee().getName()); // prints the name of the employee with highest salary in this department
        System.out.println(Department.getTotalSalary()); // prints the total salary of all departments
    }
}