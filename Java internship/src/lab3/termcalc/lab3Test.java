package lab3.termcalc;
import lab3.expression.*;
import lab3.termcalc.*;
import org.junit.*;
import static org.junit.Assert.*;

public class lab3Test {
    @Test
    public void pro2Test(){
        ExpressionMakerImp expressionMakerImp=new ExpressionMakerImp();
        TerminalCalculator terminalCalculator=new TerminalCalculator(expressionMakerImp);
        String s="1+2*(3-4)/5-2";
        Expression expression=terminalCalculator.run(s);
        assertEquals(-1.4,expression.eval(),0.01);
        s="(3*3+4*4)^0.5";
        expression=terminalCalculator.run(s);
        assertEquals(5.0,expression.eval(),0.01);
    }
}
