/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S. 
*/

/*
The string T can have duplicated characters, so need to maintain a count for each unique character. We also need to keep track of which characters have been seen during the scan. We could use two maps, but a more elegant way is to use one map intialized as the count in T, and as we scan S and see a character in T, we decrement the individual count. As we scan the S, we also maintain the left side of the window as "istart", and increment it as needed. There are several things to consider:
1. how to distinguish between characters appearing in T and not? (e.g. "D" v.s. "A")
2. how to know whether we have all the characters we need to construct T?

For Q1, we can use an index vector (dict[256]) to store the occurrences of each alphabet in T, and for other alphabets, initialized as -s.len(). When scanning, if we see the individual count of a char to be smaller or equal than -s.len(), we know that it does not appear in T.
For Q2, we maintain another variable "count", initialized as T.len(), and decremented only when we have seen a "useful" character. "useful" means character appearing in T and also not redundant. How to know if it is redundant or not? We can check the individual count is negative or not. When count == 0, we know that s[istart, i] covers T.
The next step is to check if we could move istart to the right and remove some redundant characters. This can be checked by individual count ++dict[s[istart]] <= 0. After this step, s[istart, i] is the minimum window seen so far containing T, by definition, s[istart] for sure is needed for T.
Next is to continue scanning forward. This gives 16ms solution.

An optimization (16ms=>12ms): we remove s[istart], update the counts (dict and count), and move on. Once count == 0 again, we go back to previous step again. Because we know for sure that we don't need s[istart] in layer searches, so we can remove it and update count. This can avoid many uncessary executiong of if(count == 0) part.

The code can be further shortened: in the while loop:
while(++dict[s[istart] <= 0) istart++;
and then only do: istart++;
*/

class Solution {
public:
    string minWindow(string s, string t) {
        int slen = s.size();
        vector<int> dict(256, -slen);
        int nc = t.size();
        for(int i = 0; i < nc; ++i) {
            if(dict[t[i]] < 0) dict[t[i]] = 1;
            else dict[t[i]]++;
        }
        int istart = 0, count = nc;
        int min_len = INT_MAX, min_start = -1;
        for(size_t i = 0; i < s.size(); ++i) {
            if(--dict[s[i]] >= 0) count--;
            if(count == 0) {
                while(dict[s[istart]] < 0) {
                    dict[s[istart++]]++;
                }
                int len = i-istart+1;
                if(len < min_len) { min_len = len; min_start = istart; }
                dict[s[istart++]]++; count = 1;
            }
        }
        return min_start == -1 ? "" : s.substr(min_start, min_len);        
    }
};

/*
Another solution is to use a queue to store (position in S of) T's characters seen so far, see below:
*/
/// An old solution using queue
/// Use a window to slide from left to right
/// Use counts to store the occurrences of characters needed to complete (when we see a character that is in t, we decrement the corresponding
/// count in counts. The values can become negative, indicating that the character is in excess.
/// Use a queue to store the current window, the queue is maintained in the following way:
/// 1. when we see a character that is in t, add it to end of queue
/// 2. If the new character in (1) is the same as the front of queue, and a is in excess we pop front (e.g. S = abea.. T = ab, but not: 
/// S = abea.. T = aab, where second a in S is required).
/// 3. when count is zero, we calculate the length, update minL if needed
/// 4. when we pop and push, we incre/decre counts[c], and depending on its sign, update cnt acoordingly.

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> counts(256, 0);
        int cnt = 0; // number of characters required to completely include t.
        for (int i = 0; i < t.size(); i++) { 
            counts[t[i]]++; 
            cnt++;
        }
        int minl = INT_MAX, mini = 0;
        deque<int> q;
        
        for(int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (t.find(c) == string::npos) continue;
            
            counts[c]--;
            if(counts[c] >= 0) cnt--;
            else if (s[q.front()] == c) {
                counts[c]++;
                q.pop_front();
            }
            q.push_back(i);
            
            if (cnt == 0) {
                while (counts[s[q.front()]] < 0) {
                    counts[s[q.front()]]++;
                    q.pop_front();
                }
                int len = q.back()-q.front()+1;
                if (len < minl) { minl = len; mini = q.front(); }
            }
        }
        if (minl == INT_MAX) return string();
        else return s.substr(mini, minl);
    }
};
