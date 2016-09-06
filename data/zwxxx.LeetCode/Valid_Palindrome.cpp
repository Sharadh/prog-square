/*
Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
*/

// recursive solution by Ke Hu (mrhuke@gmail.com) in Apr. 2013
class Solution {
public:

    bool isPalindrome(string s, int low, int high)
    {
        if (low >= high) return true;
        if (!isalnum(s[low]))
            return isPalindrome(s, low+1, high);
        else if (!isalnum(s[high]))
            return isPalindrome(s, low, high-1);
        else if (tolower(s[low]) != tolower(s[high]))
            return false;
        else
            return isPalindrome(s, low+1, high-1);
    }

    bool isPalindrome(string s) {
        return isPalindrome(s, 0, s.size()-1);
    }
};

// iterative solution by Ke Hu (mrhuke@gmail.com) in Apr. 2013
class Solution {
public:

    bool isPalindrome(string s) {
        
        for ( int i = 0, j = s.size()-1; i < j; )
        {
            if (!isalnum(s[i])) ++i;
            else if (!isalnum(s[j])) --j;
            else if (tolower(s[i]) != tolower(s[j])) return false;
            else{ ++i; --j; }
        }
        return true;
    }
};