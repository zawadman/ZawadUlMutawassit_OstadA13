#include <iostream>    // for std::cin, std::cout
#include <vector>      // for std::vector
#include <string>      // for std::string
#include <algorithm>   // for std::min
#include <climits>     // for INT_MAX

int main(){
    std::string s;
    std::cin >> s;
    int n = int(s.size());

    // precompute palindrome table: isPal[i][j] == true if s[i..j] is a palindrome
    std::vector<std::vector<bool>> isPal(n, std::vector<bool>(n, false));
    for(int i = n - 1; i >= 0; --i){
        for(int j = i; j < n; ++j){
            if (s[i] == s[j] && (j - i < 2 || isPal[i + 1][j - 1])) {
                isPal[i][j] = true;
            }
        }
    }

    //dp[i] = minimum cuts needed so that s[0..i] is partitioned into palindromes
    std::vector<int> dp(n, INT_MAX);
    for(int i = 0; i < n; ++i){
        if (isPal[0][i]) {
            dp[i] = 0;  // no cut needed if the whole prefix is a palindrome
        } else {
            for(int j = 0; j < i; ++j){
                if (isPal[j + 1][i]) {
                    // cut between j and j+1
                    dp[i] = std::min(dp[i], dp[j] + 1);
                }
            }
        }
    }

    std::cout << dp[n - 1] << "\n";
    return 0;
}
