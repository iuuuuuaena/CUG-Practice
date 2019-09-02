package lab3.operator;
/**
 * Enum that contains implements of BinaryOperator
 * @author zhilinh
 *
 */
public enum BinaryOperatorImp implements BinaryOperator {
	ADDITION{
		
		/**
		 * toString method that returns the addition operator "+".
		 */
		@Override
		public String toString() {
			return "+";
		}
		
		/**
		 * Method that returns the sum of arg1 and arg2.
		 * 
		 * @param arg1 the first addend.
		 * @param arg2 the second addend.
		 * @return the value of the sum.
		 */
		public double apply(double arg1, double arg2) {
			return arg1+arg2;
//			throw new Exception("Need to be implemented！");
		}
	},
	SUBTRACTION{
		
		/**
		 * toString method that returns the subtraction operator "-".
		 */
		@Override
		public String toString() {
			return "-";
		}
		
		/**
		 * Method that returns the difference of arg1 and arg2.
		 * 
		 * @param arg1 the first number.
		 * @param arg2 the second number.
		 * @return the value of the difference.
		 */
		public double apply(double arg1, double arg2) {
			return arg1-arg2;
//			throw new Exception("Need to be implemented！");
		}
	},
	MULTIPLICATION{
		
		/**
		 * toString method that returns the multiplication operator "*".
		 */
		@Override
		public String toString() {
			return "*";
		}
		
		/**
		 * Method that returns the product of arg1 and arg2.
		 * 
		 * @param arg1 the first number.
		 * @param arg2 the second number.
		 * @return the value of the product.
		 */
		public double apply(double arg1, double arg2) {
			return arg1*arg2;
//			throw new Exception("Need to be implemented！");
		}
	},
	DIVISION{
		
		/**
		 * toString method that returns the division operator "/".
		 */
		@Override
		public String toString() {
			return "/";
		}
		
		/**
		 * Method that returns the division of arg1 and arg2.
		 * 
		 * @param arg1 the first number.
		 * @param arg2 the second number.
		 * @return the value of the division.
		 */
		public double apply(double arg1, double arg2) {
			return arg1/arg2;
//			throw new Exception("Need to be implemented！");
		}
	},
	EXPONENTIATION{
		
		/**
		 * toString method that returns the exponentiation operator "^".
		 */
		@Override
		public String toString() {
			return "^";
		}
		
		/**
		 * Method that returns the product of arg1 and arg2.
		 * 
		 * @param arg1 the first number.
		 * @param arg2 the second number.
		 * @return the value of the exponentiation.
		 */
		public double apply(double arg1, double arg2) {
			return Math.pow(arg1,arg2);
//			throw new Exception("Need to be implemented！");
		}
	};
}
