#include <iostream>
#include <vector>
#include <algorithm>  
#include <cstring>    
using namespace std;
using ll = long long;

int K;
vector<int> digits;
// dp[pos][sumMod][tight==0] caches the count once tight==0
ll dp[20][100][2];
bool seen[20][100][2];

// dfs returns the count of valid numbers for the suffix starting at 'pos',
// with current digit‐sum mod K = sumMod, and 'tight' indicating whether
// we've matched the prefix of the bound exactly so far.
ll dfs(int pos, int sumMod, bool tight) {
    if (pos == (int)digits.size()) {
        // base case...if we've placed all digits, check divisibility
        return (sumMod % K == 0) ? 1 : 0;
    }
    if (!tight && seen[pos][sumMod][0]) {
        return dp[pos][sumMod][0];
    }

    int limit = tight ? digits[pos] : 9;
    ll ans = 0;
    for (int d = 0; d <= limit; ++d) {
        bool nextTight = tight && (d == limit);
        ans += dfs(pos + 1, (sumMod + d) % K, nextTight);
    }

    if (!tight) {
        seen[pos][sumMod][0] = true;
        dp[pos][sumMod][0] = ans;
    }
    return ans;
}

// counts how many numbers in [0..n] have digit‐sum ≡ 0 (mod K)
ll countUpTo(ll n) {
    if (n < 0) return 0;
    digits.clear();
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    if (digits.empty()) digits.push_back(0);
    reverse(digits.begin(), digits.end());

    memset(seen, 0, sizeof(seen));
    return dfs(0, 0, true);
}

int main(){

    ll L, R;
    cin >> L >> R >> K;
    // result = count in [0..R] minus count in [0..L-1]
    ll result = countUpTo(R) - countUpTo(L - 1);
    cout << result << "\n";
    return 0;
}