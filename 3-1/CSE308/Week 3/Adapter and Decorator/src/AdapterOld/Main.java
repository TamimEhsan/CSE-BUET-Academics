package AdapterOld;

public class Main {

    public static void main(String[] args) {
	// write your code here
        HybridCalculator hybridCalculator = new HybridCalculator();
        String fileSpace = "src/Adapter/inputSpaceSeperated.txt";
        String fileTilda = "src/Adapter/inputTildaSeperated.txt";
        int sum1 = hybridCalculator.calculateSum("space",fileSpace);
        System.out.println(sum1);
        int sum2 = hybridCalculator.calculateSum("tilda",fileTilda);
        System.out.println(sum2);
    }
}
