#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE *fp;
    fp = fopen(argv[1],"r");

    int matrixsize;
    fscanf(fp,"%d",&matrixsize);
    
    
    int **beginmatrix = (int **)malloc(matrixsize * sizeof(int *));
    int **finalmatrix = (int **)malloc(matrixsize * sizeof(int *)); 
    int **temp = (int **)malloc(matrixsize * sizeof(int *)); 

    int i, j, k = 0; 
    for (i=0; i<matrixsize; i++){
       beginmatrix[i] = (int *)malloc(matrixsize * sizeof(int)); 
    };    
    for (i = 0; i < matrixsize; i++){
        finalmatrix[i] = (int *)malloc(matrixsize*sizeof(int));
    };
    for (i=0; i<matrixsize; i++){
       temp[i] = (int *)malloc(matrixsize * sizeof(int)); 
    };




    for (i = 0; i <  matrixsize; i++){
      for (j = 0; j < matrixsize; j++){
        fscanf(fp,"%d",&beginmatrix[i][j]);
      }; 
    }; 
      

    int tothe;
    fscanf(fp,"%d",&tothe);
  

    if(tothe == 0){
      for(i =0; i < matrixsize;i++){
          finalmatrix[i][i] = 1;   
      };
      for (i = 0; i < matrixsize; i++) { 
        for (j = 0; j < matrixsize; j++) 
          printf("%d ", finalmatrix[i][j]); 
        printf("\n"); 
      }
      return 0;
    };

    
    if(tothe == 1){
      for (i = 0; i < matrixsize; i++) { 
        for (j = 0; j < matrixsize; j++) 
          printf("%d ", finalmatrix[i][j]); 
        printf("\n"); 
      }
      return 0;
    }


    if(tothe ==2){
      for (i = 0; i <  matrixsize; i++){
        for (j = 0; j < matrixsize; j++){
          for(k = 0; k<matrixsize;k++){
            finalmatrix[i][j] += beginmatrix[i][k]*beginmatrix[k][j];
          };
        }; 
      }; 
      for (i = 0; i < matrixsize; i++) { 
        for (j = 0; j < matrixsize; j++) 
          printf("%d ", finalmatrix[i][j]); 
        printf("\n"); 
      }
      return 0;  
    }


    for (i = 0; i <  matrixsize; i++){
        for (j = 0; j < matrixsize; j++){
          for(k = 0; k<matrixsize;k++){
            finalmatrix[i][j] += beginmatrix[i][k]*beginmatrix[k][j];
          };
        }; 
    }; 
    
    for(int z =0; z < tothe-2; z++ ){
      for (i = 0; i <  matrixsize; i++){
        for (j = 0; j < matrixsize; j++){
          temp[i][j] = 0;
          for(k = 0; k<matrixsize;k++){
            temp[i][j] += finalmatrix[i][k]*beginmatrix[k][j];
          };
        }; 
      };


      for (i = 0; i < matrixsize; i++){
          for(j = 0; j< matrixsize;j++){
            finalmatrix[i][j] = temp[i][j];
          };
      }; 
    }
    
      

    for (i = 0; i < matrixsize; i++) { 
        for (j = 0; j < matrixsize; j++){
          if(j==matrixsize-1){
            printf("%d", finalmatrix[i][j]); 
          }else{
            printf("%d ", finalmatrix[i][j]); 
          }

        } 
           
        printf("\n"); 
    } 
  


  

    free(finalmatrix);
    free(beginmatrix);
    fclose(fp);
    
};
