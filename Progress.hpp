#ifndef _PROGRESSHPP
#define _PROGRESSHPP

#include <iostream>
#include "biblioteca/misTads/hora.hpp"
using namespace std;

struct Progress
{
    unsigned int bytesProcessed;
    unsigned int totalBytes;
    Hora hi;
};

// funcion de inicializacion con el tamaño del archivo
Progress progress(unsigned int totalBytes)
{
    return{1,totalBytes,horaActual()};
}

// muestra el proceso de la compresion/compresion byte a byte
void progressShow(Progress &p)
{
    int progreso = static_cast<float>(p.bytesProcessed) / p.totalBytes * 100; // Calcular el progreso en porcentaje

    // Mostrar el progreso cada cierta cantidad de bytes procesados
    if (p.bytesProcessed % 10240 == 0)
    {
        cout << "\rProgreso: " << progreso << "% completado";
        cout.flush();
    }

    if(p.bytesProcessed==p.totalBytes)
    {
        cout << "\rProgreso: " << 100 << "% completado";
        cout.flush();
    }
    
    p.bytesProcessed++; // incrementar la cantidad de bytes procesados
}

// muestra por pantalla la duracion del proceso
void progressShowDuration(Progress p)
{
    Hora hf = horaActual();
    Hora h = horaDiff(p.hi,hf);
    cout<<"\nDuracion: "<<horaToString(h)<<endl;
}

#endif