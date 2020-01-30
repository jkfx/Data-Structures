package basic_exercises;

import java.math.BigDecimal;

public class Main {

	public static void main(String[] args) {
		BigDecimal d1 = new BigDecimal("3.1415926535");
		BigDecimal d2 = new BigDecimal("2.7182818284");
		BigDecimal d3 = d1.divide(d2, 10, BigDecimal.ROUND_UP);
		System.out.println(3.1415926535 / 2.7182818284);
		System.out.println(d3);
	}
}