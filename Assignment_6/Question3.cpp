#include <iostream>
#include <vector>
using namespace std;

// int longestCommonSubsequence(string s, string t, int n, int m, vector<vector<int>> &dp) {
//     if (n <= 0 || m <= 0) {
//         return 0;
//     }
//     if (dp[n - 1][m - 1] != -1) {
//         return dp[n - 1][m - 1];
//     }
//     int val;
//     if (s[n - 1] == t[m - 1]) {
//         val = 1 + longestCommonSubsequence(s, t, n - 1, m - 1, dp);
//     }
//     else {
//         int val1 = longestCommonSubsequence(s, t, n - 1, m, dp);
//         int val2 = longestCommonSubsequence(s, t, n, m - 1, dp);
//         val = max(val1, val2);
//     }
//     return dp[n - 1][m - 1] = val;
// }

int main() {
    string s, t;
    cout << "Enter the first string: ";
    cin >> s;
    cout << "Enter the second string: ";
    cin >> t;
    int n = s.length();
    int m = t.length();

    // vector<vector<int>> dp(n, vector<int>(m, -1)); // -1 represents not calculated yet
    // int lcsLength = longestCommonSubsequence(s, t, n, m, dp);
    // cout << "Length of longest common subsequence: " << lcsLength << endl;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int val;
            if (s[i - 1] == t[j - 1]) {
                val = 1 + dp[i - 1][j - 1];
            }
            else {
                val = max(dp[i - 1][j], dp[i][j - 1]);
            }
            dp[i][j] = val;
        }
    }
    cout << "Length of longest common subsequence: " << dp[n][m] << endl;


    string lcs = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i - 1] == t[j - 1]) {
            lcs = s[i - 1] + lcs;
            i--;
            j--;
        }
        else {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            }
            else {
                j--;
            }
        }
    }

    cout << "Longest Common Subsequence: " << lcs << endl;
    return 0;
}