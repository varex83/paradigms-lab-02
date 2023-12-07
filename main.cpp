#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

struct Point {
    double x, y;
};

struct AffineTransformation {
    double matrix[2][2];
    Point vector;

    Point apply(const Point& p) const {
        return {matrix[0][0] * p.x + matrix[0][1] * p.y + vector.x,
                matrix[1][0] * p.x + matrix[1][1] * p.y + vector.y};
    }
};

class AffineTransformations {
    vector<AffineTransformation> transformations;
    mt19937 rng;

public:
    AffineTransformations() : rng(random_device{}()) {}

    void addTransformation(const AffineTransformation& t) {
        transformations.push_back(t);
    }

    Point applyRandom(const Point& p) {
        uniform_int_distribution<int> dist(0, transformations.size() - 1);
        return transformations[dist(rng)].apply(p);
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    Point start;
    // number of points, start.x, start.y
    cin >> n >> start.x >> start.y;

    AffineTransformations affTrans;
    AffineTransformation t;

    // Affine(x) = M * x + v
    // M[0][0], M[0][1], M[1][0], M[1][1], v.x, v.y
    while (cin >> t.matrix[0][0] >> t.matrix[0][1] >> t.matrix[1][0] >> t.matrix[1][1] >> t.vector.x >> t.vector.y) {
        affTrans.addTransformation(t);
    }

    Point current = start;
    for (int i = 0; i < n; ++i) {
        cout << fixed << setprecision(8) << current.x << " " << current.y << endl;
        current = affTrans.applyRandom(current);
    }

    return 0;
}
