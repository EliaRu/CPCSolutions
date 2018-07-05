/*
    The program computes in a bottom-up fashion how many
    combination may be made at each step. This is computed
    by doubling the combination from the previous step and
    subtracting the number of combinations that start with
    a zero. This can be computed by subtracting the total
    combinations by the combinations that start with a zero
    both taken from the previous step.
    The BigInteger class of Java is used to manage the huge
    numbers resulting from this computation.
    Since the program must fill the table it takes O( n )
    time where n is the argument of the function.
    Reference: none.
 */
import java.util.Scanner;
import java.math.BigInteger;

class iwgbs{
    public static void main( String[] args ) {
        Scanner sc = new Scanner( System.in );
        int n = sc.nextInt( );
        BigInteger[] comb = new BigInteger[n + 1];
        BigInteger[] combWithZero = new BigInteger[n + 1];
        comb[1] = new BigInteger( "2" );
        combWithZero[1] = new BigInteger( "1" );
        for( int i = 2; i <=n; i++ ) {
            comb[i] = comb[i - 1].multiply( new BigInteger( "2" ) ).subtract( combWithZero[i - 1] );
            combWithZero[i] = comb[i - 1].subtract( combWithZero[i - 1] );
        }
        System.out.println( comb[n].toString( ) );
    }
}
