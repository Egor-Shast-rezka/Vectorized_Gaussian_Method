/*
    Egor Shastin st129457@student.spbu.ru
    
    
*/

#include "gaussian_method.h"


// ================== checkAnswerUser ==================

std::string checkAnswerUser(std::string call, std::vector<std::string> values) {
    
    std::cout << call;
    
    std::string AnswerUser;
    std::getline(std::cin, AnswerUser);
    
    while (AnswerUser.empty()) {
        
        std::cout << "Invalid input. Please try again.\n";
        std::cin.clear();
        
        std::cout << call;
        std::getline(std::cin, AnswerUser);
    }
    
    if (std::find(values.begin(), values.end(), AnswerUser) != values.end()) {
        
        AnswerUser += ".csv";
    }
    
    return AnswerUser;
}


// ================== read_CSV ==================

Eigen::MatrixXd Matrix_tools::read_CSV(const std::string& filename) {

    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: file " << filename << " unknown. Generate new random matrix 5x5.\n";
        return random_matrix(5);
    }
    
    std::string line;
    int row = 0;
    int column = 0;

    while (std::getline(file, line)) {
        row++;
        
        if (row == 1) {
            std::stringstream ss(line);
            std::string cell;
        
            while (std::getline(ss, cell, ',')) {
                column++;
            }
        }
    }
    
    file.clear();
    file.seekg(0);
    
    Eigen::MatrixXd result(row-1, column);
    int current_row = 0;
    
    while (std::getline(file, line)) {
    
        std::stringstream ss(line);
        std::string cell;

        if (current_row != 0) {
            
            int current_col = 0;
            while (std::getline(ss, cell, ',')) {
            
                result(current_row-1, current_col) = std::stod(cell);
                current_col++;
            }
        }
        current_row++;
    }
    
    return result;
}


// ================== truncate ==================

double Matrix_tools::truncate(double value, int decimals) {
    const double EPS = 0.000001;

    if (std::abs(value) < EPS) {
        value = 0.0;
    }

    double factor = std::pow(10.0, decimals);  
    value = std::round(value * factor) / factor;

    return value;
}


// ================== truth_form ==================

Eigen::MatrixXd Matrix_tools::truth_form(Eigen::MatrixXd& mat, int current_row, int current_col) {

    std::vector<Eigen::VectorXd> rows;
    
    for (int i = 0; i < mat.rows(); ++i) {
    
        rows.push_back(mat.row(i));
    }

    std::sort(rows.begin() + current_row, rows.end(), [current_col](const Eigen::VectorXd& a, const Eigen::VectorXd& b) {
            
            if (a(current_col) != 0 && b(current_col) != 0) {
            
                return a(current_col) < b(current_col);
                
            } else if (a(current_col) != 0) {
                
                return true;
            } else {
            
                return false;
            }
        });

    for (int i = 0; i < mat.rows(); ++i) {
    
        mat.row(i) = rows[i];
    }
    return mat;
}


// ================== method_gaus ==================

Eigen::MatrixXd Matrix_tools::method_gaus(Eigen::MatrixXd& matrix) {
    
    int current_col = 0;
    
    for (int current_row = 0; current_row < matrix.rows(); ++current_row) {
        
        truth_form(matrix, current_row, current_col);
        
        while (matrix(current_row, current_col) == 0) {

            current_col++;
            if (current_col == matrix.cols()-1) {
            
                return matrix;
            }
        }
        for (int current_row_2 = current_row+1; current_row_2 < matrix.rows(); ++current_row_2) {
            
            while (matrix(current_row_2, current_col) == 0) {
            
                current_col++;
                if (current_col == matrix.cols()-1) {
                
                    return matrix;
                }
            }
            
            double num = matrix(current_row_2, current_col) / matrix(current_row, current_col);
            for (int current_col_2 = current_col; current_col_2 < matrix.cols(); ++current_col_2) {
            
                matrix(current_row_2, current_col_2) = truncate(matrix(current_row_2, current_col_2) - num * matrix(current_row, current_col_2), 1);
            }

        }
        current_col++;
    }
    
    return matrix;
}


// ================== random_double ==================

double Matrix_tools::random_double(bool onlyPositive) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);

    double r = dis(gen);

    if (onlyPositive && r < 0) {
        r = -r;
    }

    if (!onlyPositive && r > 0) {
        r = -r;
    }

    return truncate(r, 1);
}


// ================== random_matrix ==================

Eigen::MatrixXd Matrix_tools::random_matrix(int size) {

    Eigen::MatrixXd matrix(size, size);

    bool onlyPositive = true;

    for (int i = 0; i < matrix.rows(); ++i) {
    
        for (int j = 0; j < matrix.cols(); ++j) {
        
            matrix(i, j) = random_double(onlyPositive);
        }
    }

    return matrix;
}


// ================== write_CSV ==================

void Matrix_tools::write_CSV(const Eigen::MatrixXd& matrix, const std::string& filename) {

    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error: file unknown" << std::endl;
        return;
    }

    for (int i = 0; i < matrix.rows(); ++i) {
    
        for (int j = 0; j < matrix.cols(); ++j) {
        
            outFile << matrix(i, j) << "\t";
        }
        outFile << "\n";
    }

    outFile.close();
}

