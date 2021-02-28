package H0507;

import java.util.Arrays;

public class Digits
{
    private int number;
    private int[] digits;
    
    public Digits(int number)
    {
        this.number = number;
        this.digits = new int[length(number)];
        for (int i = digits.length - 1; i >= 0; i--)
        {
            digits[i] = number % 10;
            number /= 10;
        }
    }
    
    public String toString()
    {
        return Arrays.toString(digits);
    }
    
    public boolean isStrictlyIncreasing()
    {
        for (int i = 0; i < digits.length - 1; i++)
        {
            if (digits[i] < digits[i+1]) continue;
            return false;
        }
        return true;
    }
    
    public boolean isPalindrome()
    {
        for (int i = 0; i < digits.length / 2; i++)
        {
            if (digits[i] == digits[digits.length - i - 1]) continue;
            return false;
        }
        return true;
    }
    
    private static int length(int number)
    {
        int k = 1;
        while (number / 10 > 0)
        {
            k++;
            number /= 10;
        }
        return k;
    }
    
    public static int rotate(int n, int r)
    {
        if (n < 0) return 0; // Error condition
        int g = length(n);
        r = r % g;
        if (r < 0) r = r + g;
        
        if (r == 0) return n;
        
        int p = 1, q = 1;
        for (int i = 1; i <= g - r; i++) p *= 10;
        for (int i = 1; i <= r; i++) q *= 10;
        return (n % p) * q + n / p;
    }
    
    public static void main(String[] args)
    {
        test(123321);
        test(12321);
        test(1234567);
        test(123409, 0);
        test(123409, 1);
        test(123409, 2);
        test(123409, 3);
        test(123409, 4);
        test(123409, 5);
        test(123409, 6);
        test(123409, 8);
        test(123409, -1);
        test(123409, -2);
        test(123409, -3);
        test(123409, 666);
    }
    
    public static void test(int n)
    {
        Digits digits = new Digits(n);
        System.out.printf("Number: %d -> %s\n", n, digits);
        System.out.printf("  isStrictlyIncreasing: %s\n", digits.isStrictlyIncreasing());
        System.out.printf("  isPalindrome: %s\n", digits.isPalindrome());
    }
    
    public static void test(int n, int r)
    {
        System.out.printf("rotate(%d, %d) = %d\n", n, r, rotate(n, r));
    }
}
