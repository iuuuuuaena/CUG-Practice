package lab3.expression;
import static org.junit.Assert.*;
import org.junit.*;

public class expressionTest {
    private Expression arg1=new NumberExpression(1);
    private Expression arg2=new NumberExpression(-1);
    private Expression arg3=new NumberExpression(2);
    private Variable x=new Variable("x");
    private double delta=0.001;
    @Test
    public void AbsoluteValueExpressionTest(){
        Expression test1=new AbsoluteValueExpression(arg1);
        Expression test2=new AbsoluteValueExpression(arg2);
        assertEquals(1,test1.eval(),delta);
        assertEquals(1,test2.eval(),delta);
        assertEquals("1.0",test1.toString());
        assertEquals("-(-1.0)",test2.toString());
    }
    @Test
    public void DerivativeExpressionTest(){
        x.store(2);
        ProductExpression product=new ProductExpression(x,x);
        DifferenceExpression difference=new DifferenceExpression(product,arg3);
        Expression expression=new DerivativeExpression(difference,x);
        assertEquals(2*x.eval(),expression.eval(),delta);
    }
    @Test
    public void DifferenceExpressionTest(){
        Expression expression=new DifferenceExpression(arg3,arg1);
        assertEquals(1.0,expression.eval(),delta);
        assertEquals("(2.0-1.0)",expression.toString());
    }
    @Test
    public void DivisionExpressionTest(){
        Expression expression=new DivisionExpression(arg1,arg3);
        assertEquals(0.5,expression.eval(),delta);
        assertEquals("(1.0/2.0)",expression.toString());
    }
    @Test
    public void ExponentiationExpressionTest(){
        Expression expression=new ExponentiationExpression(arg1,arg3);
        assertEquals(1.0,expression.eval(),delta);
        assertEquals("(1.0^2.0)",expression.toString());
    }
    @Test
    public void NegationExpressionTest(){
        Expression test1=new NegationExpression(arg1);
        assertEquals(-1.0,test1.eval(),delta);
        assertEquals("-(1.0)",test1.toString());
        Expression test2=new NegationExpression(arg2);
        assertEquals(1.0,test2.eval(),delta);
        assertEquals("-(-1.0)",test2.toString());
    }
    @Test
    public void NumberExpressionTest(){
        assertEquals(1.0,arg1.eval(),delta);
        assertEquals("1.0",arg1.toString());
    }
    @Test
    public void ProductExpressionTest(){
        Expression expression=new ProductExpression(arg1,arg3);
        assertEquals(2.0,expression.eval(),delta);
        assertEquals("(1.0*2.0)",expression.toString());
    }
    @Test
    public void SumExpressionTest(){
        Expression expression=new SumExpression(arg1,arg3);
        assertEquals(3.0,expression.eval(),delta);
        assertEquals("(1.0+2.0)",expression.toString());
    }
    @Test
    public void VariableTest(){
        x.store(2);
        assertEquals(2.0,x.eval(),delta);
        assertEquals("x",x.name());
        assertEquals("x=2.0",x.toString());
    }
    @Test
    public void NewtonsMethodTest(){
        x.store(1.4);
        ProductExpression product=new ProductExpression(x,x);
        DifferenceExpression difference=new DifferenceExpression(product,arg3);
        double res=new NewtonsMethod().zero(difference,x,1.4,0.01);
        assertEquals(1.4142,res,0.1);
    }
}
