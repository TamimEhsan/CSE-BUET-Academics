public class Grader {
    public String getGrade(double _mark,double grade){
        if( Double.isNaN(_mark) ){
            return "invalid not a number";
        }else if( _mark<0 ){
            return "invalid range: lower bound exceed";
        }
        int marks = (int) Math.ceil(_mark);
        if( grade == 3 ){
            return getGrade3Credit(marks);
        }else if( grade == 4 ){
            return getGrade4Credit(marks);
        }else{
            return "invalid grade";
        }

    }
    private String getGrade3Credit(int marks){
        if( marks>=240 && marks<=300 ){
            return "A";
        }else if( marks>=210 && marks<=239 ){
            return "B";
        }else if( marks>=180 && marks<=209 ){
            return "C";
        }else if( marks>=0 && marks<180 ){
            return "F";
        }else if(marks>300){
            return "invalid range: upper bound exceed";
        }else{
            return "invalid range: lower bound exceed";
        }
    }
    private String getGrade4Credit(int marks){
        if( marks>=320 && marks<=400 ){
            return "A";
        }else if( marks>=280 && marks<=319 ){
            return "B";
        }else if( marks>=240 && marks<=279 ){
            return "C";
        }else if( marks>=0 && marks<240 ){
            return "F";
        }else if(marks>400){
            return "invalid range: upper bound exceed";
        }else{
            return "invalid range: lower bound exceed";
        }
    }
}
