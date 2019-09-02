package lab3.termcalc;

import java.util.Scanner;

import lab3.expression.Expression;

/**
 * Main entry point for the command line calculator
 */
public class Main {
    /**
     * @param args program arguments
     */
    public static void main(String[] args) {
        //Create Instances(ExpressionMaker,TerminalCalculator)
        ExpressionMakerImp expressionMakerImp=new ExpressionMakerImp();
        TerminalCalculator terminalCalculator=new TerminalCalculator(expressionMakerImp);
//        throw new Exception("Need to be implemented！");
        //Use TerminalCalculator
        Scanner sc=new Scanner(System.in);
        try {
            while (true){
                System.out.println("输入一个表达式");
                String s=sc.nextLine();
                Expression expression=terminalCalculator.run(s);
                System.out.println(expression);
                System.out.format("=%s%n",expression.eval());
            }
        }catch (Exception e){
            e.printStackTrace();
        }
//        throw new Exception("Need to be implemented！");
    }
}
