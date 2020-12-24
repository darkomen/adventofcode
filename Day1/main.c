#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_RESULT 2020
FILE * pFile;
char line[32];
unsigned int TotalLines;
unsigned int pos;
unsigned int operatorA = 0, operatorB = 0, operatorC = 0, result = 0;
unsigned int *GroupOfNumbers;

FILE * files_OpenFile(const char* _pathfile){
    FILE * _pFile;
    _pFile = fopen(_pathfile,"rb");
    if(_pFile == NULL){
      printf("File don't exists");   
      exit(1);             
    }
    return _pFile;
}

void files_CloseFile(FILE * _pFile){
    fclose(_pFile);
}

int files_CountNumberOfLines(FILE *_file){
    char ActualLine[32];
    unsigned int NumberOfLines = 0;
    rewind(pFile);
    while(fgets(ActualLine,32,_file)){
        NumberOfLines++;
    }
    return NumberOfLines;
}

int files_FileToArray(FILE *_file, unsigned int * _groupOfNumbers){
    char ActualLine[32];
    rewind(_file);
    while(fscanf(_file,"%d",_groupOfNumbers) != EOF){
        _groupOfNumbers++;
    }
}

int SumOfTwoOperator(unsigned int *_groupOfNumbers, unsigned int _size){
    for(int i=0;i<=_size;i++){
        operatorA = *(_groupOfNumbers+i);
        for(int j=(i+1);j<=_size;j++){
            operatorB = *(_groupOfNumbers+j);
            result = operatorA + operatorB;
            if (result == TARGET_RESULT){
                printf("Operadores encontrados: %d - %d\n",operatorA,operatorB);
                printf("La multiplicacion de ambos operadores es: %lu\n",(operatorA*operatorB));
                return 0;
            }
        }
    }
}

int SumOfThreeOperator(unsigned int *_groupOfNumbers, unsigned int _size){
    for(int i=0;i<=_size;i++){
        operatorA = *(_groupOfNumbers+i);
        for(int j=(i+1);j<=_size;j++){
            operatorB = *(_groupOfNumbers+j);
            if(operatorA+operatorB < TARGET_RESULT){
                for(int k=(j+1);k<=_size;k++){
                    operatorC = *(_groupOfNumbers+k);
                    result = operatorA + operatorB + operatorC;
                    if (result == TARGET_RESULT){
                        printf("Operadores encontrados: %d - %d - %d\n",operatorA,operatorB,operatorC);
                        printf("La multiplicacion de ambos operadores es: %lu\n",(operatorA*operatorB*operatorC));
                        return 0;
                    }
                }
            }
        }
    }

}
int main() {

    pFile = files_OpenFile("./files/input.txt");
    TotalLines = files_CountNumberOfLines(pFile);

    GroupOfNumbers = (int*)malloc ( TotalLines*sizeof(int) );
    memset(GroupOfNumbers,0,TotalLines);

    files_FileToArray(pFile,GroupOfNumbers);
    files_CloseFile(pFile);

    printf("[SUMA CON DOS OPERADORES]\n ");
    SumOfTwoOperator(GroupOfNumbers,TotalLines);
    printf("[SUMA CON TRES OPERADORES]\n ");
    SumOfThreeOperator(GroupOfNumbers,TotalLines);
    free(GroupOfNumbers);

    return 0;
}

