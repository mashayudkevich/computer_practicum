#include "reader.hpp"

using namespace tsp;

Reader::Reader() : _currVertexId(0) {}

void Reader::read_data(std::string filepath, std::unordered_map<VertexId, Vertex> &verList) {
    std::string curr_line;
    std::ifstream in(filepath);
    
    // разделитель - пробел
    const char delimeter = ' ';

    if ( in.is_open() ) {
        std::getline(in, curr_line);
        while ( std::getline(in, curr_line) ) {
            std::stringstream ss(curr_line);
            std::string x_str;
            std::string y_str;

            // разделяем строку по пробелу
            getline(ss, x_str, delimeter);
            double x = std::stod(x_str);

            getline(ss, y_str, delimeter);
            double y = std::stod(y_str);

            verList[_currVertexId] = std::make_pair(x, y);
            _currVertexId++;
        }
    }
    in.close();
}