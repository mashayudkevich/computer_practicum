#include <iostream>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

vector<int> colorGraph(const vector<vector<int>>& graph) {
    int numVertices = graph.size();
    vector<int> colors(numVertices, 0);

    random_device rd;
    mt19937 gen(rd());

    for (int vertex = 0; vertex < numVertices; vertex++) {
        unordered_set<int> neighborColors;

        for (int neighbor : graph[vertex]) {
            if (colors[neighbor] != 0) {
                neighborColors.insert(colors[neighbor]);
            }
        }

        int currentColor = 1;
        while (neighborColors.count(currentColor) > 0) {
            currentColor++;
        }

        colors[vertex] = currentColor;
    }

    return colors;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    vector<vector<int>> graph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int source, target;
        cin >> source >> target;
        graph[source].push_back(target);
        graph[target].push_back(source);
    }

    vector<int> colors = colorGraph(graph);

    
    int maxColor = 0;
    for (int color : colors) {
        maxColor = max(maxColor, color);
    }

    cout << maxColor << endl;

    for (int color : colors) {
        cout << color << " ";
    }
    cout << endl;

    return 0;
}
