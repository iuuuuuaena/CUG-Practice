package lab3.operator;
import static org.junit.Assert.*;
import org.junit.*;

public class BinaryOperatorTest {
    @Test
    public void ADDITIONTest(){
        BinaryOperator operator=BinaryOperatorImp.ADDITION;
        assertEquals(3,operator.apply(1,2),0.001);
        assertEquals("+",operator.toString());
    }
    @Test
    public void SUBTRACTIONTest(){
        BinaryOperator operator=BinaryOperatorImp.SUBTRACTION;
        assertEquals(-1,operator.apply(1,2),0.001);
        assertEquals("-",operator.toString());
    }
    @Test
    public void MULTIPLICATION(){
        BinaryOperator operator=BinaryOperatorImp.MULTIPLICATION;
        assertEquals(2,operator.apply(1,2),0.001);
        assertEquals("*",operator.toString());
    }
    @Test
    public void DIVISIONTest(){
        BinaryOperator operator=BinaryOperatorImp.DIVISION;
        assertEquals(0.5,operator.apply(1,2),0.001);
        assertEquals("/",operator.toString());
    }
    @Test
    public void EXPONENTIATIONTest(){
        BinaryOperator operator=BinaryOperatorImp.EXPONENTIATION;
        assertEquals(1,operator.apply(1,2),0.001);
        assertEquals("^",operator.toString());
    }
}
