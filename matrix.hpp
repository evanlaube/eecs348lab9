#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstddef>
#include <vector>
#include <iostream>

// all of your function definitions should be in this file now

template <typename T>
class Matrix {
public:
    Matrix<T>(std::size_t N) {
        // initialize an empty NxN matrix
        data = std::vector<T>(N*N);
        // Set size to N
        size = N;
    }
    Matrix<T>(std::vector<std::vector<T>> nums) {
        // Set size to the number of rows/cols
        size = nums.size();
        // Allocate space for data
        data = std::vector<int>(size*size);

        // Store all data as a 1d array, where elements can be indexed with the formula:
        //      index = (row*size) + col
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                data[i*size+j] = nums[i][j];
            }
        }
    }

    Matrix<T> operator+(const Matrix &rhs) const {
        // Make sure that the matrices have the same size
        if(size != rhs.size) {
            throw std::runtime_error("Attempted to add matrices of different sizes");
        }
        // Create a result matrix of the same size
        Matrix<T> result(size);
        for(int i = 0; i < size; i++) {
            for(int n = 0; n < size; n++) {
                // For each element in the result, set it equal to that position in a and b
                result.data[i*size + n] = data[i*size+n] + rhs.data[i*size+n];
            }
        }

        // Return the result matrix
        return result;
    }

    Matrix<T> operator*(const Matrix &rhs) const {
        // Make sure that the matrices are the same size
        if(size != rhs.size) {
            throw std::runtime_error("Attempted to multiply matrices of different sizes");
        }

        // Create a result matrix of the same size
        Matrix<T> result(size);

        // O(n^3) algorithm to calculate the result of multiplication
        for(int row = 0; row < size; row++) {
            for(int col = 0; col < size; col++) {
                for(int k = 0; k < size; k++) {
                    // For each element, sum the row of the lhs(this) multiplied by the col of the rhs
                    result.data[row*size + col] += data[row * size + k] * rhs.data[k * size + col];
                }
            }
        }

        // Return result matrix
        return result;
    }

    void set_value(std::size_t i, std::size_t j, T n) {
        // Make sure that the row and column index are in bounds
        if(i >= (std::size_t)size || j >= (std::size_t)size) {
            throw std::out_of_range("Attempted to set matrix cell out of bounds");
        }

        // Set the entry at index row*size+col to the input data
        data[i*size+j] = n;
    }

    T get_value(std::size_t i, std::size_t j) const {
        // Make sure that the row and column index are in bounds
        if(i >= size || j >= size) {
            throw std::out_of_range("Attempted to get matrix cell out of bounds");
        }

        // Return the entry at index row*size+col
        return data[i*size+j];
    }

    int get_size() const {
        return size;
    }

    T sum_diagonal_major() const {
        // Start sum at zero
        T sum = 0;
        // Loop through all points where row index = col index
        for(int i = 0; i < size; i++) {
            // Add the entry at the position to sum
            sum += data[i*size + i];
        }
        // Return the final sum
        return sum;
    }

    T sum_diagonal_minor() const {
        // Start sum at zero
        T sum = 0;
        // Loop through all points from top right of matrix to bottom left
        for(int i = 0; i < size; i++) {
            // Add each entry to sum
            sum += data[i*size + (size-1-i)];
        }
        return sum;
    }

    void swap_rows(std::size_t r1, std::size_t r2) {
        // Loop size times
        for(int i = 0; i < size; i++) {
            // Store entry in col i, r1 into temp
            T temp = data[r1*size + i];
            // Set the entry in r1 to the entry in r2
            data[r1*size+i] = data[r2*size+i];
            // Set the entry in r2 to temp
            data[r2*size+i] = temp;
        }
    }

    void swap_cols(std::size_t c1, std::size_t c2) {
        // Loop size times
        for(int i =0; i < size; i++) {
            // Store entry in row i, c1 into temp
            T temp = data[i*size + c1];
            // Set the entry in c1 to the entry in c2
            data[i*size+c1] = data[i*size+c2];
            // Set the entry in c2 to temp
            data[i*size+c2] = temp;
        }
    }
    void print_matrix() const {
        // Get largest number of digits of number in matrix
        // int maxDigits = 0;
        // // Loop through each entry in the matrix
        // for(int i = 0; i < size*size; i++) {
        //     // Get the number at position i
        //     int number = data[i];
        //     // If the number is negative, make it positive
        //     if(number < 0) {
        //         number = -number;
        //     }
        //     // Start the number of digits at zero
        //     int digits = 0;
        //     // Calculate the number of digits in the number by repetitively diving by 10
        //     if(number == 0) {
        //         digits = 0;
        //     } else {
        //         while (number != 0) {
        //             number /= 10;
        //             digits++;
        //         }
        //     }

        //     // Set maxDigits to the max of digits and itself
        //     maxDigits = std::max(digits, maxDigits);
        // }

        // Print each entry in the matrix
        for(int i = 0; i < size; i++) {
            for(int n = 0; n < size; n++) {
                // Format to print each number the same width
                //std::cout << std::setw(maxDigits) << std::setfill('0') << data[size*i + n] << " ";
                std::cout << data[size*i + n] << " ";
            }
            std::cout << std::endl;
        }
    }
private:
    std::vector<T> data;
    int size;
};

#endif // __MATRIX_HPP__
