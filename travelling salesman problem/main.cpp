#include <math.h>
#include <time.h>

#include "reader.hpp"
#include "matrix.hpp"
#include "little.hpp"

using tsp::Reader;
using tsp::Matrix;
using tsp::LittleSolver;
using tsp::VertexId;
using tsp::Vertex;

double distance(Vertex &v1, Vertex &v2) {
    double x1 = v1.first,
           x2 = v2.first,
           y1 = v1.second,
           y2 = v2.second;
    return sqrt( (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) );
}

void fill_matrix(Matrix<double> &matrix, std::unordered_map<VertexId, Vertex> &vers) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            matrix.item(i,j) = distance( vers.at(i), vers.at(j) );
        }
    }
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "");

    Reader reader{};
    std::unordered_map<VertexId, Vertex> vers;
    double num_vertex;
    double opt_len;

    // считывание данных
    if (argc < 2) {
        std::cout << "Введите путь к файлу, содержащему данные" << std::endl;
        return 1;
    } else {
        reader.read_data(argv[1], vers);
    }

    Matrix<double> matrix{vers.size(), 0};
    fill_matrix(matrix, vers);

    LittleSolver solver{matrix};

    time_t start_time;
    time_t end_time;
    time( &start_time );

    solver.solve();

    time( &end_time );

    
    std::cout << "Record: " << solver.getRecord() << std::endl;
    for ( auto verId : solver.getSolution() )
        std::cout << verId << " ";
    std::cout << std::endl;
    std::cout << "Время работы алгритма в секундах: " << end_time - start_time << std::endl;

    return 1;
}