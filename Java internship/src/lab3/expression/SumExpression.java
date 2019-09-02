package lab3.expression;

/**
 * Class to compute the sum of the values of two Expressions
 * @author zhilinh
 *
 */
public final class SumExpression implements Expression {//加法
	
	private Expression addend1, addend2;
	
	/**
	 * Public constructor that assigns two Expressions to instance Expressions.
	 * 
	 * @param addend1 the first addend of the sum
     * @param addend2 the second addend of the sum
	 */
	public SumExpression(Expression addend1, Expression addend2) {
		this.addend1 = addend1;
		this.addend2 = addend2;
	}
	
	/**
	 * Method that returns the value of the sum of two Expressions.
	 * 
	 * @return returns the value of the Expression.
	 */
	public double eval() {
		return addend1.eval()+addend2.eval();
//		throw new Exception("Need to be implemented！");
	}
	
	/**
	 * toString method that returns two expressions and the addition
	 * operator with parentheses.
	 */
	@Override
	public String toString() {
		return "("+addend1.toString()+"+"+addend2.toString()+")";
//		throw new Exception("Need to be implemented！");
	}

}
