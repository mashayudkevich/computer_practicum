#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
const int MAXN = 10000;

int main(){
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);}

    vector<int> colors(n, -1); // цвета вершин, -1 - вершина еще не раскрашена
    int num_colors = 0;

    for (int v = 0; v < n; v++) {
        bool used_colors[MAXN] = {}; // цвета, использованные для окраски соседних вершин
        for (int u : adj[v]) {
            if (colors[u] != -1) {
                used_colors[colors[u]] = true;
            }
        }
        for (int j = 0; ; j++) {
            if (!used_colors[j]) {
                colors[v] = j;
                num_colors = max(num_colors, j + 1);
                break;
            }
        }
    }


    cout << "Number of colors: " << num_colors << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": " << colors[i] << endl;
    }

    return 0;
}
