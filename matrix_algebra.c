#include "matrix_algebra.h"

//define a struct to represent an n by m matrix. 
// the entries of this matrix should be doubles.
struct matrix 
{
	int n;
	int m;
	double ** mat;
};

mat* create_matrix(int n, int m)
{
	//Fill this function to return an n x m matrix of zeros.
	//The matrix should be allocated on the heap (that is, you return a mat* pointer)
	mat* matrix;
	matrix = malloc(sizeof(mat));
	matrix -> n = n;
	matrix -> m = m;
	matrix -> mat = malloc(sizeof(double *) * n);
	for (int i = 0; i < n; i++)
	{
		matrix -> mat[i] = malloc(sizeof(double) * m);
		for (int k = 0; k < m; k++)
		{
			matrix -> mat[i][k] = 0;
		}
	}

	return matrix;
}

mat* matrix_read(char* filename)
{
	//given a filename, read the next matrix stored in that file.
	// remember, matrices are stored in binary files in the following format:
	// int n, int m, nxm doubles, where n is the num of rows, m the num of columns and the following doubles are the n rows of m elements in the matrix.
	// if reading the matrix fails for whatever reason, you should return NULL.
	FILE * fptr = fopen(filename, "rb");
	if (fptr == NULL) {return NULL;}
	int n;
	int m;
	fread(&n, sizeof(int), 1, fptr);
	fread(&m, sizeof(int), 1, fptr);
	mat* matrix = create_matrix(n, m);
	for (int i = 0; i < n; i++)
	{
		fread(matrix -> mat[i], sizeof(double), m, fptr);
	}
	fclose(fptr);
	return matrix;
}

mat* matrix_multiply(mat* A, mat*B)
{
	//fill this function to return a new matrix AB, the product of A and B. Return NULL if the product does not exist.
	if (A->m != B->n) return NULL;
	mat* matrix = create_matrix(A -> n, B -> m);
	for (int r = 0; r < A -> n; r++)
	{
		for (int c = 0; c < B -> m; c++)
		{
			double dot = 0;
			for (int ac = 0; ac < A -> m; ac++)
			{
				dot += A -> mat[r][ac] * B -> mat[ac][c];
			}
			matrix -> mat[r][c] = dot;
		}
	}

	return matrix;
}

mat* matrix_add(mat* A, mat* B)
{
	//fill this function to return the matrix A+B, the addition of A and B. Return NULL if the addition does not exist.
	if ((A -> n == B -> n) && (A -> m == B -> m))
	{
		mat* matrix  = create_matrix(A -> n, A -> m);
		for (int r = 0; r < A -> n; r++)
		{
			for (int c = 0; c < A -> m; c++)
			{
				matrix -> mat[r][c] = A -> mat[r][c] + B -> mat[r][c];
			}
		}

		return matrix;
	}

	return NULL;
}

void matrix_free(mat* A)
{
	//fill in this funciton to free the matrix A.
	if (A == NULL) return;
    for (int i = 0; i < A -> n; i++) 
	{
        free(A -> mat[i]);
    }
    free(A -> mat);
    free(A);
}

int matrix_write(char* filename, mat* A)
{
	// write A to the binary file filename. If this fails for whatever reason, return 0.
	if (A == NULL) {return 0;}
	FILE * fptr = fopen(filename, "wb");
	if (fptr == NULL) {return 0;}
	fwrite(&A -> n, sizeof(int), 1, fptr);
	fwrite(&A -> m, sizeof(int), 1, fptr);

	for (int i = 0; i < A -> n; i++)
	{
		fwrite(A -> mat[i], sizeof(double), A -> m, fptr);
	}
	fclose(fptr);
	return 1;

}

// fill this function to modify A into cA, that is, to multiply each entry of A by c.
mat* matrix_scale(double c, mat* A)
{
	mat* matrix = create_matrix(A -> n, A -> m); 
	for (int r = 0; r < A -> n; r++)
		{
			for (int col = 0; col < A -> m; col++)
			{
				matrix -> mat[r][col] = c * A -> mat[r][col];
			}
		}

	return matrix;
}






