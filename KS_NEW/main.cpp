#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int weight;};

struct Res {
    int obj;
    int opt;
    vector<int> selectedItems;};

Res ks(int n, int K, const vector<Item>& items) {
    vector<vector<int>> dp(n + 1, vector<int>(K + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= K; j++) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][j] = dp[i - 1][j];}}}
    
    Res result;
    result.obj = dp[n][K];
    
    int rw = K;
    for (int i = n; i > 0; i--) {
        if (dp[i][rw] != dp[i - 1][rw]) {
            result.selectedItems.push_back(1);
            rw -= items[i - 1].weight;
        } else {
            result.selectedItems.push_back(0);}}
    
    result.opt = result.selectedItems[n - 1];
    
    return result;}

int main() {
    int n, K;
    cin >> n >> K;
    
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }
    
    Res result = ks(n, K, items);
    
    cout << result.obj << " " << result.opt << endl;
    
    for (int i = n - 1; i >= 0; i--) {
        cout << result.selectedItems[i] << " ";
    }
    
    return 0;}
