public class Department {

    private int id;
    private String name;
    private Employee [] employees;
    private int employeeCount;
    private static Department[] departments;
    private static int departmentCount;
    // add your code here
    // there can be at most 20 departments  

    // you are not allowed to write any other constructor
    public Department(int id, String name) {
        this.id = id;
        this.name = name;
        this.employees = new Employee[10];
        if( departments == null ){
            departments = new Department[20];
        }
        departments[departmentCount++] = this;
        // add your code here
    }

    // add your code here
    public void addEmployee(Employee employee){
        employees[employeeCount++] = employee;
    }
    public int getDepartmentSalary(){
        int totalSalary = 0;
        for(int i = 0;i <employeeCount;i++){
            totalSalary+=employees[i].getSalary();
        }
        return totalSalary;
    }
    public Employee getMaxSalaryEmployee(){
        int idx = 0;
        if( employeeCount == 0 ){
            return null;
        }
        for(int i = 1;i < employeeCount;i++){
            if( employees[idx].getSalary() < employees[i].getSalary() ){
                idx = i;
            }
        }
        return employees[idx];
    }
    public static int getTotalSalary(){
        int totalSalary = 0;
        for( int i = 0;i<departmentCount;i++){
            totalSalary+=departments[i].getDepartmentSalary();
        }
        return totalSalary;
    }
}