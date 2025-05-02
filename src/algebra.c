#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows!=b.rows || a.cols!=b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        Matrix c=create_matrix(0,0);
        return c;
    }
    else{
        Matrix c=create_matrix(a.rows,a.cols);
        for (int i=0;i<c.rows;i++) {
            for (int j=0;j<c.cols;j++) {
                c.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return c;    
    }
    
}
Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows!=b.rows || a.cols!=b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        Matrix c=create_matrix(0,0);
        return c;
    }
    else{
        Matrix c=create_matrix(a.rows,a.cols);
        for (int i=0;i<c.rows;i++) {
            for (int j=0;j<c.cols;j++) {
                c.data[i][j]=a.data[i][j]-b.data[i][j];
            }
        }
        return c;    
    }
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols!=b.rows) {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        Matrix c=create_matrix(0,0);
        return c;
    }
    else{
        Matrix c=create_matrix(a.rows,b.cols);
        for (int i=0;i<c.rows;i++) {
            for (int j=0;j<c.cols;j++) {
                double c_num=0.0;
                for (int k=0;k<a.cols;k++) {
                    c_num +=a.data[i][k]*b.data[k][j];
                }
            c.data[i][j] = c_num;
            }
        }
        return c;
    }
}
Matrix scale_matrix(Matrix a, double k)
{
    Matrix c=create_matrix(a.rows,a.cols);
    for (int i=0;i<c.rows;i++) {
        for (int j=0;j<c.cols;j++) {
            c.data[i][j]=a.data[i][j]*k;
        }
    }
    return c;
}

Matrix transpose_matrix(Matrix a)
{
    Matrix c=create_matrix(a.cols,a.rows);
    for (int i=0;i<a.rows;i++) {
        for (int j=0;j<a.cols;j++) {
            c.data[j][i]=a.data[i][j];
        }
    }
    return c;
}

double det_matrix(Matrix a)
{
    if (a.rows!=a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0.0;
    }
    else if(a.rows==1&&a.cols==1){
        return a.data[0][0];
    }
    else{
        double sum=0.0;
        double pn_num=1.0;
        for (int i=0;i<a.rows;i++){
            Matrix c=create_matrix(a.rows-1,a.cols-1);
            for(int j=0;j<a.rows;j++){
                if(i==j)continue;
                for(int k=1;k<a.cols;k++){
                    if(j<i){
                        c.data[j][k-1]=a.data[j][k];
                    }
                    else{
                        c.data[j-1][k-1]=a.data[j][k];
                    }
                }
            }
            double row_num=0.0;
            row_num=a.data[i][0]*pn_num*det_matrix(c);
            for (int i = 0; i < c.rows; i++) {
                free(c.data[i]);
            }
            free(c.data);
            sum+=row_num;
            pn_num=-pn_num;
        }
        return sum;
    }
}

Matrix inv_matrix(Matrix a)
{
    if (a.rows != a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        Matrix c = create_matrix(0, 0);
        return c;
    }
    double det = det_matrix(a);
    if (det == 0.0) {
        printf("Error: The matrix is singular.\n");
        Matrix c = create_matrix(0, 0);
        return c;
    }
    Matrix bs = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            Matrix m = create_matrix(a.rows - 1, a.cols - 1);
            for (int r = 0; r < a.rows; r++) {
                if (r == j) continue;
                int row_in_m = r < j ? r : r - 1;
                for (int c = 0; c < a.cols; c++) {
                    if (c == i) continue;
                    int col_in_m = c < i ? c : c - 1;
                    m.data[row_in_m][col_in_m] = a.data[r][c];
                }
            }
            double mdet = det_matrix(m);
            bs.data[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * mdet;
        }
    }
    Matrix inv = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            inv.data[j][i] = bs.data[i][j] / det; // 转置伴随矩阵
        }
    }
    return inv;
}

int rank_matrix(Matrix a)
{
    Matrix c=create_matrix(a.rows,a.cols);
    for(int i=0;i<a.rows;i++) {
        for(int j=0;j<a.cols;j++) {
            c.data[i][j]=a.data[i][j];
        }
    }
    int row=0;
    for(int ii=0;ii<a.cols&&row<a.rows;ii++) {
        int Num=row;
        for(int jj=row+1;jj<a.rows;jj++) {
            if(fabs(c.data[jj][ii])>fabs(c.data[Num][ii])) Num=jj;
        }
        if(fabs(c.data[Num][ii])==0)continue;
        if(Num!=row){
            for(int z=0;z<a.cols;z++){
                double t=c.data[row][z];
                c.data[row][z]=c.data[Num][z];
                c.data[Num][z]=t;
            }
        }
        double xx=c.data[row][ii];
        for(int k=ii;k<a.cols;k++)c.data[row][k]/=xx;
        for(int kk=0;kk<a.rows;kk++){
            if(kk!=row){
                double mul=c.data[kk][ii];
                for(int j=ii;j<a.cols;j++){
                    c.data[kk][j]-=mul*c.data[row][j];
                }
            }
        }
        row++;
    }
    int rank=row;
    for (int i = 0; i < c.rows; i++) {
        free(c.data[i]);
    }
    free(c.data);
    return rank;
}

double trace_matrix(Matrix a)
{
    if (a.rows !=a.cols) {
        printf("Error: The matrix must be a square matrix.\n");
        return 0.0;
    }
    double sum=0.0;
    for (int i=0;i<a.rows;i++) {
        sum+=a.data[i][i];
    }
    return sum;
}
void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}