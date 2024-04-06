public class Department {

    private int id;
    private String name;
    private Employee [] employees;
    private int employeeCount;
    // add your code here
    // there can be at most 20 departments  

    // you are not allowed to write any other constructor
    public Department(int id, String name) {
        this.id = id;
        this.name = name;
        this.employees = new Employee[10];
        // add your code here
    }

    // add your code here
}