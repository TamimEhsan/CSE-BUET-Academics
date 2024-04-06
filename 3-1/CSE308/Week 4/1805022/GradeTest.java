import org.junit.*;

import static org.junit.Assert.assertEquals;

public class GradeTest {
    Grader grader;

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        System.out.println(">>>>>>>>>>>>>>>>Testing Started<<<<<<<<<<<<<<<<<<<<");
    }

    @Before
    public void setUp() throws Exception {

        grader = new Grader();
    }

    @Test
    public void testInvalidGrade(){
        // Credit test invalid
        assertEquals("invalid grade",grader.getGrade(100,-1));
        assertEquals("invalid grade",grader.getGrade(100,3.5));
        assertEquals("invalid grade",grader.getGrade(100,Double.NaN));
        assertEquals("invalid grade",grader.getGrade(100,Double.POSITIVE_INFINITY));
        assertEquals("invalid grade",grader.getGrade(100,Double.NEGATIVE_INFINITY));
    }

    @Test
    public void testValid3CreditAGrade(){
        // valid grades 3 credit
        assertEquals("A",grader.getGrade(300,3));
        assertEquals("A",grader.getGrade(299.0001,3));
        assertEquals("A",grader.getGrade(270.5,3));
        assertEquals("A",grader.getGrade(240,3));
        assertEquals("A",grader.getGrade(239.9999,3));
    }

    @Test
    public void testValid3CreditBGrade(){
        assertEquals("B",grader.getGrade(239,3));
        assertEquals("B",grader.getGrade(238.9999,3));
        assertEquals("B",grader.getGrade(220.5,3));
        assertEquals("B",grader.getGrade(210,3));
        assertEquals("B",grader.getGrade(210.0001,3));
    }

    @Test
    public void testValid3CreditCGrade(){
        assertEquals("C",grader.getGrade(209,3));
        assertEquals("C",grader.getGrade(208.9999,3));
        assertEquals("C",grader.getGrade(200.5,3));
        assertEquals("C",grader.getGrade(180,3));
        assertEquals("C",grader.getGrade(180.0001,3));
    }

    @Test
    public void testValid3CreditFGrade(){
        assertEquals("F",grader.getGrade(179,3));
        assertEquals("F",grader.getGrade(178.9999,3));
        assertEquals("F",grader.getGrade(100.5,3));
        assertEquals("F",grader.getGrade(0,3));
        assertEquals("F",grader.getGrade(0.0001,3));
        assertEquals("F",grader.getGrade(Double.MIN_VALUE,3));

    }

    @Test
    public void testValid4CreditAGrade(){
        assertEquals("A",grader.getGrade(400,4));
        assertEquals("A",grader.getGrade(399.0001,4));
        assertEquals("A",grader.getGrade(370.5,4));
        assertEquals("A",grader.getGrade(320,4));
        assertEquals("A",grader.getGrade(320.9999,4));
    }

    @Test
    public void testValid4CreditBGrade(){
        assertEquals("B",grader.getGrade(319,4));
        assertEquals("B",grader.getGrade(318.9999,4));
        assertEquals("B",grader.getGrade(300.5,4));
        assertEquals("B",grader.getGrade(280,4));
        assertEquals("B",grader.getGrade(280.0001,4));
    }

    @Test
    public void testValid4CreditCGrade(){
        assertEquals("C",grader.getGrade(279,4));
        assertEquals("C",grader.getGrade(278.9999,4));
        assertEquals("C",grader.getGrade(250.5,4));
        assertEquals("C",grader.getGrade(240,4));
        assertEquals("C",grader.getGrade(240.0001,4));

    }

    @Test
    public void testValid4CreditFGrade(){
        assertEquals("F",grader.getGrade(239,4));
        assertEquals("F",grader.getGrade(238.9999,4));
        assertEquals("F",grader.getGrade(100.5,4));
        assertEquals("F",grader.getGrade(0,4));
        assertEquals("F",grader.getGrade(0.0001,4));
        assertEquals("F",grader.getGrade(Double.MIN_VALUE,4));
    }

    @Test
    public void test3CreditUpperBoundExceed(){
        assertEquals("invalid range: upper bound exceed",grader.getGrade(300.0001,3));
        assertEquals("invalid range: upper bound exceed",grader.getGrade(500,3));
        assertEquals("invalid range: upper bound exceed",grader.getGrade(Double.MAX_VALUE,3));
        assertEquals("invalid range: upper bound exceed",grader.getGrade(Double.POSITIVE_INFINITY,3));
    }

    @Test
    public void test4CreditUpperBoundExceed(){
        assertEquals("invalid range: upper bound exceed",grader.getGrade(400.0001,4));
        assertEquals("invalid range: upper bound exceed",grader.getGrade(500,4));
        assertEquals("invalid range: upper bound exceed",grader.getGrade(Double.MAX_VALUE,4));
        assertEquals("invalid range: upper bound exceed",grader.getGrade(Double.POSITIVE_INFINITY,4));
    }

    @Test
    public void test3CreditLowerBoundExceed(){
        assertEquals("invalid range: lower bound exceed",grader.getGrade(-0.00001,3));
        assertEquals("invalid range: lower bound exceed",grader.getGrade(-500,3));
        assertEquals("invalid range: lower bound exceed",grader.getGrade(Double.NEGATIVE_INFINITY,3));
    }

    @Test
    public void test4CreditLowerBoundExceed(){
        assertEquals("invalid range: lower bound exceed",grader.getGrade(-0.00001,4));
        assertEquals("invalid range: lower bound exceed",grader.getGrade(-500,4));
        assertEquals("invalid range: lower bound exceed",grader.getGrade(Double.NEGATIVE_INFINITY,4));
    }

    @Test
    public void testInvalidMarks(){
        assertEquals("invalid not a number",grader.getGrade(Double.NaN,3));
        assertEquals("invalid not a number",grader.getGrade(Double.NaN,4));
    }

    @After
    public void tearDown() throws Exception {
        grader = null;

    }
    @AfterClass
    public static void setUpAfterClass() throws Exception {
        System.out.println(">>>>>>>>>>>>>>>> Testing Ended <<<<<<<<<<<<<<<<<<<<");
    }

}
