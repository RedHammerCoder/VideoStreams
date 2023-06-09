#include "../Inc/Utilly.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
using namespace BinaryOps;
char BUFF[512];

int main(){
    memset((void*)BUFF,'a',512);
    strncpy(BUFF+20,"args",4 );
    strncpy(BUFF+80,"args",4 );
    strncpy(BUFF+240,"args",4 );
    StrSplit  binView(BUFF,512);
    char* TR=nullptr;
    do
    {
        auto[tail , len]= binView.Splite("args",4);
        printf("%d ,  %s  Toend\n",len,tail-len);
        TR=tail;
    } while (TR!=nullptr);
    return 0;
    
    
    
        /* code */
    }
    
    
