#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "matrix.hpp"

template <typename T>
Matrix<T> readMatrix(std::ifstream &inputFile, int size) {
    Matrix<T> matrix(size);
    std::string line;

    for(int i = 0; i < size; i++) {
        std::getline(inputFile, line);
        std::stringstream ss(line);
        T number;
        int n = 0;
        while(ss >> number) {
            matrix.set_value(i, n, number);
            n++;
        }
    }
    return matrix;
}

template <typename T>
void processMatrices(std::ifstream &inputFile, int size) {
        Matrix<T> a = readMatrix<T>(inputFile, size);
        Matrix<T> b = readMatrix<T>(inputFile, size);
        // Print Matrix A to user
        std::cout << "Matrix A:" << std::endl;
        a.print_matrix();
        std::cout << std::endl;

        // Print Matrix B to user
        std::cout << "Matrix B:" << std::endl;
        b.print_matrix();
        std::cout << std::endl;

        // Demo matrix addition
        std::cout << "Result of A + B: " << std::endl;
        (a+b).print_matrix();
        std::cout << std::endl;

        // Demo matrix multiplication
        std::cout << "Result of A * B: " << std::endl;
        (a*b).print_matrix();
        std::cout << std::endl;

        // Demo the major diagonal sums
        std::cout << "Sum of major diagonal elements in A: " << a.sum_diagonal_major() << std::endl;
        std::cout << "Sum of major diagonal elements in B: " << b.sum_diagonal_major() << std::endl;
        std::cout << std::endl;

        // Demo the minor diagonal sums
        std::cout << "Sum of minor diagonal elements in A: " << a.sum_diagonal_minor() << std::endl;
        std::cout << "Sum of minor diagonal elements in B: " << b.sum_diagonal_minor() << std::endl;
        std::cout << std::endl;

        if(size > 2) { // If the size of the matrices is more than 2
            // Demo the row swapping function by swapping row 2 and 3 of matrix A
            Matrix<T> cpy = a;
            cpy.swap_rows(1, 2);
            std::cout << "Result of swapping row 2 of Matrix A with row 3" << std::endl;
            cpy.print_matrix();
            std::cout << std::endl;
        }

        if(size > 3) { // If the size is more than 3
            // Demo the column swapping function by swapping column 3 and 4 of matrix B
            Matrix<T> cpy = b;
            cpy.swap_cols(2,3);
            std::cout << "Result of swapping col 3 of Matrix B with col 4" << std::endl;
            cpy.print_matrix();
            std::cout << std::endl;
        }
}

int main(int argc, char *argv[]) {
    // Prompt the user for an input file
    std::cout << "Enter name of file to process: ";
    // Create a string to store the filename
    std::string filename;
    // Take user input and store in filename
    std::cin >> filename;

    // Create an input file stream with the input file name
    std::ifstream inputFile(filename);

    // Make sure that the file exists
    if(inputFile.is_open()) {
        // Create a string to store each line
        std::string line;
        // Initialize the size of the matrices to zero
        int size = 0;
        int datatype = 0;

        inputFile >> size >> datatype;

        // Get next line after size
        std::getline(inputFile, line);

        // Skip all blank lines that may have been inserted
        while(line == "\n") {
            std::getline(inputFile, line);
        }

        if(datatype == 0) {
            processMatrices<int>(inputFile, size);
        } else if(datatype == 1) {
            processMatrices<double>(inputFile, size);
        } else {
            std::cerr << "Invalid datatype. Must be 0 or 1." << std::endl;
            return 1;
        }

    } else { // If the file is unable to be opened
        // Print an error to the user and return
        std::cerr << "Unable to open file. Make sure it exists and has valid permissions" << std::endl;
        return 1;
    }

    return 0;
}
