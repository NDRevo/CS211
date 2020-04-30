#include <stdio.h>
#include <stdlib.h>

void  convert(char output[], int value, int x){
    if (value == 0){
        output[x] = '\0';
        return;
    }
   
    if(value >= 1000){
        output[x] = 'M';
        value = value - 1000;
        x = x + 1;
        convert(output,value,x);
    }
    else if(value >= 900 ){
        output[x] = 'C';
        x = x + 1;
        output[x] = 'M';
        value = value - 900;
        x = x +1;
        convert(output,value,x);
    }
    else if(value >= 500 ){
        output[x] = 'D';
        value = value - 500;
        x = x + 1;
        convert(output,value,x);
    }
    else if(value >=400 ){
        output[x] = 'C';
        x = x+1;
        output[x] = 'D';
        value = value - 400;
         x = x+1;
        convert(output,value,x);
        
    }
    else if(value >= 100 ){
        output[x] = 'C';
        value = value - 100;
        x = x + 1;
        convert(output,value,x);
    }
    else if( value >= 90 ){
        output[x] = 'X';
        x = x+1;
        output[x] = 'C';
        value = value - 90;
         x = x+1;
        convert(output,value,x);
    }
    else if(value >= 50 ){
        output[x] = 'L';
        value = value - 50;
        x = x + 1;
        convert(output,value,x);
    }
    else if(value >=40 ){
        output[x] = 'X';
        x = x+1;
        output[x] = 'L';
        value = value - 40;
         x = x+1;
        convert(output,value,x);
    }
    else if(value >= 10 ){
        output[x] = 'X';
        value = value - 10;
        x = x + 1;
        convert(output,value,x);

    }
    else if( value >= 9 ){
        output[x] = 'I';
        x = x+1;
        output[x] = 'X';
        value = value - 9;
         x = x+1;
        convert(output,value,x);
    }
    else if(value >= 5 ){
        output[x] = 'V';
        value = value - 5;
        x = x + 1;
        convert(output,value,x);
    }
    else if( value >= 4 ){
        output[x] = 'I';
        x = x+1;
        output[x] = 'V';
        value = value - 4;
         x = x+1;
        convert(output,value,x);
    }
    else if(value >= 1 ){
        output[x] = 'I';
        value = value - 1;
        x = x + 1;
        convert(output,value,x);

    }
   

    

};


int main(int argc, char* argv[]) {
    int value = atoi(argv[1]);
    char output[500];


    convert(output, value, 0);
    printf("%s\n", output);
    return 0;
};

