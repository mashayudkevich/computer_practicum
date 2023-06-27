#include <iostream>
#include <vector>
#include <limits>

struct Point {
    double x;
    double y;}

void solveTransportProblem(int N, int V, double c, std::vector<double>& distances, std::vector<Point>& points) {
    std::vector<std::vector<double>> plan(N, std::vector<double>(V, 0.0));

    std::vector<double> supply(N, 0.0);
    std::vector<double> demand(V, 0.0);

    for (int i = 0; i < N; i++) {
        supply[i] = points[i].x;
    }

    for (int j = 0; j < V; j++) {
        demand[j] = points[j].y;
    }

    double totalCost = 0.0;

    while (true) {
        
        int maxCostIndex = -1;
        double maxCost = std::numeric_limits<double>::min();

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < V; j++) {
                if (plan[i][j] == 0.0) {
                    double cost = distances[i * V + j];
                    if (cost > maxCost) {
                        maxCost = cost;
                        maxCostIndex = i * V + j;
                    }
                }
            }
        }

        
        if (maxCostIndex == -1)
            break;

        int row = maxCostIndex / V;
        int col = maxCostIndex % V;

        
        double quantity = std::min(supply[row], demand[col]);
        if (quantity > 0.0) {
            plan[row][col] = quantity;
            supply[row] -= quantity;
            demand[col] -= quantity;
            totalCost += quantity * distances[row * V + col];
        }
        else {
            plan[row][col] = 0.0;  
        }
    }

    
    std::cout << totalCost << std::endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < V; j++) {
            std::cout << plan[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int N, V;
    double c;
    std::cin >> N >> V >> c;

    std::vector<double> distances(N * V);
    std::vector<Point> points(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < V; j++) {
            std::cin >> distances[i * V + j];
        }
    }

    for (int i = 0; i < N; i++) {
        std::cin >> points[i].x;
        std::cin >> points[i].y;
    }

    solveTransportProblem(N, V, c, distances, points);

    return 0;}
