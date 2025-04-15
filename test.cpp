/*
    Egor Shastin st129457@student.spbu.ru
    
    This is code for unit testing all classes by using Google Test
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


// ================== main ==================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
