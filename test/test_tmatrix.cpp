#include "tmatrix.h"


#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;
    TDynamicMatrix<int> matrix2(matrix1);
    EXPECT_EQ(matrix1, matrix2);
    
}


TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;
    TDynamicMatrix<int> matrix2(matrix1);
    TDynamicMatrix<int>* p1 = &matrix1;
    TDynamicMatrix<int>* p2 = &matrix2;
    EXPECT_NE(p1, p2);

}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> matrix(10);
    EXPECT_EQ(matrix.size(), 10);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix(2);
    matrix[0] = v1;
    matrix[1] = v2;
    EXPECT_EQ(v1, matrix[0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix(2);
    matrix[0] = v1;
    matrix[1] = v2;
    ASSERT_ANY_THROW(matrix.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix(2);
    matrix[0] = v1;
    matrix[1] = v2;
    ASSERT_ANY_THROW(matrix.at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    int arr1[2] { 1, 2 };
    int arr2[2] { 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix(2);
    matrix[0] = v1;
    matrix[1] = v2;
    EXPECT_EQ(matrix, matrix);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    TDynamicMatrix<int> matrix2(2);
    matrix2 = matrix1;
    EXPECT_EQ(matrix1, matrix2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;


    int arr3[3]{ 1, 2, 3 };
    int arr4[3]{ 4, 5, 6 };
    int arr5[3]{ 7, 8, 9 };
    TDynamicVector<int> v3(arr3, 3);
    TDynamicVector<int> v4(arr4, 3);
    TDynamicVector<int> v5(arr5, 3);
    TDynamicMatrix<int> matrix2(2);
    matrix2[0] = v3;
    matrix2[1] = v4;
    matrix2[2] = v5;

    matrix1 = matrix2;

    EXPECT_EQ(matrix1.size(), matrix2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;


    int arr3[3]{ 1, 2, 3 };
    int arr4[3]{ 4, 5, 6 };
    int arr5[3]{ 7, 8, 9 };
    TDynamicVector<int> v3(arr3, 3);
    TDynamicVector<int> v4(arr4, 3);
    TDynamicVector<int> v5(arr5, 3);
    TDynamicMatrix<int> matrix2(2);
    matrix2[0] = v3;
    matrix2[1] = v4;
    matrix2[2] = v5;

    matrix1 = matrix2;

    EXPECT_EQ(matrix1, matrix2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;
    TDynamicMatrix<int> matrix2(matrix1);
    EXPECT_EQ(matrix1 == matrix2, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix(2);
    matrix[0] = v1;
    matrix[1] = v2;

    EXPECT_EQ(matrix == matrix, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;


    int arr3[3]{ 1, 2, 3 };
    int arr4[3]{ 4, 5, 6 };
    int arr5[3]{ 7, 8, 9 };
    TDynamicVector<int> v3(arr3, 3);
    TDynamicVector<int> v4(arr4, 3);
    TDynamicVector<int> v5(arr5, 3);
    TDynamicMatrix<int> matrix2(2);
    matrix2[0] = v3;
    matrix2[1] = v4;
    matrix2[2] = v5;

    EXPECT_EQ(matrix1 == matrix2, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;

    int arr3[2]{ 4, 3 };
    int arr4[2]{ 2, 1 };
    TDynamicVector<int> v3(arr3, 2);
    TDynamicVector<int> v4(arr4, 2);
    TDynamicMatrix<int> matrix2(2);
    matrix2[0] = v3;
    matrix2[1] = v4;

    TDynamicMatrix<int> matrix(2);
    matrix = matrix1 + matrix2;

    int arr5[2]{ 5, 5 };
    int arr6[2]{ 5, 5 };
    TDynamicVector<int> v5(arr5, 2);
    TDynamicVector<int> v6(arr6, 2);
    TDynamicMatrix<int> matrix3(2);
    matrix3[0] = v5;
    matrix3[1] = v6;

    EXPECT_EQ(matrix3, matrix);

}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;

    int arr3[3]{ 4, 3, 4 };
    int arr4[3]{ 2, 1, 2 };
    int arr5[3]{ 1, 1, 6 };
    TDynamicVector<int> v3(arr3, 3);
    TDynamicVector<int> v4(arr4, 3);
    TDynamicVector<int> v5(arr5, 3);
    TDynamicMatrix<int> matrix2(3);
    matrix2[0] = v3;
    matrix2[1] = v4;
    matrix2[2] = v5;

    ASSERT_ANY_THROW(matrix1 + matrix2);
}


TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;

    int arr3[2]{ 4, 3 };
    int arr4[2]{ 2, 1 };
    TDynamicVector<int> v3(arr3, 2);
    TDynamicVector<int> v4(arr4, 2);
    TDynamicMatrix<int> matrix2(2);
    matrix2[0] = v3;
    matrix2[1] = v4;

    TDynamicMatrix<int> matrix(2);
    matrix = matrix1 - matrix2;

    int arr5[2]{ -3, -1 };
    int arr6[2]{ 1, 3 };
    TDynamicVector<int> v5(arr5, 2);
    TDynamicVector<int> v6(arr6, 2);
    TDynamicMatrix<int> matrix3(2);
    matrix3[0] = v5;
    matrix3[1] = v6;

    EXPECT_EQ(matrix3, matrix);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    int arr1[2]{ 1, 2 };
    int arr2[2]{ 3, 4 };
    TDynamicVector<int> v1(arr1, 2);
    TDynamicVector<int> v2(arr2, 2);
    TDynamicMatrix<int> matrix1(2);
    matrix1[0] = v1;
    matrix1[1] = v2;

    int arr3[3]{ 4, 3, 4 };
    int arr4[3]{ 2, 1, 2 };
    int arr5[3]{ 1, 1, 6 };
    TDynamicVector<int> v3(arr3, 3);
    TDynamicVector<int> v4(arr4, 3);
    TDynamicVector<int> v5(arr5, 3);
    TDynamicMatrix<int> matrix2(3);
    matrix2[0] = v3;
    matrix2[1] = v4;
    matrix2[2] = v5;

    ASSERT_ANY_THROW(matrix1 - matrix2);
}

