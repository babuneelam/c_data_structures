#include <stdio.h>
#include <stdlib.h>

#define NO_MORE -1

void str_reverse(char *, int );
char *my_itoa(int , int , char *);
int get_bit(int , int );
int set_bit(int , int );
int clear_bit(int , int );
int flip_bit(int , int );
int turn_off_first_non_zero_bit(int);

char help_str[] = "Allowed Operations: \n"
    "	-1 - Exit\r\n"
    "	 1 - print help(this list)\r\n"
    "	 2 <num> <bit_pos> - test whether the bit in num at bit_pos is set (0 being LSB)\r\n"
    "	 3 <num> <bit_pos> - set a bit in num at bit_pos (0 being LSB)\r\n"
    "	 4 <num> <bit_pos> - clear a bit in num at bit_pos (0 being LSB)\r\n"
    "	 5 <num> <bit_pos> - flip a bit in num at bit_pos (0 being LSB)\r\n"
    "	 6 <num> - turn off firt non-zero bit in num\r\n"
    ;

int main()
{
    int op, num, bit_pos;
    unsigned int a;
    char str[12]; // should be able to hold -2^31(-2147483648) to 
		  // +2^32(2147483647). So, using 12 bits one bit for \0

/*
    scanf("%d", &num);
    a=num; // both a & num has same bits set in the representation
    printf("int num signed =%d unsigned %u \r\n", num, num);
    printf("unsigned a signed =%d unsigned %u \r\n", a, a);
*/

    printf("%s",help_str);
    scanf("%d", &op);
    while(op != NO_MORE)
    {
        switch(op)
        {
	    case 1:
    		printf("%s",help_str);
                break;
            case 2: /*Print bit in a num at bit_pos*/
                scanf("%d%d", &num, &bit_pos);
		if ((bit_pos <0) || (bit_pos >32))
		{
		    printf("	bit_pos must be b/w 0-31\r\n");
		    break;
		}
		printf("	num in binary: %s \r\n", my_itoa(num, 2, str));
                if(get_bit(num, bit_pos))
		    printf("	bit is set at %d \r\n", bit_pos);
                else
		    printf("	bit is not set at %d \r\n", bit_pos);
                break;
            case 3: /*set bit in a num at bit_pos */
                scanf("%d%d", &num, &bit_pos);
		if ((bit_pos <0) || (bit_pos >32))
		{
		    printf("	bit_pos must be b/w 0-31\r\n");
		    break;
		}
		printf("	num in binary: %s \r\n", my_itoa(num, 2, str));
		printf("	num in binary %s after setting bit at %d \r\n", my_itoa(set_bit(num, bit_pos), 2, str), bit_pos);
                break;
            case 4: /*clear bit in a num at bit_pos */
                scanf("%d%d", &num, &bit_pos);
		if ((bit_pos <0) || (bit_pos >32))
		{
		    printf("	bit_pos must be b/w 0-31\r\n");
		    break;
		}
		printf("	num in binary: %s\r\n", my_itoa(num, 2, str));
		printf("	num in binary %s after clearing bit at %d \r\n", my_itoa(clear_bit(num, bit_pos), 2, str), bit_pos);
                break;
            case 5: /* Flip a bit in a num at bit_pos */
                scanf("%d%d", &num, &bit_pos);
		if ((bit_pos <0) || (bit_pos >32))
		{
		    printf("	bit_pos must be b/w 0-31\r\n");
		    break;
		}
		printf("	num in binary: %s\r\n", my_itoa(num, 2, str));
		printf("	num in binary %s after flipping bit at %d \r\n", my_itoa(flip_bit(num, bit_pos), 2, str), bit_pos);
                break;
            case 6: /* Clear the first non-zero bit in a num */
                scanf("%d", &num);
		printf("	num in binary: %s\r\n", my_itoa(num, 2, str));
		printf("	num in binary %s after clearing first non-zero bit \r\n", my_itoa(turn_off_first_non_zero_bit(num), 2, str));
                break;
            default: /*error */
                printf("	Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    return 0;
}
// Bit operators:  >>, <<, |, &, ^, ~
//
// Integer representation in computers
// -----------------------------------
// Computers store integers in two's complement representation. 
// A +ve num is represented as itself. But, a -ve num is represented with 
// first bit set & rest of the bits representing a 2's complement of the num.
// for example, -3 if represented as a 4-bit num: 2's complement of 3 is 
// 2^3-3=8-3=5=101. So, -3 would be 1101. Generalizing this representation:
// representation of -K as a N-bit num = concat(1,2^(N-)-K). 
// So, -3 as a 4bit num is concat(1,8-3)=1101
// Another way: invert the bits in positive representation, then add 1 & then prepend sign bit.
// For -3: 3 as a 4-bit num would be 011, -3 would be sign bit,(100+1)=1101.
// representation of K + representation of -K =2^(N-1) (excluding the sign bit)
// Source: Cracking the coding intw book

// Binary to decimal converter: http://www.binaryhexconverter.com/binary-to-decimal-converter
// Decimal to binary converter: http://www.binaryhexconverter.com/decimal-to-binary-converter

// Arithmetic vs Logical shift : 
// -------------------------------
// https://en.wikipedia.org/wiki/Bitwise_operation#Arithmetic_shift
// https://en.wikipedia.org/wiki/Bitwise_operation#Logical_shift
// http://teaching.idallen.com/dat2343/09f/notes/04bit_operations_shift.txt
// http://stackoverflow.com/questions/7622/are-the-shift-operators-arithmetic-or-logical-in-c
//
// In an arithmetic right shift (ARSH), the sign bit is shifted in on the
// left, thus preserving the sign of the operand.  In all other shifts,
// zeroes are shifted in as needed. So logical and arithmetic are equivalent in left-shifting and for non-negative values in right shifting; 
// For negative numbers, represented by two's complement encoding, shifting 
// right by n bits has the effect of mathematically dividing it by 2n and 
// rounding towards −∞ (floor); thus right shifting is different for 
// non-negative and negative values. 
// for X < 0, X >> n = floor(X ÷ 2n)
// C stadard undefined behaviors (so, implementation-dependent):
//	left shifting a signed NEGATIVE integer (signed non-negative is OK), 
//	right shfting a signed NEGATIVE integer (signed non-negative is OK).
//
// To force a logical shift on a negative number, we can typecast it to a
// unisgned num & then shift.
// Another example:
// if you wanted to drop the left-most bit of an unsigned integer, then 
// you might try this as your mask:
//	~0 >> 1
// Unfortunately, this will get you into trouble because the mask will have 
// all of its bits set because the value being shifted (~0) is signed, thus 
// an arithmetic shift is performed. Instead, you'd want to force a 
// logical shift by explicitly declaring the value as unsigned, i.e. by 
// doing something like this:
// 	~0U >> 1;


// first LSB means bit_pos is 0, second LSB means bit_pos is 1
int set_bit(int num, int bit_pos)
{
    return (num | (1 << bit_pos));
}

// return 1 if set, 0 if not set
int get_bit(int num, int bit_pos)
{
    return ((num & (1 << bit_pos)) !=0);
}

int clear_bit(int num, int bit_pos)
{
    return (num & ~(1 << bit_pos));
}

int flip_bit(int num, int bit_pos)
{
    int mask = (1 << bit_pos);

    num ^= mask;
    // Alternative below code works too
/*    if (num & mask) // bit is set
	num &= ~mask;
    else // bit not set
	num |= mask; */
    return num;
}

int turn_off_first_non_zero_bit(int num)
{
    return(num & (num-1));
}

int get_num_bits_set(int num)
{
    int bits=0;

    while (num)
    {
	num=turn_off_first_non_zero_bit(num);
	bits++;
    }
    return bits;
}

int is_2_pow(int num)
{
    return(turn_off_first_non_zero_bit(num)? 1: 0);
}

// Shiting signed integers - results in undefined behavior in C


char *my_itoa(int num, int base, char *str)
{
    int is_negative=0, i=0, remainder;

    if ((base < 2) && (base > 16))
	return NULL; // error

    if (num ==0)
    {
	str[i++] = '0';
	str[i++] = '\0';
	return str;
    }
    if (num <0)
    {
        is_negative = 1;
	num = -num;
    }
    while (num)
    {
	remainder = num % base;
        str[i++] = (remainder > 9)?('a'+(remainder-10)):('0'+remainder);
        num = num/base;
    }
    if (is_negative)
	str[i++] = '-';
    str[i] = '\0'; // i not incremented here
    str_reverse(str, i);

    return str;
}

void str_reverse(char *str, int len)
{
    int i, j;
    char tmp;

    for (i=0, j=len-1; i<j; i++, j--)
    {
        tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
    }
}

