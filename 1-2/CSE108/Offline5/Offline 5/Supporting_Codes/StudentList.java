import java.util.ArrayList;
import java.util.List;

class Student {
    private String name;
    private int id;

    public Student(String name, int id) {
        this.name = name;
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public int getId() {
        return id;
    }
}

public class StudentList {

    public static void main(String[] args) {
        List<Student> studentList = new ArrayList();

        Student s1 = new Student("A", 1);
        Student s2 = new Student("B" , 2);
        Student s3 = new Student("C", 3);

        studentList.add(s1);
        studentList.add(s2);
        studentList.add(s3);
        studentList.add(new Student("D", 4));

        for (Student s : studentList) {
            System.out.println(s.getId() + ", " + s.getName());
        }

        String searchName = "D";
        int searchIndex = -1;
        for (int i = 0; i < studentList.size(); i++) {
            Student t = studentList.get(i);
            if (t.getName().equals(searchName)) {
                searchIndex = i;
            }
        }
        if (searchIndex != -1) {
            studentList.remove(searchIndex);
        }

        for (Student s : studentList) {
            System.out.println(s.getId() + ", " + s.getName());
        }
    }
}
