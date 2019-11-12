// Michal Welna 302935
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <functional>
#include <climits>
#include "salesman.hpp"


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

double get_forbidden_cost(){return INF;}


std::tuple<int,int> find_i_jNANS (std::vector<std::tuple<int,int>> &buff){
    int tmp,tmp2;
    auto p = std::get<0>(buff[0]);
    for(int i = 1; i<buff.size(); i++){
        if(p==std::get<0>(buff[i])){
            tmp = std::get<0>(buff[i+1]);
            break;
        }
        else if(i){tmp = p; break;}
    }

    auto w = std::get<1>(buff[0]);
    for(int i = 1; i<buff.size(); i++){
        if(w==std::get<1>(buff[i])){
            tmp2 = std::get<1>(buff[i+1]);
            break;
        }
        else if(w==std::get<1>(buff[i+1])){
            tmp2 = std::get<1>(buff[i]);
            break;
        }
        else {tmp2 = w;}
    }
    return std::make_tuple(tmp,tmp2);
}

std::vector<std::tuple<int,int>> find_last_two_points(std::vector<std::vector<double>> &mtrx){
    std::vector<std::tuple<int,int>> buff,vec;
    int w,k;
    for(int i=0; i<mtrx.size(); i++){
        for(int j=0; j<mtrx[i].size(); j++){
            if(mtrx[i][j]==0){
                buff.push_back(std::make_tuple(i+1,j+1));
            }
        }
    }
    if(buff.size()==2){return buff;}
    else {

        buff.push_back(find_i_jNANS(buff));
        w = std::get<0>(buff.back());
        k = std::get<1>(buff.back());
        for (int i = 0; i < buff.size() - 1; i++) {
            if (std::get<0>(buff[i]) == w) {
                vec.push_back(buff[i]);
            } else if (std::get<1>(buff[i]) == k) {
                vec.push_back(buff[i]);
            }

        }
    }
    return vec;
}

std::tuple<int,int> findMaxValue_in_map(std::map<std::pair<int,int>,double> &mp){
    double current_max = 0;
    std::tuple<int,int> argMax = std::make_tuple(0,0);
    for(auto it = mp.begin(); it!=mp.end(); it++){
        if(it->second > current_max){
            argMax = std::make_tuple(it->first.first,it->first.second);
            current_max = it->second;

        }
    }
    return argMax;
}

std::vector<std::vector<double>> reduce_rows_cols(std::vector<std::vector<double>> &mtrx, std::tuple<int,int> &tpl){
    for(int j=0; j< mtrx[std::get<0>(tpl)-1].size(); j++){
        mtrx[std::get<0>(tpl)-1][j] = INF;
    }
    for(int i =0; i<mtrx.size();i++){
        mtrx[i][std::get<1>(tpl)-1] = INF;
    }
    mtrx[std::get<1>(tpl)-1][std::get<0>(tpl)-1] = INF;
    return mtrx;
}

double reduce(std::vector<std::vector<double>>& mtrx, double ss){

    std::vector<double> vec1,vec2,vec_help,vec_sum,vec_help1;
    double lower_bound = 0;

    for(int i=0; i<mtrx.size();i++){
        for (int j=0; j<mtrx[i].size(); j++){
            vec_help1.push_back(mtrx[i][j]);
        }
        vec_help1.erase(std::remove_if(std::begin(vec_help1),std::end(vec_help1), [](const auto& value) {return std::isnan(value);}),std::end(vec_help1));
        vec1.push_back(*std::min_element(vec_help1.begin(),vec_help1.end()));
        vec_help1.clear();
    }


    for(int i=0; i<mtrx.size();i++){
        for(int j=0; j<mtrx[i].size();j++){
            mtrx[i][j] -= vec1[i];
        }
    }

    for(int j=0; j<mtrx[0].size();j++){
        for(int i=0; i<mtrx.size();i++){
            if (mtrx[i][j]==0) {vec_help.push_back(0); continue;}
            else{
                vec_help.push_back(mtrx[i][j]);
            }
        }
        vec_help.erase(std::remove_if(std::begin(vec_help),std::end(vec_help), [](const auto& value) {return std::isnan(value);}),std::end(vec_help));
        vec2.push_back(*std::min_element(vec_help.begin(),vec_help.end()));
        vec_help.clear();
    }


    for(int j=0; j<mtrx[0].size();j++){
        for(int i=0; i<mtrx.size();i++){
            mtrx[i][j] -= vec2[j];
        }
    }


    vec1.erase(std::remove_if(std::begin(vec1),std::end(vec1), [](const auto& value) {return std::isnan(value);}),std::end(vec1));
    vec2.erase(std::remove_if(std::begin(vec2),std::end(vec2), [](const auto& value) {return std::isnan(value);}),std::end(vec2));


     for(std::vector<double>::iterator it = vec1.begin(); it!= vec1.end(); it++){
         lower_bound += *it;
     }
     for(std::vector<double>::iterator it = vec2.begin(); it!= vec2.end(); it++){
        lower_bound += *it;
     }
    return lower_bound + ss;
}

std::tuple<int,int> check_paths_and_choose_tuple(std::vector<std::vector<double>> &mtrx){

    std::vector<double> vec1,vec2;
    std::map<std::pair<int,int>,double> tmp;
    std::vector<std::tuple<int,int>> path;
    std::tuple<int,int> pas;

    double buff1,buff2;
    for (int i=0; i<mtrx.size();i++){
        for(int j=0; j<mtrx[i].size();j++) {
            if (mtrx[i][j] == 0) {
                for (int k = 0; k < mtrx[i].size(); k++) {
                    vec1.push_back(mtrx[i][k]);
                }
                vec1.erase(vec1.begin() + j);
                vec1.erase(std::remove_if(std::begin(vec1),std::end(vec1), [](const auto& value) {return std::isnan(value);}),std::end(vec1));
                buff1 = *std::min_element(vec1.begin(),vec1.end());
                for(int l =0; l<mtrx.size(); l++){
                    vec2.push_back(mtrx[l][j]);
                }
                vec2.erase(vec2.begin()+ i);
                vec2.erase(std::remove_if(std::begin(vec2),std::end(vec2), [](const auto& value) {return std::isnan(value);}),std::end(vec2));
                buff2 = *std::min_element(vec2.begin(),vec2.end());
                auto pair = std::make_pair(i+1,j+1);
                tmp[pair] = buff1+buff2;
            }
            vec1.clear();
            vec2.clear();
        }
    }


    pas = findMaxValue_in_map(tmp);
    reduce_rows_cols(mtrx,pas);


    return pas;
}

std::vector<int> sort_tuples_and_give_result(std::vector<std::tuple<int,int>> &vec){
    std::vector<std::tuple<int,int>> sorted_vec;
    std::tuple<int,int> buff;
    std::vector<int> vec_results;


    for(int i=0; i<vec.size(); i++){
        if(i==0){
            sorted_vec.push_back(vec[i]);
        }
        buff = sorted_vec[i];
        for(int j=0; j<vec.size();j++){
            if(std::get<1>(buff)==std::get<0>(vec[j])){
                sorted_vec.push_back(vec[j]);
                break;

            }
        }
    }

    for(int i=0; i<sorted_vec.size(); i++){
        vec_results.push_back(std::get<0>(sorted_vec[i]));
    }
    return vec_results;
}

std::vector<int> tsp(std::vector<std::vector<double>> &cost_matrix){
    int i = 1;
    double LB = 0;
    std::vector<int> result1;
    std::vector<std::tuple<int,int>> result;
    while(i<cost_matrix.size()){
        LB += -(LB - reduce(cost_matrix,LB));
        if(i==cost_matrix.size()-1){
            auto vec_ntb_added = find_last_two_points(cost_matrix);
            result.insert(result.end(), vec_ntb_added.begin(), vec_ntb_added.end());
            result1 = sort_tuples_and_give_result(result);
        }else {
            auto tp1 = check_paths_and_choose_tuple(cost_matrix);
            result.push_back(tp1);
        }
        i++;
    }
    std::cout<<"Lower_Bound: "<<LB<<std::endl;

    return result1;
}




int main(){
    std::vector<int> vec;
    vec = tsp(mat3);
    for (auto e : vec){
        std::cout<< e <<' ';
    }
}
