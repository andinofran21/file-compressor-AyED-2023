#include <iostream>
#include <sys/time.h>
using namespace std;

typedef unsigned long long Long;
struct Timer
{
    Long momento1;
    Long momento2;
};

// tipo entero muy grande
// retorna la fecha actual expresada como la cantidad de millse-gundos 
//transcurridos a partir del 1 de enero de 1970.

Long timeInMillis() 
{
    struct timeval i;
    gettimeofday(&i, NULL);
    return (i.tv_sec * 1000000 + i.tv_usec) / 1000;
}

void timerStart(Timer &t) // instante inicial (i)
{ 
    t.momento1=timeInMillis();
}
void timerStop(Timer& t) // instante final (f)
{
    t.momento2=timeInMillis();
}


Long timerElapsedTime(Timer t)// retorna el tiempo transcurrido entre f e i, expresado en milisegundos
{
    Long ret =t.momento2-t.momento1;

    return ret;
}
