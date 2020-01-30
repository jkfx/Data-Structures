package test;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

class GenericMemoryCell<AnyType> implements Comparable<AnyType>{
	public AnyType read() {
		return storedValue;
	}

	public void write(AnyType x) {
		storedValue = x;
	}

	private AnyType storedValue;

	@Override
	public int compareTo(AnyType o) {
		// TODO Auto-generated method stub
		return 0;
	}

}

public class Test {
	public static void main(String[] args) {
		List<Integer> list = new ArrayList<Integer>();
		list.add(2);
	}
}
