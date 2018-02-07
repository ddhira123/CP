import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.math.BigInteger;

public class Triangles2 {
    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        PrintWriter writer = new PrintWriter(System.out);

        int n = reader.nextInt();
        int x[] = new int[n];
        int y[] = new int[n];

        for(int i = 0 ; i < n ; i++) {
            x[i] = reader.nextInt();
            y[i] = reader.nextInt();
        }

        long sqrX = 0;
        long sqrY = 0;
        long sumX = 0;
        long sumY = 0;
        long sumXY = 0;

        BigInteger ans = new BigInteger("0");

        for(int i = 0 ; i < n ; i++) {
            sumX += x[i];
            sumY += y[i];

            sqrX += (long)x[i] * x[i];
            sqrY += (long)y[i] * y[i];
            sumXY += (long)x[i] * y[i];
        }

        for(int i = 0 ; i < n ; i++) {
            BigInteger val = new BigInteger("0");

            // a^2b^2
            Long a = sqrX;
            a -= 2 * sumX * x[i];
            a += (long)(n-i) * x[i] * x[i];

            Long b = sqrY;
            b -= 2 * sumY * y[i];
            b += (long)(n-i) * y[i] * y[i];

            BigInteger ab = new BigInteger(a.toString());
            ab = ab.multiply(new BigInteger(b.toString()));
            //

            // abcd
            Long mid = sumXY;
            mid -= sumY * x[i];
            mid -= sumX * y[i];
            mid += (long)(n-i) * x[i] * y[i];

            BigInteger abcd = new BigInteger(mid.toString());
            abcd = abcd.multiply(abcd);
            // 

            val = ab.subtract(abcd);
            val = val.multiply(new BigInteger("2"));

            ans = ans.add(val);

            sumX -= x[i];
            sumY -= y[i];

            sqrX -= (long)x[i] * x[i];
            sqrY -= (long)y[i] * y[i];
            sumXY -= (long)x[i] * y[i];
        }

        BigInteger dec = ans.divide(new BigInteger("8"));
        BigInteger frac = ans.mod(new BigInteger("8"));
        int f = frac.intValue();

        writer.print(dec);
        writer.print(".");

        if(f == 0) {
            writer.print("000");
        } else {
            writer.print(f * 125);
        }
        writer.println("0");

        writer.flush();
    }

    public static class InputReader {
        private BufferedReader reader;
        private StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream));
            tokenizer = null;
        }

        public String next() {
            while(tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                }
                catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }
}