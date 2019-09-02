package lab3.guicalc;

import java.util.HashSet;
import java.util.Set;

import lab3.operator.BinaryOperator;
import lab3.operator.BinaryOperatorImp;
import lab3.operator.UnaryOperator;
import lab3.operator.UnaryOperatorImp;

/**
 * Main program that runs the GUI Calculator
 */
public class Main {

    /**
     * Add BinaryOperators and UnaryOperators implements to the calculator.
     * 
     * @param args as input
     */
    public static void main(String[] args) {
        // Generating OperatorSet
        Set<BinaryOperator> binaryOperatorSet=new HashSet<>();
        binaryOperatorSet.add(BinaryOperatorImp.ADDITION);
        binaryOperatorSet.add(BinaryOperatorImp.SUBTRACTION);
        binaryOperatorSet.add(BinaryOperatorImp.MULTIPLICATION);
        binaryOperatorSet.add(BinaryOperatorImp.DIVISION);
        binaryOperatorSet.add(BinaryOperatorImp.EXPONENTIATION);
        Set<UnaryOperator> unaryOperatorSet=new HashSet<>();
        unaryOperatorSet.add(UnaryOperatorImp.ABS);
        unaryOperatorSet.add(UnaryOperatorImp.NEGATION);
//        throw new Exception("Need to be implemented！");
        new GuiCalculator(unaryOperatorSet,binaryOperatorSet);
        // Run the calculator!
//        throw new Exception("Need to be implemented！");

    }
}
