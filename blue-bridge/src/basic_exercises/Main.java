package basic_exercises;

import java.util.Arrays;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {

		Scanner scn = new Scanner(System.in);
		int n = scn.nextInt();
		int[] a = new int[n], b = new int[n];
		for (int i = 0; i < n; i++) {
			a[i] = scn.nextInt();
		}
		int m = scn.nextInt();
		int[] res = new int[m];
		for (int i = 0; i < m; i++) {
			b=Arrays.copyOf(a, a.length);
			int l = scn.nextInt();
			int r = scn.nextInt();
			int k = scn.nextInt();
			Arrays.sort(b, l - 1, r);
			res[i] = b[r - k];
		}
		for (int i = 0; i < m; i++) {
			System.out.println(res[i]);
		}

	}
}
