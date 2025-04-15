/*
    Egor Shastin st129457@student.spbu.ru
    
    > A file with unit tests based on Google Test. 
    > Checks the correctness of various operations related to matrix processing: 
    reading, writing, transformations, and generation.
*/

#include "gaussian_method.h"
#include <gtest/gtest.h>
#include <fstream>


// ================== create_test_csv ==================

void create_test_csv(const std::string& filename, const std::vector<std::vector<double>>& data) {

    std::ofstream file(filename);
    
    for (const auto& row : data) {
    
        for (size_t i = 0; i < row.size(); ++i) {
        
            file << row[i];
            if (i != row.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}


// ================== check_big_matrix ==================

bool check_big_matrix(Eigen::MatrixXd& matrix) {
    
    for (int i = 1; i < matrix.rows(); ++i) {
        if (matrix(i, 0) != 0) return false;
    }

    for (int j = 0; j < matrix.cols() - 1; ++j) {
        if (matrix(matrix.rows() - 1, j) != 0) return false;
    }
    return true;
}

// ================== ReadCSV Test ==================

TEST(MatrixToolsTest, ReadCSV) {
    
    Matrix_tools matrix;
    std::string filename = "test_read.csv";
    
    create_test_csv(filename, {
        {1.0, 2.0, -1.0, 8.0},
        {2.0, -3.0, 1.0, -11.0},
        {-1.0, 2.0, 4.0, -3.0}
    });

    Eigen::MatrixXd mat = matrix.read_CSV(filename);
    ASSERT_EQ(mat.rows(), 2);
    ASSERT_EQ(mat.cols(), 4);
    EXPECT_DOUBLE_EQ(mat(0,0), 2.0);
    EXPECT_DOUBLE_EQ(mat(1,3), -3.0);
}


// ================== RandomMatrix Test ==================

TEST(MatrixToolsTest, RandomMatrix) {

    Matrix_tools matrix;
    
    Eigen::MatrixXd mat = matrix.random_matrix(5);
    ASSERT_EQ(mat.rows(), 5);
    ASSERT_EQ(mat.cols(), 5);
}


// ================== MethodGausSimple Test ==================

TEST(MatrixToolsTest, MethodGausSimple) {
    
    Matrix_tools matrix;
    
    Eigen::MatrixXd A(3, 4);
    A << 1, 2, -1, 8,
         2, -3, 1, -11,
        -1, 2, 4, -3;

    Eigen::MatrixXd result = matrix.method_gaus(A);

    EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result(2, 0), 0.0);
}

// ================== WriteCSV Test ==================

TEST(MatrixToolsTest, WriteCSV) {

    Matrix_tools matrix;
    
    Eigen::MatrixXd mat(2, 2);
    mat << 1.1, 2.2,
           3.3, 4.4;

    std::string filename = "test_write.csv";
    matrix.write_CSV(mat, filename);

    std::ifstream file(filename);
    ASSERT_TRUE(file.is_open());

    std::string line;
    std::getline(file, line);
    ASSERT_NE(line.find("1.1"), std::string::npos);
    file.close();
}


// ================== Test With Big Matrix ==================

TEST(MatrixToolsTest, TestWithBigMatrix) {
    
    Matrix_tools Matrix_tools;
    
    std::random_device rd;
    
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(20, 100);      
    
    for (int i = 0; i < 40; ++i) {
    
        Eigen::MatrixXd matrix = Matrix_tools.random_matrix(dis(gen));
        Matrix_tools.method_gaus(matrix);
        
        EXPECT_TRUE(check_big_matrix(matrix));
        if (!check_big_matrix(matrix)) break;
        if (i % 10 == 0) std::cout << "10 random Matrix cheked.\n";
    }
}


// ================== main ==================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
