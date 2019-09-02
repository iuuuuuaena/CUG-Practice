package lab3.operator;
import static org.junit.Assert.*;
import org.junit.*;

public class UnaryOperatorImpTest {
    @Test
    public void ABSTest(){
        UnaryOperator operator=UnaryOperatorImp.ABS;
        assertEquals("abs",operator.toString());
        assertEquals(1,operator.apply(-1),0.001);
        assertEquals(1,operator.apply(1),0.001);
    }
    @Test
    public void NEGATIONTest(){
        UnaryOperator operator=UnaryOperatorImp.NEGATION;
        assertEquals("neg",operator.toString());
        assertEquals(1,operator.apply(-1),0.001);
        assertEquals(-1,operator.apply(1),0.001);
    }
}
