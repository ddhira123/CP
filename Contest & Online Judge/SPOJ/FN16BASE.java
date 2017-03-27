import java.math.*;
import java.io.*;
import java.util.*;

public class Main {
	final static int MAGIC = 31623;
	final static int ASD = 300000;
	static boolean[] flag;
	static int[] primes;
	static long[] temp;
	static long[] haha;
	static List<Long> primaNya;
	static List<Long> countNya;
	static int tSize;
	static List<Long> factors;
	static long limit;

	private static void sieve() {
		flag = new boolean[MAGIC];
		temp = new long[MAGIC];

		for(int i = 2 ; i < MAGIC ; i++)
			if(!flag[i]) {
				temp[tSize++] = i;
				for(int j = i ; j < MAGIC ; j += i)
					flag[j] = true;
			}

		primes = new int[tSize];
		for(int i = 0 ; i < primes.length ; i++)
			primes[i] = (int)temp[i];
	}

	private static void factorizeSmall(long val) {
		for(int i = 0 ; i < primes.length && val >= primes[i] ; i++) {
			while(val % primes[i] == 0) {
				temp[tSize++] = primes[i];
				val /= primes[i];
			}
		}
		if(val != 1)
			temp[tSize++] = val;
	}

	private static long mulmod(long a,long b,long c) {
		long ret = 0;
		long base = a % c;
		while(b > 0) {
			if(b % 2 == 1) ret = (ret + base) % c;
			base = (base + base) % c;
			b /= 2;
		}
		return ret;
	}

	private static long gcd(long a, long b) {
		while(b != 0) {
			long c = a % b;
			a = b;
			b = c;
		}
		return a;
	}

	private static long pollardRho(long n) {
		int i = 0;
		int k = 2;
		long x = 3;
		long y = 3;
		while(true) {
			i++;
			x = (mulmod(x,x,n) + n - 1) % n;
			long d = gcd(Math.abs(y - x),n);
			if(d != 1 && d != n) return d;
			if(i == k) {
				y = x;
				k *= 2;
			}
		}
	}

	private static void factorize(long val) {
		if(val <= limit) factorizeSmall(val);
		else if(BigInteger.valueOf(val).isProbablePrime(10)) temp[tSize++] = val;
		else {
			long divisor = pollardRho(val);
			factorize(divisor);
			factorize(val / divisor);
		}
	}

	private static void populate(int step, long mul) {
		if(step == primaNya.size()) {
			if(mul != 1) {
				factors.add(mul);
				// System.out.println(mul);
			}
		} else {
			long lel = 1;
			for(int i = 0 ; i <= countNya.get(step) ; i++) {
				populate(step+1, mul * lel);
				lel *= primaNya.get(step);
			}
		}
	}

	private static long getBase(long y, long base) {
		long cur = 1;
		long ret = 0;

		while(y > 0) {
			long sisa = y % base;
			long div = y / base;

			if(sisa >= 10) {
				return -1L;
			}

			ret += cur * sisa;

			y = div;
			cur *= 10;
		}

		return ret;
	}

	private static long solver(long y, long l) {
		temp = new long[ASD];
		factors = new ArrayList<Long>();

		for(long i = y ; i >= y-9 ; i--) {
			tSize = 0;
			factorize(i);
			haha = new long[tSize];
			for(int it = 0 ; it < tSize ; it++)
				haha[it] = temp[it];

			Arrays.sort(haha);

			primaNya = new ArrayList<Long>();
			countNya = new ArrayList<Long>();

			for(int it = 0 ; it < tSize ; ) {
				int j = it;
				while(j < tSize && haha[it] == haha[j]) {
					j++;
				}
				primaNya.add(haha[it]);
				countNya.add((long)j-it);
				// System.out.println(haha[it] + " " + (j-it));
				it = j;
			}

			// System.out.println("now " + i + " tSize=" + tSize);
			// for(long x : primaNya) {
			// 	System.out.println(x);
			// }
			populate(0, 1);
		}

		long ret = y+1;
		long basisNya = -1;
		for(long x : factors) {
			long temp = getBase(y, x);
			// System.out.println("y " + y + "x " + x + " temp" + temp);
			if(temp != -1 && temp >= l && x > basisNya) {
				basisNya = x;
			} 
		}

		return basisNya;
	}

	public static void main(String[] args) throws IOException {
		sieve();
		limit = (long)(MAGIC-1) * (MAGIC-1);
		Scanner reader = new Scanner(System.in);
		PrintWriter writer = new PrintWriter(System.out);

		while(reader.hasNextLine()) {
			String temp = reader.nextLine();
			long y, l;
			String strs[] = temp.split(" ");
			y = Long.parseLong(strs[0]);
			l = Long.parseLong(strs[1]);

			System.out.println(solver(y, l));
		}

		writer.close();
	}
}