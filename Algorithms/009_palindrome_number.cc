/*
Determine whether an integer is a palindrome. Do this without extra space.

Some hints:

Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/

// Most straightforward solution: construct the reverse number from x, and compare with x
// Doesn't handle overflow explicitly because when overflow happens, y != x

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int y = 0, num = x;
        while (num > 0) {
            y = y * 10 + num % 10;
            num /= 10;
        }
        return y == x;
    }
};
