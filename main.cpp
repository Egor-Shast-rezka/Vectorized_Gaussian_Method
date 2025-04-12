/*
    Egor Shastin st129457@student.spbu.ru
    
    
*/

#include "gaussian_method.h"


// ================== main ==================

int main() {

    Matrix_tools Matrix_tools;
    
    std::string fileName = checkAnswerUser("Write the file name (it should be in the format .csv): ", {".csv"});
    
    Eigen::MatrixXd matrix = Matrix_tools.read_CSV(fileName);
    
    Matrix_tools.method_gaus(matrix);
    
    std::string name_output_file = "output_matrix.csv";
    
    std::cout << "Output file was created. Its name " << name_output_file << "\n";
    
    Matrix_tools.write_CSV(matrix, name_output_file);
    
    return 0;
}
