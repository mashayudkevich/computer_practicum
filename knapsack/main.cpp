#include <iostream>
#include <vector>
#include <algorithm>
 
 
int main() {
    int n, K;
    std::cin >> n >> K;
    std::vector<int> v(n), w(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i] >> w[i];}
 
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(K+1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= K; ++j) {
            if (w[i-1] <= j) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
 
    std::vector<int> items(n, 0);
    int weight = K;
    for (int i = n; i > 0 && weight > 0; --i) {
        if (dp[i][weight] != dp[i-1][weight]) {
            items[i-1] = 1;
            weight -= w[i-1];
        }
    }
 
    std::cout << dp[n][K] << " " << weight << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << items[i] << " ";
    }
    std::cout << "\n";
 
    return 0;}
