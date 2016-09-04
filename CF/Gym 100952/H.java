import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class H {
	public static BigInteger dp[][];

	public static void main(String args[]) {
		dp = new BigInteger[251][251];
		for(int i = 250 ; i >= 1 ; i--)
			for(int j = 1 ; j <= 250 ; j++) {
				dp[i][j] = new BigInteger("0");
				if(i == j) dp[i][j] = new BigInteger("1");
				if(i*2 == j) dp[i][j] = dp[i][j].add(new BigInteger("1"));
				if(i*2 < j) dp[i][j] = dp[i][j].add(dp[i][j-2*i]);
				if(i < 250) dp[i][j] = dp[i][j].add(dp[i+1][j]);
			}

		Scanner in = new Scanner(System.in);
		PrintWriter ot = new PrintWriter(System.out);

		int n = in.nextInt();
		while(n > 0) {
			ot.println(dp[1][n]);
			n = in.nextInt();
		}	

		ot.close();
	}
}