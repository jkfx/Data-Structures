package basic_exercises;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class Main {

	public static int f(String s)
	{
		return s.split("[\\+\\-*/]").length;
	}
	
	public static void main(String[] args)
	{
		System.out.println(f("12+35*5-2*18/9-3")); //7
		System.out.println(f("354*12+3-14/7*6")); //6
	}
}
