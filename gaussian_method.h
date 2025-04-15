/*
    Egor Shastin st129457@student.spbu.ru
    
    > Is the header file that declares the Matrix_tools class and its interface. 
    > It is used to declare all auxiliary methods necessary for working with matrices, 
    reading/writing files, and solving a system of equations using the Gauss method.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <Eigen/Dense>


#ifndef GAUSSIAN_METHOD_H
#define GAUSSIAN_METHOD_H


// ================== checkAnswerUser ==================

std::string checkAnswerUser(std::string call, std::vector<std::string> values);


// ================== Matrix_tools ==================

class Matrix_tools {
private:

    double truncate(double value, int decimals);
    
    Eigen::MatrixXd truth_form(Eigen::MatrixXd& mat, int current_row, int current_col);
    
    double random_double(bool onlyPositive);
    
public:
    
    Eigen::MatrixXd random_matrix(int size);
    
    Eigen::MatrixXd read_CSV(const std::string& filename);

    Eigen::MatrixXd method_gaus(Eigen::MatrixXd& matrix);
    
    void write_CSV(const Eigen::MatrixXd& matrix, const std::string& filename);
};


#endif
