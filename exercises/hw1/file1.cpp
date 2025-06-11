/* Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'


*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

#include <iostream>
using namespace std;

int main() {
 
  // initialize limits, product and sum
  int limit = 10, even_product = 1, odd_product = 1, sum;
  // initialize char c
  char c;
  // print the limit
  cout << "The value of limit is " << limit << endl;
  
  // loop to calculate even and odd product from 1 to 10
  for (int i = 1; i <= limit; ++i) {
    // if the number is odd, multiply to odd_product
    if (i % 2 == 1) {
      odd_product *= i; 
    } else { // else multiply to even_product
      even_product *= i;
    }
  }
  // print the sum
  sum = even_product + odd_product;
  cout << "The Sum = " << sum << "\n";

  // loop to print alternate character in reverse
  for (c = 'Z'; c >= 'A'; c -= 2) {
    cout << c << " ";
  }
  cout << endl;

  return 0;
}
// limit should be 10 since line 20 is directly printing the value of it

// even and odd product should be initialized to 1, since 0 times anything is zero.
// sum will always be zero if they are initialized to 0. Also, the even and odd product
// should be switched, and the loop should start from 1 to avoid the 0 multiplier issue.

// the i is never define, we can either change the representation to i, or change the
// cout << i << " " to cout << c << " "