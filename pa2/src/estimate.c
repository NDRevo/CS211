#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(double **matrix,int rows, int columns){
	for (int i = 0; i < rows; i++) { 
        for (int j = 0; j < columns; j++) 
          printf("%.0f", matrix[i][j]); 
        printf("\n"); 
    }

}

void transpose(double **arguments,double **argumentsTransposed, int numAttributes, int numHouses){
	for(int i = 0; i < numAttributes; i++){
		for(int j = 0; j < numHouses; j++){
			argumentsTransposed[i][j] = arguments[j][i];
		}
	}
	//print(argumentsTransposed,numAttributes,numHouses);
}

void inversing(double **matrix, double **inverse, int numHouses){
	for(int p = 0; p < numHouses; p++){
		double f = matrix[p][p];
		for(int i = 0; i < numHouses;i++){
			matrix[p][i]= matrix[p][i]/f;
			inverse[p][i]=inverse[p][i]/f;
		}
		
		for(int i = p+1;i < numHouses;i++){
			double f = matrix[i][p];
			for(int k = 0; k < numHouses;k++){
				matrix[i][k] -= matrix[p][k]*f;
				inverse[i][k] -= inverse[p][k]*f;
			}
			
		}
	}

	for(int p = numHouses-1; p >= 0; p--){
		for(int i = p-1; i >= 0; i--){
			double f = matrix[i][p];
			for(int k = numHouses-1; k >= 0;k--){
				matrix[i][k] -= matrix[p][k]*f;
				inverse[i][k] -= inverse[p][k]*f;
			}
		}	
	}
}
void multiply(double **matrix,double **othermatrix,double **finalmatrix, int finalrow, int numHouses,int finalcol){
    for (int i = 0; i <  finalrow; i++){
    	for (int j = 0; j < finalcol; j++){
        	finalmatrix[i][j] = 0;
			for(int k = 0; k < numHouses;k++){
				finalmatrix[i][j] += matrix[i][k]*othermatrix[k][j];
			};
    	}
	}
}

int main(int argc, char* argv[]){
	if(argc < 3) {
		printf("You forgot the fucking inputs dumb fuck\n");
		return 0;
	}
	FILE *train;
	FILE *data;
    train = fopen(argv[1],"r");
	data = fopen(argv[2],"r");
	char trainword[6];
	char dataword[6];
	fscanf(train,"%s",trainword);
	fscanf(data,"%s",dataword);
	if(strcmp(trainword, "train")){
		printf("Error: First Arg is not TRAIN\n");
		return 1;
	}
	if(strcmp(dataword, "data")){
		printf("Error: Second Arg Arg is not DATA\n");
		return 1;
	}
	
	int numAttributes;
	fscanf(train,"%d",&numAttributes);
	int numHouses;
	fscanf(train,"%d",&numHouses);
	numAttributes++;

	int dataAttributes;
	int dataHouses;
	fscanf(data,"%d",&dataAttributes);
	fscanf(data,"%d",&dataHouses);
	dataAttributes++;

	double **traindata = (double **)malloc(numHouses * sizeof(double *));
	double **datadata = (double **)malloc(dataHouses * sizeof(double *));
	double **arguments = (double **)malloc(numHouses * sizeof(double *));
	double **argumentsTransposed = (double **)malloc(numAttributes * sizeof(double *));	
	double **houseprices = (double **)malloc(numHouses * sizeof(double *));
	double **argumentandtemp = (double **)malloc(numAttributes * sizeof(double *));
	double **inverse = (double **)malloc(numAttributes* sizeof(double *));
	double **transinverse = (double **)malloc(numAttributes * sizeof(double *));
	double **weights = (double **)malloc(numAttributes * sizeof(double *));
	double **finalhouseprices = (double **)malloc(dataHouses * sizeof(double *));
	

	//Train data first, first k-1 columns are attributes , k'th column are prices
    int i, j = 0; 
	for (i=0; i < numHouses; i++){
       traindata[i] = (double *)malloc(numAttributes * sizeof(double)); 
    };
	for (i=0; i < dataHouses; i++){
       datadata[i] = (double *)malloc(dataAttributes * sizeof(double)); 
    };
    for (i=0; i < numHouses; i++){
        arguments[i] = (double *)malloc(numAttributes * sizeof(double)); 
    };
	for (i=0; i < numAttributes; i++){
        argumentsTransposed[i] = (double *)malloc(numHouses* sizeof(double)); 
    };
	for (i=0; i < numHouses; i++){
        houseprices[i] = (double *)malloc(2 * sizeof(double)); 
    }; 
	for (i=0; i < numAttributes; i++){
        argumentandtemp[i] = (double *)malloc(numAttributes * sizeof(double)); 
    }; 
	for (i=0; i < numAttributes; i++){
        inverse[i] = (double *)malloc(numAttributes * sizeof(double)); 
    }; 
	for (i=0; i < numAttributes; i++){
        transinverse[i] = (double *)malloc(numHouses * sizeof(double)); 
    }; 
	for (i=0; i < numAttributes; i++){
        weights[i] = (double *)malloc(1 * sizeof(double)); 
    }; 
	for (i=0; i < dataHouses; i++){
        finalhouseprices[i] = (double *)malloc(1 * sizeof(double)); 
    }; 
	//Make inverse identity
	for(i = 0; i < numAttributes; i++){
		for(int k = 0; k <numAttributes;k++){
			if(i == k){
				inverse[i][k]= 1;
			}
			else{
				inverse[i][k] = 0;
			}

		}
	}
	//Inputs into array from train
	for (i = 0; i <  numHouses; i++){
      for (j = 0; j < numAttributes; j++){
		fscanf(train,"%lf",&traindata[i][j]);
      }; 
    }; 
	//inputs into array from data
	for (i = 0; i <  dataHouses; i++){
      for (j = 0; j < dataAttributes; j++){
		if(j == 0){
			datadata[i][j] = 1;
		}
		else{
			fscanf(data,"%lf",&datadata[i][j]);
		}
      }; 
    }; 
	//inputs arguments AKA: X
	for (i = 0; i < numHouses; i++) { 
        for (j = 0; j < numAttributes; j++){
			if(j == 0){
				arguments[i][j] = 1;
			}
			else{
				arguments[i][j] = traindata[i][j-1];				
			}
		}
    }
	//Inputs house prices AKA: Y
	for (i = 0; i < numHouses; i++) { 
		houseprices[i][0] = traindata[i][numAttributes-1];				
    }


	transpose(arguments,argumentsTransposed,numAttributes,numHouses);
	multiply(argumentsTransposed,arguments,argumentandtemp,numAttributes,numHouses,numAttributes);
	inversing(argumentandtemp,inverse,numAttributes);
	multiply(inverse,argumentsTransposed,transinverse,numAttributes,numAttributes,numHouses);
	multiply(transinverse,houseprices,weights,numAttributes,numHouses,1);
	multiply(datadata,weights,finalhouseprices,dataHouses,dataAttributes,1);

	print(finalhouseprices,dataHouses,1);
	
	for (int i = 0; i < dataHouses; i++){
    	free(finalhouseprices[i]);
	}
	for (int i = 0; i < numHouses; i++){
    	free(traindata[i]);
	}
	for (int i = 0; i < numHouses; i++){
    	free(arguments[i]);
	}
	for (int i = 0; i < numAttributes; i++){
    	free(argumentsTransposed[i]);
	}
	for (int i = 0; i < numHouses; i++){
    	free(houseprices[i]);
	}
	for (int i = 0; i < numAttributes; i++){
    	free(argumentandtemp[i]);
	}
	for (int i = 0; i < numAttributes; i++){
    	free(inverse[i]);
	}
	for (int i = 0; i < numAttributes; i++){
    	free(transinverse[i]);
	}
	for (int i = 0; i < numAttributes; i++){
    	free(weights[i]);
	}
	for (int i = 0; i < dataHouses; i++){
    	free(datadata[i]);
	}

	free(finalhouseprices);
	free(traindata);
	free(arguments);
	free(argumentsTransposed);
	free(houseprices);
	free(argumentandtemp);
	free(inverse);
	free(transinverse);
	free(weights);
	free(datadata);

	return 0;
}
