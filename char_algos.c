#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_MORE -1
#define MAX_STR_LEN 25

int my_is_num(char);
int my_is_alpha(char);
int my_is_alphanum(char);
int my_is_uppercase(char);
int my_is_lowercase(char);
int my_atoi(char *);
char *my_itoa(int , int , char *);
void my_strcpy(char *, char *);
int my_strcmp(char *, char *);
void str_reverse(char *);
void str_reverse1(char *, int);
int is_palindrome(char *);
void quick_sort(char *, int , int );
int qs_partition(char *, int , int , int );

char help_str[] = "Allowed Operations: \n"
    "	-1 - Exit\r\n"
    "	 1 - print help(this list)\r\n"
    "	 2 <char> - is_num\r\n"
    "	 3 <char> - is_alpha \r\n"
    "	 4 <char> - is_alphanum \r\n"
    "	 5 <char> - is_uppercase \r\n"
    "	 6 <char> - is_lowercase \r\n"
    "	 7 <str> - atoi \r\n"
    "	 8 <num> - itoa \r\n"
    "	 9 <str> - strcpy (max str len 20)\r\n"
    "	 10 <str1> <str2> - strcmp (max str len 20)\r\n"
    "	 11 <str> - reverse (max str len 20)\r\n"
    "	 12 <str> - check whether palindrome (max str len 20)\r\n"
    "	 13 <str> - sort (max str len 20)\r\n"
    ;

int main()
{
    int op, num;
    char c, src[MAX_STR_LEN], dst[MAX_STR_LEN];
    char str[MAX_STR_LEN]; // 25 len should be able to hold -2^31(-2147483648) to 
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
            case 2: /*is_num*/
		getchar();
                scanf(" %c", &c);
                if(my_is_num(c))
		    printf("	num\r\n");
                else
		    printf("	not num\r\n");
                break;
            case 3: /*is_alpha*/
		getchar();
                scanf(" %c", &c);
                if(my_is_alpha(c))
		    printf("	alpha\r\n");
                else
		    printf("	not alpha\r\n");
                break;
            case 4: /*is_alphanum*/
		getchar();
                scanf(" %c", &c);
                if(my_is_alphanum(c))
		    printf("	alphanum\r\n");
                else
		    printf("	not alphanum\r\n");
                break;
            case 5: /* is_uppercase */
		getchar();
                scanf(" %c", &c);
                if(my_is_uppercase(c))
		    printf("	uppercase\r\n");
                else
		    printf("	not uppercase\r\n");
                break;
            case 6: /* is_lowercase */
		getchar();
                scanf(" %c", &c);
                if(my_is_lowercase(c))
		    printf("	lowercase\r\n");
                else
		    printf("	not lowercase\r\n");
                break;
            case 7: /* atoi */
// why not scanf %s? because fgets offers protection against buffer overflows
// http://stackoverflow.com/questions/26955466/difference-between-gets-vs-scanf-vs-fgets-in-c-programming
// The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
// If a newline is read, it is stoed into the buffer. A terminating null byte \0 is stored after the last character in the buffer
		getchar();
                memset(src,'\n',MAX_STR_LEN);
                fgets(src, MAX_STR_LEN, stdin); 
                if(src[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                src[strlen(src)-1] = '\0'; // remove '\n' at the end

                //scanf("%s", src);
                printf("	atoi= %d\r\n",my_atoi(src));
                break;
            case 8: /* itoa */
                scanf("%d", &num);
                printf("	itoa= %s\r\n",my_itoa(num, 10, str));
                break;
            case 9: /* strcpy */
                //scanf("%s", src);
		getchar();
                memset(src,'\n',MAX_STR_LEN);
                fgets(src, MAX_STR_LEN, stdin); 
                if(src[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                src[strlen(src)-1] = '\0'; // remove '\n' at the end

		my_strcpy(src, dst);
		printf ("	copied str = %s\r\n", dst);
                break;
            case 10: /* strcmp */
                //scanf("%s%s", src, dst);
		getchar();
                memset(src,'\n',MAX_STR_LEN);
                fgets(src, MAX_STR_LEN, stdin); 
                if(src[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
  		    c= getchar();
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                src[strlen(src)-1] = '\0'; // remove '\n' at the end

                memset(dst,'\n',MAX_STR_LEN);
                fgets(dst, MAX_STR_LEN, stdin); 
                if(dst[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                dst[strlen(dst)-1] = '\0'; // remove '\n' at the end

		printf("	strcmp ret %d \r\n", my_strcmp(src, dst));
                break;
            case 11: /* reverse */
                //scanf("%s", src);
		getchar();
                memset(src,'\n',MAX_STR_LEN);
                fgets(src, MAX_STR_LEN, stdin); 
                if(src[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                src[strlen(src)-1] = '\0'; // remove '\n' at the end

		str_reverse(src);
		printf ("	reversed str = %s\r\n", src);
                break;
            case 12: /* check palindrome*/
                //scanf("%s", src);
		getchar();
                memset(src,'\n',MAX_STR_LEN);
                fgets(src, MAX_STR_LEN, stdin); 
                if(src[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                src[strlen(src)-1] = '\0'; // remove '\n' at the end

                if(is_palindrome(src))
		    printf("	palindrome\r\n");
                else
		    printf("	not palindome\r\n");
                break;
            case 13: /* sort*/
                //scanf("%s", src);
		getchar();
                memset(src,'\n',MAX_STR_LEN);
                fgets(src, MAX_STR_LEN, stdin); 
                if(src[MAX_STR_LEN-1] != '\n')
                {
                    printf("Input string is more than allowed limit \r\n");
                    while ( getchar() != '\n' ); // flush any additional chars from stdin
                    break;
                }
                src[strlen(src)-1] = '\0'; // remove '\n' at the end

		quick_sort(src, 0, strlen(src)-1);
		printf ("	sorted str = %s\r\n", src);
                break;
            default: /*error */
                printf("	Invalid operation\r\n");
                break;
        }
        scanf("%d", &op);
    }

    return 0;
}



// ASCII, Extended ASCII vs Unicode
// Source : http://stackoverflow.com/questions/19212306/whats-the-difference-between-ascii-and-unicode

// ASCII was meant for English only. Most ASCII characters are printable 
// characters of the alphabet such as abc, ABC, 123, ?&!, etc. The others 
// are control characters such as carriage return, line feed, tab, etc.
// ASCII table: http://www.asciitable.com/
// '1'-30, '9'-39, 'A'-65, 'Z'-90, 'a'-97, 'z'-122, ' '-20

// ASCII Extended
// Some clever people started using the 8th bit to encode more characters to 
// support their language (to support "é" for example). Just using one extra 
// bit doubled the size of the original ASCII table to map up to 256 
// characters (2^8 = 256 characters). There are many variations of the 
// 8-bit ASCII table, for example, the ISO 8859-1, also called ISO Latin-1.
// Extended ASCII table: http://www.asciitable.com/

// Unicode, The Rise
// https://en.wikipedia.org/wiki/List_of_Unicode_characters
// ASCII Extended solves the problem for languages that are based on the 
// Latin alphabet... what about the others needing a completely different 
// alphabet? Greek? Russian? Polish? Chinese and the likes?
// We would have needed an entirely new character set... that's the rational 
// behind Unicode. Unicode doesn't contain every character from every 
// language, but it sure contains a gigantic amount of characters.
// Unicode contains a repertoire of more than 120,000 characters

// Unicode Encoding
// You cannot save text to your hard drive as "Unicode". Unicode is an 
// abstract representation of the text. You need to "encode" this abstract 
// representation. That's where an Encoding comes into play (UTF-8, UTF-16, etc.).


// Unicode is a superset of ASCII, and the numbers 0–128 have the same meaning 
// in ASCII as they have in Unicode. For example, the number 65 means 
// "Latin capital 'A'".



// is num, is alpha, isuppercase,...
int my_is_num(char c)
{
    return((c>='1')&&(c<='9'));
}

int my_is_alpha(char c)
{
    return(((c>='A')&&(c<='Z')) || ((c>='a')&&(c<='z')));
}

int my_is_alphanum(char c)
{
    return(((c>='1')&&(c<='9')) || ((c>='A')&&(c<='Z')) || ((c>='a')&&(c<='z')));
}

int my_is_uppercase(char c)
{
    return((c>='A')&&(c<='Z'));
}

int my_is_lowercase(char c)
{
    return((c>='a')&&(c<='z'));
}



// my atoi functions
int my_atoi(char *str)
{
    int i=0, sign=1, num=0;

    if (!str)
	return 0; // error, what to return??

    if (strlen(str) > 11) // we would have number overflow!!
	return 0; // error, what to return??
    if (str[i] == '-')
    {
	sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++)
    {
	if (!my_is_num(str[i]))
	    return 0; // error, what to return??
	num = num*10 + (str[i] - '0');
    }
    return (sign*num);
}

// my itoa functions
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
    str_reverse1(str, i);

    return str;
}

// strcpy in place
void my_strcpy(char *src, char *dst)
{
    while (*dst++ = *src++);
}

//strcpy for overlapping buffers

//strcmp
int my_strcmp(char *src, char *dst)
{
    int i;

    for (i=0; i< strlen(src); i++)
    {
	if ((dst[i] == '\0') || (src[i] > dst[i]))
	    return 1;
	else if (src[i] < dst[i])
	    return -1;
    }
    if (dst[i] != '\0')
	return -1;
    return 0;
}

// reverse a string in place
void str_reverse(char *str)
{
    int i, j;
    char tmp;

    for (i=0, j=strlen(str)-1; i<j; i++, j--)
    {
        tmp = str[i];
	str[i] = str[j];
	str[j] = tmp;
    }
}

void str_reverse1(char *str, int len)
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


// check for palidrome
int is_palindrome(char *s)
{
    int i, j;

    for (i=0, j=strlen(s)-1; i<j; i++, j--)
    {
	if (s[i] != s[j])
	    return 0;
    }
    return 1;
}


// sort a string.. Assuming an ASCII string (okay for other code as well)
void quick_sort(char *s, int start, int end)
{
    int pivot, partition_index;

    if (start >= end)
        return;

    pivot = s[end]; // picking last element of the list as pivot
                    // Other ways: choose a random index, 
                    // choose 3 random indices & take median of the three numbers at these indices.
    partition_index = qs_partition(s, start, end, pivot);
    quick_sort(s, start, partition_index-1);
    quick_sort(s, partition_index+1, end);
}

int qs_partition(char *s, int start, int end, int pivot)
{
    int left=start-1, right=end, tmp;

    while (left < right)
    {
        while (s[++left] < pivot) ;
        while ((right > 0) && (s[--right] > pivot)) ;
        if (left >= right )
            break;
        // swap the elements at indices left & right
        tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
    }

    // swap elements at end & left
    tmp = s[left];
    s[left] = s[end];
    s[end] = tmp;

    return left;
}

