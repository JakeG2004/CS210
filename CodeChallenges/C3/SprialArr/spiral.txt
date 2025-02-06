#include <stdio.h>
#include <stdlib.h>

int** CreateMatrix(int rows, int cols);
void PrintSpiral(int** matrix, int rows, int cols);

int main()
{
   int rows = 4;
   int cols = 5;

   int** matrix = CreateMatrix(rows, cols);
   printf("\n\n");

   PrintSpiral(matrix, rows, cols);
}

void PrintSpiral(int** matrix, int rows, int cols)
{
   int depth = 0;

   // Calculate min depth
   int rowMin = (rows / 2) + (rows % 2);
   int colMin = (cols / 2) + (cols % 2);

   while(depth != rowMin && depth != colMin)
   {
      // Print across the top
      for(int i = depth; i < cols - depth; i++)
      {
         printf("%i ", matrix[depth][i]);
      }

      // Print acrosss the right
      for(int i = depth + 1; i < rows - depth; i++)
      {
         printf("%i ", matrix[i][cols - 1 - depth]);
      }

      // Print across the bottom
      for(int i = cols - 2 - depth; i >= depth; i--)
      {
         printf("%i ", matrix[rows - 1 - depth][i]);
      }

      // Print across the left
      for(int i = rows - 2 - depth; i > depth; i--)
      {
         printf("%i ", matrix[i][depth]);
      }

      depth++;
   }

   printf("\n");
}

int** CreateMatrix(int rows, int cols)
{
   // Create 2d array dynamically
   int** matrix = (int**)malloc(sizeof(int*) * rows);
   for(int i = 0; i < rows; i++)
   {
      matrix[i] = (int*)malloc(sizeof(int) * cols);
   }

   // Fill array with values dynamically
   for(int i = 0; i < rows; i++)
   {
      for(int j = 0; j < cols; j++)
      {
         matrix[i][j] = i * cols + j;
         printf("%i ", matrix[i][j]);
      }

      printf("\n");
   }

   return matrix;
}
