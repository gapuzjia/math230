import java.util.*;

public class Lab1 
{
	public static void main (String[]args)
	{
		//declare variables
		long num;
		int decimal;
		int sum;
		
		//declare scanner
		Scanner scnr = new Scanner(System.in);
		
		//priming read
		System.out.print("Please enter a base 6 number (leading zeros are OK), 0 to quit: ");
		num = scnr.nextLong();		
		
		
		while(num > 0)
		{
			//if input is valid base 6 number, call all methods
			if(isBase6(num))
			{
				//convert base 6 to decimal
				decimal = (int)base6ToDecimal(num);
				
				//invoke base6ToDecimal method
				System.out.printf("The decimal value of your base 6 number %d is: %d\n", (int)num, decimal);
				
				//invoke cowabunga method
				System.out.printf("Invoking cowabunga: Divisible by 5, 7, both or neither? ");
				cowabunga(decimal);
				
				//invoke packpedalAndSum method
				System.out.printf("Your decimal number backwards is: ");
				sum = backpedalAndSum(decimal);
				System.out.println();
				System.out.printf("The sum of the digits of your decimal number is %d.\n\n", sum);
			}
			
			//if input is not a valid base 6 number, prompt user for another input
			else
				System.out.printf("Sorry, your number is not a base 6 number.\n\n");
			
			//read for next value
			System.out.print("Please enter a base 6 number (leading zeros are OK), 0 to quit: ");
			num = scnr.nextLong();
		}
		
		//print to console is user quits
		System.out.printf("Bye!");
	}
	
	public static boolean isBase6(long num)
	{
		boolean isValid = true;
		
		//strip last digit from num while digits remain 
		//or until flag is set to false
		while(num > 0 && isValid)
		{
			//if ones digit is out of the range 0 - 5,
			//set isValid to false
			if(num % 10 > 5)
				isValid = false;
			
			//truncate num
			num /= 10;
		}
		
		return isValid;
	}
	
	public static long base6ToDecimal(long n)
	{
		long result = 0;
		long last_digit;
		
		//Initializing base
		int base = 1;
		
		while(n > 0)
		{
			last_digit = n % 10;
			n = n / 10;
			result += last_digit * base;
			
			//update base
			base *= 6;
		}
		
		return result;
	}
	
	public static void cowabunga(int decimalNum)
	{
		//declare and initialize flags to false
		boolean divBy5 = false;
		boolean divBy7 = false;
		
		//check if divisible by 5
		if(decimalNum % 5 == 0)
			divBy5 = true;
		
		//check if divisible by 7
		if(decimalNum % 7 == 0)
			divBy7 = true;
		
		//check if divisible by 5, 7, both or neither
		if(divBy5 && divBy7)
			System.out.println("Both, Cowabunga!");
		
		else if(divBy5)
			System.out.println("5, Cowa!");
		
		else if(divBy7)
			System.out.println("7, Bunga!");
			
		else
			System.out.println("Neither, Fidlesticks!");	
	}
	
	public static int backpedalAndSum(int decimalNum)
	{
		int sum = 0;
		int digit;
		
		while(decimalNum > 0)
		{
			digit = decimalNum % 10;
			System.out.printf("%d ", digit);
			sum += digit;
			decimalNum /= 10;
		}
		
		return sum;
			
	}
	
	
	
}
