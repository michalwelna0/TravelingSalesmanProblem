// Michal Welna 302935
#ifndef CPPSEM3_SALESMAN_HPP
#define CPPSEM3_SALESMAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <functional>
#include <climits>

#define INF (NAN) //integer infinity

std::vector<int> tsp(std::vector<std::vector<double>> &cost_matrix);
std::vector<int> sort_tuples_and_give_result(std::vector<std::tuple<int,int>> &vec);
std::tuple<int,int> check_paths_and_choose_tuple(std::vector<std::vector<double>> &mtrx);
double reduce(std::vector<std::vector<double>>& mtrx, double ss);
std::vector<std::vector<double>> reduce_rows_cols(std::vector<std::vector<double>> &mtrx, std::tuple<int,int> &tpl);
std::tuple<int,int> findMaxValue_in_map(std::map<std::pair<int,int>,double> &mp);
std::vector<std::tuple<int,int>> find_last_two_points(std::vector<std::vector<double>> &mtrx);
std::tuple<int,int> find_i_jNANS (std::vector<std::tuple<int,int>> &buff);
double get_forbidden_cost();

std::vector<std::vector<double>> cost_matrix {
        { INF , 10 , 8 , 19 , 12} ,
        {10 , INF , 20 , 6, 3} ,
        {8 , 20 , INF , 4 , 2} ,
        {19 , 6 , 4 , INF , 7} ,
        {12 , 3 , 2 , 7 , INF }
};

std::vector<std::vector<double>> mat1 {
        {INF, 12,   3,  45,   6},
        {78, INF,  90,  21,   3},
        { 5,  56, INF,  23,  98},
        {12,   6,   8, INF,  34},
        { 3,  98,   3,   2, INF}
};

std::vector<std::vector<double>> mat2 {
        {INF,  3.0,  4.0,  2.0,  7.0},
        {3.0,  INF,  4.0,  6.0,  3.0},
        {4.0,  4.0,  INF,  5.0,  8.0},
        {2.0,  6.0,  5.0,  INF,  6.0},
        {7.0,  3.0,  8.0,  6.0,  INF},
};

std::vector<std::vector<double>> mat3 {
        {INF, 29, 82, 46, 68, 52, 72, 42, 51, 55, 29, 74, 23, 72, 46 },
        { 29, INF, 55, 46, 42, 43, 43, 23, 23, 31, 41, 51, 11, 52, 21},
        { 82, 55, INF, 68, 46, 55, 23, 43, 41, 29, 79, 21, 64, 31, 51},
        { 46, 46, 68, INF, 82, 15, 72, 31, 62, 42, 21, 51, 51, 43, 64},
        { 68, 42, 46, 82, INF, 74, 23, 52, 21, 46, 82, 58, 46, 65, 23},
        { 52, 43, 55, 15, 74, INF, 61, 23, 55, 31, 33, 37, 51, 29, 59},
        { 72, 43, 23, 72, 23, 61, INF, 42, 23, 31, 77, 37, 51, 46, 33},
        { 42, 23, 43, 31, 52, 23, 42, INF, 33, 15, 37, 33, 33, 31, 37},
        { 51, 23, 41, 62, 21, 55, 23, 33, INF, 29, 62, 46, 29, 51, 11},
        { 55, 31, 29, 42, 46, 31, 31, 15, 29, INF, 51, 21, 41, 23, 37},
        { 29, 41, 79, 21, 82, 33, 77, 37, 62, 51, INF, 65, 42, 59, 61},
        { 74, 51, 21, 51, 58, 37, 37, 33, 46, 21, 65, INF, 61, 11, 55},
        { 23, 11, 64, 51, 46, 51, 51, 33, 29, 41, 42, 61, INF, 62, 23},
        { 72, 52, 31, 43, 65, 29, 46, 31, 51, 23, 59, 11, 62, INF, 59},
        { 46, 21, 51, 64, 23, 59, 33, 37, 11, 37, 61, 55, 23, 59, INF}
};


#endif //CPPSEM3_SALESMAN_HPP


