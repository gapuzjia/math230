import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Lab2 
{
    public static void main (String[]args)throws IOException
	{
		String creditCard;
		File file = new File("C:\\Users\\Jia Gapuz\\Desktop\\Math230Lab2data.txt");
		
		if(!file.exists())
		{
			System.out.println("The file cannot be found");
			System.exit(0);
		}
		
		//declare scanner
		Scanner inputFile = new Scanner(file);
		
		while(inputFile.hasNext())
		{
			//scan in next line from file and print to console
			creditCard = inputFile.nextLine();
			System.out.printf("The credit card number is: %s\n", creditCard);
			
			//if credit card number is exactly 16 digits, check if a valid card
			if(creditCard.length() == 16)
				isValid(creditCard);
			
			else
				System.out.printf("ERROR! Number MUST have exactly 16 digits\n");
			
			//convert credit card number to base 23
			convertBase23(creditCard);
		}
		
		//close file
		inputFile.close();
		
	}
	
	public static void isValid(String creditCard)
	{
		boolean visa = false;
		boolean masterCard = false;
		int checkDigit = 0;
		int currDigit;
				
		//if first digit of credit card is 4, card is a visa
		if(creditCard.charAt(0) == '4')
			visa = true;
		
		//if first two digits of credit card is 50 - 56 inclusive, card is mastercard
		else if(creditCard.charAt(0) == '5')
		{
			if(creditCard.charAt(1) - '0' > 0 &&creditCard.charAt(1) - '0' < 6 )
				masterCard = true;
		}
		
		//calculate check digit
		for(int i = 0; i < 15; i++)
		{
			//extract char at subscript i, convert to an integer
			currDigit = creditCard.charAt(i) - '0';
			
			//if digit is at an even subscript, multiply digit by two
			if(i % 2 == 0)
			{
				currDigit *= 2;
				
				//if the product is a two digit number, take the sum of the two digits
				if(currDigit > 9)
					currDigit = currDigit % 10 + currDigit / 10;
			}
				
			//add currDigit to checkDigit sum
			checkDigit += currDigit;
		}
		
		//take only difference of 10 and the ones digit in checkDigit
		checkDigit = 10 - (checkDigit % 10);
		
		//print out expected checkDigit and actual check digit
		System.out.printf("Check digit should be: %d\n" , checkDigit);
		System.out.printf("Check digit is: %d\n", creditCard.charAt(15) - '0');
		
	
		//if sum does not match check digit 
		if(checkDigit!= creditCard.charAt(15) - '0')
			System.out.println("Number is not valid");
		
		//if sum does match check digit
		else
		{
			if(visa)
				System.out.println("Number is a valid VISA card.");
			
			else if(masterCard)
				System.out.println("Number is a valid MasterCard.");
			
			else
				System.out.println("Number is valid, but not VISA or MasterCard");
		}
	}
	
	public static void convertBase23(String creditCard)
	{
		String lookup = "0123456789ABCDEFGHIJKLMN";
		long decCreditCard = 0;
		long base = 1;
		int [] nums = new int[30];
		int ctr = 0;
		
		//traverse the string backwards to convert to a long
		for(int i = creditCard.length() - 1; i > -1; i--)
		{
			decCreditCard += Character.getNumericValue(creditCard.charAt(i)) * base;
			base *= 10;
		}
		
		
		//convert long to base 23 and store remainders in nums array
		while(decCreditCard > 0)
		{
			nums[ctr] = (int)(decCreditCard % 23);
			decCreditCard /= 23;
			ctr++;
		}
		
		System.out.printf("The credit card number in base 23 is: ");
		
		//print out nums array backwards
		for(int i = ctr - 1; i > -1; i--)
			System.out.printf("%c", lookup.charAt(nums[i]));
		
		System.out.printf("\n\n");
		
	}
}
