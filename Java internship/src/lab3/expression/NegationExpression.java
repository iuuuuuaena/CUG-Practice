package lab3.expression;

/**
 * Class to reverse the sign of an Expression.
 * @author zhilinh
 *
 */
public final class NegationExpression implements Expression {//取负

	private Expression operand;
	
	/**
	 * Public constructor that assigns the Expression to instance Expression.
	 * 
	 * @param operand the expression whose value will be returned with a negative sign 
	 */
	public NegationExpression(Expression operand) {
		this.operand = operand;
	}
	
	/**
	 * Method that returns the value of the Expression with an contrary sign.
	 * 
	 * @return returns the value of the Expression.
	 */
	public double eval() {
		return -operand.eval();
//		throw new Exception("Need to be implemented！");
	}
	
	/**
	 * toString method that returns the Expression with an contrary sign.	 * 
	 */	
	@Override
	public String toString() {
		return "-("+operand.toString()+")";
//		throw new Exception("Need to be implemented！");
	}

}
