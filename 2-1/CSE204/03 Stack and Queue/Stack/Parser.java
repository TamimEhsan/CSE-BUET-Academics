package com.tamimehsan;

public class Parser {
    private String equation;
    private Stack<Float> numberStack;
    private Stack<Character> operatorStack;
    private boolean isValid = false;

    public Parser(String equation) {
        equation = equation.replaceAll("\\s", "");
        this.equation = equation;
        numberStack = new Stack<>();
        operatorStack = new Stack<>();
    }

    /**
     * Checks if the given equation is Invalid or Probably valid.
     *
     * @param
     * @return false if Invalid, true if probably valid
     */
    private boolean mayBeValid() {
        return isValid = checkRBS() && checkSyntax();
    }

    /**
     * Checks if the given equation has a regular bracket sequence
     *
     * @return
     */
    private boolean checkRBS() {
        int brackets = 0;
        for (int i = 0; i < equation.length(); i++) {
            char c = equation.charAt(i);
            if (c == '(') {
                brackets++;
            } else if (c == ')') {
                if (brackets == 0) return false;
                brackets--;
            }
        }
        return brackets == 0;
    }

    /**
     * Checks if the given equation has a correct syntax
     *
     * @return true if yes
     */
    private boolean checkSyntax() {
        if (equation.length() == 0) return false;
        if (isOperator(equation.charAt(0))) return false;
        if (!isOperator(equation.charAt(0)) && !isParenthesis(equation.charAt(0)) && !isDigit(equation.charAt(0)))
            return false; // case: #&%
        for (int i = 1; i < equation.length(); i++) {
            char c = equation.charAt(i);
            char b = equation.charAt(i - 1);
            if (!isOperator(c) && !isParenthesis(c) && !isDigit(c)) return false; // case: #&%
            if (isOperator(b) && c == ')') return false;                            // case: +)
            if (isDigit(b) && c == '(') return false;                             // case 8(
            if (b == ')' && isDigit(c)) return false;                             // case )5
            if (b == '(' && isOperator(c) && c != '-') return false;                 // case: (*
            if (isOperator(b) && isOperator(c)) return false;                      // case: *-
            if (isParenthesis(b) && isParenthesis(c) && b != c) return false;       // case: () )(
        }
        if (isOperator(equation.charAt(equation.length() - 1))) return false;         // case: +100-1  or 100+5/

        return true;
    }

    /**
     * Parses the given equation after checking the validity of the expression
     *
     * @return the computed float value of the equation
     * @throws ArithmeticException if the expression is not valid
     */
    public float parse() throws ArithmeticException {
        if (!mayBeValid()) throw new ArithmeticException();
        equation = "(" + equation + ")";
        int sz = equation.length();
        float number = 0;
        for (int i = 0; i < sz; i++) {
            char ch = equation.charAt(i);
            if (ch == '(') {
                operatorStack.push(ch);
            } else if (isDigit(ch)) {
                // Parses the number in float here
                number = 0;
                boolean decimal = false;
                float mult = 1;
                while (i < sz && isDigit(equation.charAt(i))) {
                    ch = equation.charAt(i);
                    if (ch == '.' && decimal) {
                        throw new ArithmeticException();
                    } else if (ch == '.') {
                        decimal = true;
                    } else if (decimal) {
                        int digit = ch - '0';
                        mult = mult / 10;
                        number += digit * mult;
                    } else {
                        int digit = ch - '0';
                        number = number * 10 + digit;
                    }
                    i++;
                }
                i--;
                numberStack.push(number);
            } else if (isOperator(ch)) {
                // checks for unary operator here
                if (ch == '-' && !operatorStack.empty() && equation.charAt(i - 1) == '(') {
                    numberStack.push((float) 0);
                    operatorStack.push('u');
                } else {
                    // checks for unary invalidity
                    if (!operatorStack.empty() && operatorStack.top() == 'u') {
                        throw new ArithmeticException();
                    }
                    // Handles preceedence of two operator
                    while (!operatorStack.empty() && operatorStack.top() != '(' && preceeds(operatorStack.top(), ch)) {
                        float a = 0, b = 0;
                        if (!numberStack.empty()) {
                            a = numberStack.top();
                            numberStack.pop();
                        }
                        if (!numberStack.empty()) {
                            b = numberStack.top();
                            numberStack.pop();
                        }
                        char c = operatorStack.top();
                        operatorStack.pop();
                        float value = evaluate(b, a, c);
                        numberStack.push(value);
                    }
                    operatorStack.push(ch);
                }
            } else {
                // Reaches end of a block. And calculates the value of the block
                // pushes the value to be used for next expression
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    float a = 0, b = 0;
                    if (!numberStack.empty()) {
                        a = numberStack.top();
                        numberStack.pop();
                    }

                    if (!numberStack.empty()) {
                        b = numberStack.top();
                        numberStack.pop();
                    }
                    char c = operatorStack.top();
                    operatorStack.pop();
                    float value = evaluate(b, a, c);
                    numberStack.push(value);
                }
                operatorStack.pop();
            }
        }
        // here we didn' check if the stack is empty or not because
        // we added a parenthesis around the expression
        if (!numberStack.empty()) number = numberStack.top();
        return number;

    }

    /**
     * Checks if character c is a digit from 0 to 9 or a decimal point
     *
     * @param c
     * @return true if it is a decimal value
     */
    private boolean isDigit(char c) {
        return (c > 47 && c < 58) || c == '.';
    }

    /**
     * Checks if a given char c is a parenthesis of type ( or )
     *
     * @param c
     * @return true if c is a parenthesis
     */
    private boolean isParenthesis(char c) {
        return c == '(' || c == ')';
    }

    /**
     * Checks if a character is a operator of type + - * /
     *
     * @param c
     * @return true if c is a operator
     */
    private boolean isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    /**
     * Evaluates the result of a binary expression a # b
     *
     * @param a First number of the expression
     * @param b Second number of the expression
     * @param c The operator
     * @return a float result of the expression
     * @throws ArithmeticException if divides by zero
     */
    private float evaluate(float a, float b, char c) throws ArithmeticException {
        switch (c) {
            case '+':
                return a + b;
            case '-':
            case 'u':
                return a - b;
            case '*':
                return a * b;
            case '/':
                if (b == 0) throw new ArithmeticException();
                return a / b;
            default:
                return 0;
        }
    }

    /**
     * Checks precedence between two operator
     *
     * @param a The current operator
     * @param b The previous operator
     * @return true if the previous operator preceeds current operator
     * false otherwise
     */
    private boolean preceeds(char a, char b) {
        return (a != '+' && a != '-') || (b != '*' && b != '/');
    }
}
