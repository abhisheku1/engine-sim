#include "../include/matrix.h"

#include <assert.h>

Matrix::Matrix() {
    m_matrix = nullptr;
    m_width = 0;
    m_height = 0;
}

Matrix::Matrix(int width, int height, double value) {
    m_matrix = nullptr;

    initialize(width, height, value);
}

Matrix::~Matrix() {
    destroy();
}

void Matrix::initialize(int width, int height, double value) {
    destroy();

    m_height = height;
    m_width = width;

    m_matrix = new double *[height];
    for (int i = 0; i < height; ++i) {
        m_matrix[i] = new double[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            m_matrix[i][j] = value;
        }
    }
}

void Matrix::destroy() {
    if (m_matrix == nullptr) {
        return;
    }

    for (int i = 0; i < m_height; ++i) {
        delete[] m_matrix[i];
    }

    delete[] m_matrix;
}

void Matrix::set(int column, int row, double value) {
    m_matrix[row][column] = value;
}

double Matrix::get(int column, int row) {
    return m_matrix[row][column];
}

void Matrix::multiply(Matrix &b, Matrix *target) {
    assert(m_width == b.m_height);
    assert(target->m_width == b.m_width);
    assert(target->m_height == m_height);

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < b.m_width; ++j) {
            double v = 0.0f;
            for (int ii = 0; ii < m_width; ++ii) {
                v += m_matrix[i][ii] * b.m_matrix[ii][j];
            }

            target->m_matrix[i][j] = v;
        }
    }
}

void Matrix::subtract(Matrix &b, Matrix *target) {
    assert(b.m_width == m_width);
    assert(b.m_height = m_height);
    assert(target->m_width == m_width);
    assert(target->m_height == m_height);

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            target->m_matrix[i][j] = m_matrix[i][j] - b.m_matrix[i][j];
        }
    }
}

void Matrix::negate(Matrix *target) {
    assert(target->m_width == m_width);
    assert(target->m_height == m_height);

    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            target->m_matrix[i][j] = -m_matrix[i][j];
        }
    }
}

void Matrix::transpose(Matrix *target) {
    assert(target->m_width == m_height);
    assert(target->m_height == m_width);

    for (int i = 0; i < m_width; ++i) {
        for (int j = 0; j < m_height; ++j) {
            target->m_matrix[i][j] = m_matrix[j][i];
        }
    }
}