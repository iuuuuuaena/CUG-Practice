package lab3.expression;

/**
 * Class to compute the exponentiation of two Expression
 * @author zhilinh
 *
 */
public final class ExponentiationExpression implements Expression {//幂计算

	private Expression base, exponent;
	
	/**
	 * Public constructor that assigns two Expressions to instance Expressions.
	 * 
	 * @param base of the exponentiation
     * @param exponent of the exponentiation
	 */
	public ExponentiationExpression(Expression base, Expression exponent) {
		this.base = base;
		this.exponent = exponent;
	}
	
	/**
	 * toString method that returns a string of assigned Expressions and an
	 * exponentiation operator with two parentheses. 
	 */
	@Override
	public String toString() {
		return "("+base.toString()+"^"+exponent.toString()+")";
//		throw new Exception("Need to be implemented！");
	}
	
	/**
	 * Method that returns the result of the computation.
	 * 
	 * @return returns the value of the Expression. 
	 */
	public double eval() {
		return Math.pow(base.eval(),exponent.eval());
//		throw new Exception("Need to be implemented！");
	}

}
