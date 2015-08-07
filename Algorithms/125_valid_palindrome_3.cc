// Similar to solution 2, but with two sentinels at front and end. This can save the boundary checks in the inner while loop.

class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        s = 'a' + s + 'a';
        int n = s.size();
        int i(-1), j(n);
        while (i < j) {
            while (!isAlphaNumeric(s[++i])) ;
            while (!isAlphaNumeric(s[--j])) ;
            
            // i and j point to first meaningful characeter
            if (!isSame(s[i], s[j])) return false;
        }
        return true;
    }
    bool isAlphaNumeric(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }
    bool isSame(char c1, char c2) {
        if (c1 == c2) return true;
        if (c1 >= 'A' && c1 <= 'Z') return c2 == c1 + 32;
        if (c1 >= 'a' && c1 <= 'z') return c2 == c1 - 32;
    }
};