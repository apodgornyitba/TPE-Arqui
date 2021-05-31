#include <libC.h>
#include <lib.h>
#include <stdarg.h>

#define  ULONG_MAX ((unsigned long)(~0L))      /* 0xFFFFFFFF */
#define  LONG_MAX  ((long)(ULONG_MAX >> 1))   /* 0x7FFFFFFF */
#define  LONG_MIN  ((long)(~LONG_MAX))       /* 0x80000000 */


//http://www.firmcodes.com/write-printf-function-c/
int printf(char *format, ...)
{
    char *traverse;
    unsigned int i;
    char *s;
    //Module 1: Initializing print's arguments
    va_list arg;
    va_start(arg, format);
    for (traverse = format; *traverse != '\0'; traverse++)
    {
        while (*traverse != '%')
        {
            putChar(*traverse);
            traverse++;
        }
        traverse++;
        //Module 2: Fetching and executing arguments
        switch (*traverse)
        {
        case 'c':
            i = va_arg(arg, int); //Fetch char argument
            putChar(i);
            break;
        case 'd':
            i = va_arg(arg, int); //Fetch Decimal/Integer argument
            if (i < 0)
            {
                i = -i;
                putChar('-');
            }
            puts(numtostr(i, 10));
            break;
        case 's':
            s = va_arg(arg, char *); //Fetch string
                puts(s);
            break;
        case 'x':
            i = va_arg(arg, unsigned int); //Fetch Hexadecimal representation
                puts(numtostr(i, 16));
            break;
        }
    }
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg);
    return 0;
}

//http://www.firmcodes.com/write-printf-function-c/
char *numtostr(unsigned int num, int base)
{
    static char Representation[] = "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;
    ptr = &buffer[49];
    *ptr = '\0';
    do
    {
        *--ptr = Representation[num % base];
        num /= base;
    } while (num != 0);
    return (ptr);
}

//https://code.woboq.org/gcc/libiberty/strtol.c.html
long strtol(const char *nptr, char **endptr, register int base)
{
        register const char *s = nptr;
        register unsigned long acc;
        register int c;
        register unsigned long cutoff;
        register int neg = 0, any, cutlim;
         /*Skip white space and pick up leading +/- sign if any.
         * If base is 0, allow 0x for hex and 0 for octal, else assume decimal; if base is already 16, allow 0x.
         */
        do {
                c = *s++;
        } while (c == ' ');
        if (c == '-') {
                neg = 1;
                c = *s++;
        } else if (c == '+')
                c = *s++;
        if ((base == 0 || base == 16) && c == '0' && (*s == 'x' || *s == 'X')) {
                c = s[1];
                s += 2;
                base = 16;
        }
        if (base == 0)
                base = c == '0' ? 8 : 10;
        cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
        cutlim = cutoff % (unsigned long)base;
        cutoff /= (unsigned long)base;
        for (acc = 0, any = 0;; c = *s++) {
                if ( c >= '0' && c <= '9' )
                        c -= '0';
                else if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                        c -= (c >= 'A' && c <= 'Z') ? 'A' - 10 : 'a' - 10;
                else
                        break;
                if (c >= base)
                        break;
                if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
                        any = -1;
                else {
                        any = 1;
                        acc *= base;
                        acc += c;
                }
        }
        if (any < 0) {
                acc = neg ? LONG_MIN : LONG_MAX;
        } else if (neg)
                acc = -acc;
        if (endptr != 0)
                *endptr = (char *) (any ? s - 1 : nptr);
        return (acc);
}

//https://iq.opengenus.org/how-printf-and-scanf-function-works-in-c-internally/
int scanf (char * str, ...)
{
    va_list vl;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0}, c;
    char *out_loc;
    
    while(c != ' ') 
    {
        if (getChar(&c))
        {   
 	       buff[i] = c;
 	       i++;
 	    }
 	}
 	va_start( vl, str );
 	i = 0;
 	while (str && str[i])
 	{
 	    if (str[i] == '%') 
 	    {
 	       i++;
 	       switch (str[i]) 
 	       {
 	           case 'c': 
 	           {
	 	           *(char *)va_arg( vl, char* ) = buff[j];
	 	           j++;
	 	           ret ++;
	 	           break;
 	           }
 	           case 'd': 
 	           {
	 	           *(int *)va_arg( vl, int* ) = strtol(&buff[j], &out_loc, 10);
	 	           j+=out_loc -&buff[j];
	 	           ret++;
	 	           break;
 	            }
 	            case 'x': 
 	            {
	 	           *(int *)va_arg( vl, int* ) = strtol(&buff[j], &out_loc, 16);
	 	           j+=out_loc - &buff[j];
	 	           ret++;
	 	           break;
 	            }
 	        }
 	    } 
 	    else 
 	    {
 	        buff[j] = str[i];
            j++;
        }
        i++;
    }
    va_end(vl);
    return ret;
}

//https://www.techiedelight.com/implement-strcmp-function-c/
// Function to implement strcmp function
int strcmp(const char *X, const char *Y)
{
    while (*X)
    {
        // if characters differ, or end of the second string is reached
        if (*X != *Y) {
            break;
        }
         // move to the next pair of characters
        X++;
        Y++;
    }
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

int putChar(char c)
{
    char buff[2] = {0};
    buff[0] = c;
    return write(1,buff,2);
}

void puts(char * str)
{
    while(*str) {
        putChar(*str);
        str++;
    }
}

int getChar(char * c)
{
    char buffAux[2] = {0};
    int ret = read(0, buffAux, 2);
    if (ret <= 0)
        return -1;
    *c = buffAux[0];
    return ret;
}

// Función Hexa to Int
//https://stackoverflow.com/questions/10156409/convert-hex-string-char-to-int
uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        uint8_t byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}
