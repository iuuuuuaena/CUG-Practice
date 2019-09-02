package lab3.expression;

/**
 * Class to compute the difference between two Expressions.
 * @author zhilinh
 *
 */
public final class DifferenceExpression implements Expression {//减法

	private Expression op1, op2;
	
	/**
	 * Public constructor that assigns two operand to local instance to compute.
	 * 
	 * @param op1 the first operand of the subtraction
     * @param op2 the second operand of the subtraction
	 */
	public DifferenceExpression(Expression op1, Expression op2) {
		this.op1 = op1;
		this.op2 = op2;
	}
	
	/**
	 * toString method that returns a string of assigned Expressions and a subtraction
	 * operator with two parentheses.
	 */
	@Override
	public String toString() {
		return "("+op1.toString()+"-"+op2.toString()+")";
//		throw new Exception("Need to be implemented！");
	}
	
	/**
	 * Method that returns the result of the computation.
	 * 
	 * @return returns the value of the Expression.
	 */
	public double eval() {
		return op1.eval()-op2.eval();
//		throw new Exception("Need to be implemented！");
	}

}
