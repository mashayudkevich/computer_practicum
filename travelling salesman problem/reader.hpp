#pragma once

#include <iostream>
#include <fstream>
#include <string>
//#include <string.h>
#include <unordered_map>
#include <sstream>

#include "matrix.hpp"

namespace tsp {

    using Vertex = std::pair<double, double>;
    using VertexId = int;

    class Reader {
        public:
            Reader();

            // основной метод, считывает данные из файла filepath
            // возвращает значения в аргументах verList, num_vertex, opt_len
            void read_data(std::string filepath, std::unordered_map<VertexId, Vertex> &verList);

        private:
            // текущая считываемая вершина
            int _currVertexId;
    };
}