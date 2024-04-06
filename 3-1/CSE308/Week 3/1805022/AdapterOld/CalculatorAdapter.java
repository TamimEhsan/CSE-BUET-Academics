package AdapterOld;

public class CalculatorAdapter implements Calculator{
    AdvancedCalculator advancedCalculator;

    @Override
    public int calculateSum(String seperatorType,String filenName) {
        advancedCalculator = new CalculatorTildaSeperated();
        return advancedCalculator.calculateSum(filenName);
    }
}
