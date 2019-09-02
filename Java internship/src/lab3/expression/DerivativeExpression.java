package lab3.expression;

/**
 * Class to compute the derivative of an Expression. 
 * @author zhilinh
 *
 */
public class DerivativeExpression implements Expression {//表达式导数

	private final double deltaX = 1e-9;
	private Expression fn;
	private Variable independentVar;
	private double fnVal;
	
	/**
	* Creates an expression representing the derivative of the specified
	* function with respect to the specified variable.
	*
	* @param fn the function whose derivative this expression represents
	* @param independent the variable with respect to which we're
	* differentiating
	*/
	public DerivativeExpression(Expression fn, Variable independent) {
		this.fn=fn;
		fnVal=fn.eval();
		independentVar=independent;
//		throw new Exception("Need to be implemented！");
	}
	
	/**
	 * Method that returns the derivative of the Expression.
	 * 
	 * @return returns the value of the Expression.
	 */
	@Override
	public double eval() {
		independentVar.store(independentVar.eval()+deltaX);
		return (fn.eval()-fnVal)/deltaX;
//		throw new Exception("Need to be implemented！");
	}
}
