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

        std::string curr_line;
        std::fstream in("tests_data");
        char delimeter = ' ';
        std::unordered_map<std::string, double> tests_list;
        
        if (in.is_open()) {
            while ( std::getline(in, curr_line) ) {
                std::stringstream ss(curr_line);
                std::string filename;
                std::string opt_len_str;

                // разделяем строку по пробелу
                getline(ss, filename, delimeter);
                getline(ss, opt_len_str, delimeter);
                double opt_len = std::stod(opt_len_str);

                tests_list[filename] = opt_len;
            }
        }
        in.close();

        // число корректных решений
        int num_correct = 0;
        // общее число тестов
        int num_total = tests_list.size();
        // список примеров, на которых выдает неправильный ответ
        std::vector<std::string> uncorr_list;

        for (auto [filename, opt_len] : tests_list) {
            Reader reader{};
            std::unordered_map<VertexId, Vertex> vers;

            std::string filepath = "data/" + filename;
            std::cout << filepath << std::endl;
            reader.read_data(filepath, vers);

            Matrix<double> matrix{vers.size(), 0};
            fill_matrix(matrix, vers); 

            LittleSolver solver{matrix};

            time_t start_time;
            time_t end_time;
            time( &start_time );
            
            solver.solve();
            
            time( &end_time );

            std::cout << "Рекорд: " << solver.getRecord() << std::endl;
            std::cout << "Решение: ";
            for ( auto verId : solver.getSolution() )
                std::cout << verId << " ";

            std::cout << std::endl;
            std::cout << "Время работы алгритма в секундах: " << end_time - start_time << std::endl;

            std::cout << std::endl << std::endl;

            if (solver.getRecord() == opt_len) {
                num_correct++;
            } else {
                uncorr_list.push_back(filename);
            }
        }
        std::cout << "Процент правильных ответов: " << num_correct / num_total * 100 << std::endl;

        return 1;
    }