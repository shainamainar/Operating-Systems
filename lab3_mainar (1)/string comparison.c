#include <string.h>

#include <stdio.h>

int main()
// The strcmp method compares the first string to the second one. 



// if the result is 0, the two strings are equal
// if the result is negative, the first string is less than the second
// if the result is positive, the first string is more than the secon 
{

   // Try different combinations of string pairs

   // apple vs apple

   // apple vs apples

   // apple vs zebra

   // zebra vs apple

   // apple vs APPLE

   // APPLE vs apple

   char* S1 = strdup("apple");

   char* S2 = strdup("apple");

   char* S3 = strdup("zebra");
   int result = strcmp(S1, S2);
   char* S4 = strdup("APPLE");
   int result3 = strcmp(S1, S4);
   int result2 = strcmp(S1,S3);
   printf("%d\n", result);
   printf("%d\n", result3);
   printf("%d\n", result2);
}
