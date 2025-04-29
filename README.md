# X-Lab硬件部第一次内训作业（线性代数计算库的实现）
姓名：何辰阳     学号：3240104411  

---

## 1. 作业背景与说明  



### 1.1 作业内容  

本次作业旨在用C语言实现一个实现一个线性代数计算库，来辅助我们进行运算。考察了基础的数学能力、通过编程解决问题的能力以及工程管理、CMake、git等综合能力。作业在编程部分需完成以下内容：  

> 1. 根据`inc/algebra.h`中的注释和预定义，在`src/algebra.c`中实现对应的函数。
> 2. 自行编写`CMakeLists.txt`文件，使工程能够在本地成功编译运行。
> 3. 修改`README.md`文件，需要包含实现思路以及本地运行截图。

### 1.2 输入与输出
本题目采用帧判定的思路进行：

每一帧的第一行指令代码，`+`、`-`、`*`、`.`、`t`、`d`、`i`、`r`、`j`分别测试`add_matrix`（加法运算）、`sub_matrix`（减法运算）、`mul_matrix`（乘法运算）、`scale_matrix`（数乘运算）、`transpose_matrix`（转置运算）、`det_matrix`（行列式求解）、`inv_matrix`（矩阵的逆运算）、`rank_matrix`（矩阵求秩）、`trace_matrix`（矩阵求迹）函数，`q`表示退出。

接下来的一行输入矩阵 $\mathbf{A}$ 的行数 $m$ 和列数 $n$ ，在接下来的 $m$ 行中输入 $n$ 个双精度浮点数，以空格分开。
对于二元运算函数的测试，需要再按照上述过程输入矩阵 $\textbf{B}$ 。  

在每一帧中，依次根据输入的指令代码运行对应的函数，并给出函数的输出与标准值比对。 

---

## 2. algebra.c的函数思路简介、代码实现、输出示例  



### 2.1 加法的实现  

#### 2.1.1 思路简介  

矩阵的加法运算较为简单，将两个行数、列数均相同的存在于` Matrix`结构中的矩阵（以一个二维数组的形式储存）每个对应位置的数对应相加产生一个新矩阵并输出即可。另外，若两个矩阵的行数或列数不相等，则无法进行矩阵的加法运算，会报错并输出一个空矩阵。

#### 2.1.2 代码实现  

``````c
Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.rows!=b.rows || a.cols!=b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        Matrix c=create_matrix(0,0);
        return c;
    }
    /*
    判断两个矩阵的行数、列数是否相等，若行数或列数不相等则报错
    */
    else{
        Matrix c=create_matrix(a.rows,a.cols);
        for (int i=0;i<c.rows;i++) {
            for (int j=0;j<c.cols;j++) {
                c.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return c;    
    }
    /*
    两个矩阵每个对应位置的数对应相加产生一个新矩阵并输出
    */
    
}
``````

#### 2.1.3 输出示例  

![](C:\Users\he'chen'yang\Desktop\tp\+1.png) ![](C:\Users\he'chen'yang\Desktop\tp\+2.png)![](C:\Users\he'chen'yang\Desktop\tp\+3.png)![](C:\Users\he'chen'yang\Desktop\tp\+4.png)

  

### 2.2 减法的实现  

#### 2.2.1 思路简介  

矩阵的减法运算与加法运算类似，将两个行数、列数均相同的存在于` Matrix`结构中的矩阵（以一个二维数组的形式储存）每个对应位置的数对应相减产生一个新矩阵并输出即可。另外，若两个矩阵的行数或列数不相等，则无法进行矩阵的减法运算，会报错并输出一个空矩阵。

#### 2.2.2 代码实现  

``````C
Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.rows!=b.rows || a.cols!=b.cols) {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        Matrix c=create_matrix(0,0);
        return c;
    }
    /*
    判断两个矩阵的行数、列数是否相等，若行数或列数不相等则报错
    */
    else{
        Matrix c=create_matrix(a.rows,a.cols);
        for (int i=0;i<c.rows;i++) {
            for (int j=0;j<c.cols;j++) {
                c.data[i][j]=a.data[i][j]-b.data[i][j];
            }
        }
        return c;    
    }
    /*
    两个矩阵每个对应位置的数对应相加产生一个新矩阵并输出
    */
}
``````

#### 2.2.3 输出示例  

