#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int getNumberOfDigits(int number, int system){
    int counter = 0;

    if(number < 0)
        number *= -1;
    while (number > 0){
        number = number/system;
        counter++;
    }
     
    return counter;

}

void printInt(int number, int system){

    if (number == 0){
        char digit = '0';
        write(1, &digit, 1);
    }
    else 
    {   
        int digits = getNumberOfDigits(number, system);
        int sign = 0;
        if (number < 0)
            sign = 1;
       
        char* num;
        num = (char*)malloc((digits + sign)*sizeof(char));
        if (number < 0) 
         { 
            num[0] = '-';
            number *= -1;
        }
        int i = digits + sign -1;
        while(i>=sign){
            num[i] = number%system + 48;
            if (system == 16 && num[i]>57){
                num[i] += 7;
            }
            number -= number%system;
            number /= system;
            i--;
        }
        write (1, &num[0], digits + sign);
        free(num);
    }
}

void printString(char *line){
    int i=0;
    while(line[i] != '\0'){
        write(1, &line[i], 1);
        i++;
    }
}


void myPrintf(char *line, ...){
    //va_start
    char *ptr = (char*)&line;
    ptr += sizeof(char*);
    int i=0;
    while (line[i] != '\0'){
        if (line[i] != '%'){
            write(1, &line[i],1);
        }
        else if (line[i+1] == 's'){ 
            //va_arg
            char *str = *((char**)ptr);
            ptr += sizeof(char*);
            printString(str);
            i++;
        }
        else if (line[i+1] == 'd'){ 
            //va_arg
            int int1 = *((int*)ptr);
            ptr += sizeof(int);
            printInt(int1, 10);
            i++;
        }
        else if (line[i+1] == 'x'){ 
            //va_arg
            int int1 = *((int*)ptr);
            ptr += sizeof(int);
            printInt(int1, 16);
            i++;
        }
        else if (line[i+1] == 'b'){ 
            //va_arg
            int int1 = *((int*)ptr);
            ptr += sizeof(int);
            printInt(int1, 2);
            i++;
        }
        i++;
    }
    
}

void scanInt(char *input, int *adress, int length, int system){
    *adress = 0;
    int multiplier = 1;
    int sign = 0;
     if (input[0] == '-') 
    {
       sign = 1;
    }    
    
    for(int i=length-1;i>=sign;i--){
        if(system == 16 && input[i]>64){
            *adress += (input[i]-55) * multiplier;
        }
        else {
            *adress += (input[i]-48) * multiplier;
        }
        multiplier *= system;
    }

    if (sign == 1)
        *adress *= -1;

 
}

void scanString(char *input, char *adress, int length){
    for(int i=0;i<length-1;i++){
        adress[i]=input[i];
    }
    adress[length-1] = '\0';
}

void myScanf(const char *format, ...){
    //va_start
    char *ptr = (char*)&format;
    ptr += sizeof(char*);
    int i=0;
    char* input;
    input = (char*)malloc(32*sizeof(char));
    while(format[i] != '\0'){
        if(format[i]=='%'){
            int length = read(0, input, 32);
            i++;
            switch(format[i]){
                case 's':{
                    char *str = *((char**)ptr);
                    ptr += sizeof(char*);
                    scanString(input, str, length);
                    break;
                }
                case 'x':{
                    int* int1;
                    int1 = *((int*)ptr);
                    scanInt(input, int1, length-1, 16);
                    ptr += sizeof(int*);
                    break;
                }
                case 'b':{
                    int* int1;
                    int1 = *((int*)ptr);
                    scanInt(input, int1, length-1, 2);
                    ptr += sizeof(int*);
                    break;
                }
                case 'd':{
                    int* int1;
                    int1 = *((int*)ptr);
                    scanInt(input, int1, length-1, 10);
                    ptr += sizeof(int*);
                    break;
                }
            }
        }
        i++;
    }
}

int main(){
    int s;
    char test[33];
    myPrintf("TEST\nPodaj string:\n");
    myScanf("%s", test);
    myPrintf("To twoj string: %s\nPodaj liczbe calkowita:\n", test);
    myScanf("%d", &s);
    myPrintf("To twoja liczba calkowita w systemie: dec %d bin %b hex %x\nPodaj liczbe w systemie binarnym:\n", s, s, s);
    myScanf("%b", &s);
    myPrintf("To twoja liczba binarna: %d \nPodaj liczbe w systemie heksadecymalnym:\n", s);
    myScanf("%x", &s);
    myPrintf("To twoja liczba heksadecymalna: %d \n", s);
}
