#include<iostream>
using namespace std;

struct Fraccion
{
    int n;
    int d;
};

Fraccion fraccion(int numerador, int denominador) // funcion de inicializacion
{
    return {numerador,denominador};
}

string fraccionToString(Fraccion f)
{
    string sNumerador = to_string(f.n);
    string sDenominador = to_string(f.d);

    return sNumerador+"/"+sDenominador;
}

bool fraccionOk(Fraccion f)
{
    return f.d!=0;
}

double fraccionSumar(Fraccion f1, Fraccion f2)
{
    double suma=0;
    if(f1.d==f2.d)
    {
        suma=(f1.n+f2.n)/f1.d;
    }
    else
    {
        int dComun = f1.d*f2.d;
        suma=(double)((dComun/f1.d*f1.n)+(dComun/f2.d*f2.n))/dComun;
    }
    return suma;
}

double fraccionRestar(Fraccion f1, Fraccion f2)
{
    double suma=0;
    if(f1.d==f2.d)
    {
        suma=(f1.n-f2.n)/f1.d;
    }
    else
    {
        int dComun = f1.d*f2.d;
        suma=(double)((dComun/f1.d*f1.n)-(dComun/f2.d*f2.n))/dComun;
    }
    return suma;
}

double fraccionMultiplicar(Fraccion f1, Fraccion f2)
{
    return (double)(f1.n*f2.n)/(f1.d*f2.d);
}

double fraccionDividir(Fraccion f1, Fraccion f2)
{
    return (double)(f1.n*f2.d)/(f1.d*f2.n);
}