#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

struct Point {
    double x;
    double y;}

double dist(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);}

vector<int> solveTSP(const vector<Point>& points) {
    int N = points.size();
    vector<bool> visited(N, false);
    vector<int> path;
    int current = 0;
    visited[current] = true;
    path.push_back(current);

    while (path.size() < N) {
        int next = -1;
        double minDist = numeric_limits<double>::max();

        for (int i = 0; i < N; ++i) {
            if (!visited[i]) {
                double dist = dist(points[current], points[i]);
                if (dist < minDist) {
                    minDist = dist;
                    next = i;
                }
            }
        }

        visited[next] = true;
        path.push_back(next);
        current = next; }

    return path;}

int main() {
    int N;
    cin >> N;

    vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    vector<int> path = solveTSP(points);

    double totalDist = 0.0;
    for (int i = 0; i < N; ++i) {
        int p1 = path[i];
        int p2 = path[(i + 1) % N];
        totalDist += dist(points[p1], points[p2]);
    }

    cout << "obj " << totalDist << endl;
    for (int i = 0; i < N; ++i) {
        cout << path[i] << " ";
    }
    cout << endl;

    return 0;}
