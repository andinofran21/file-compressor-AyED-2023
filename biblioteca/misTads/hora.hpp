#include<iostream>
using namespace std;

struct Hora
{
    int seg;
    int min;
    int hora;
};

Hora hora(int horas, int minutos, int segundos) // funcion de inicializacion
{
    return {segundos,minutos,horas};
}

string horaToString(Hora h)
{
    string sHora=to_string(h.hora);
    string sMinutos=to_string(h.min);
    string sSegundos=to_string(h.seg);

    return sHora+"hs "+sMinutos+"min "+sSegundos+"seg";
}

int horaGetHora(Hora h)
{
    return h.hora;
}
int horaGetMinutos(Hora h)
{
    return h.min;
}
int horaGetSegundos(Hora h)
{
    return h.seg;
}

double horaHToHora(Hora h)
{
    double horas = (double)(h.hora + h.min/60 + h.seg/3600); 
    return (double)horas;
}



int horaHToMin(Hora h)
{
    return h.hora*60+h.min+h.seg/60;
}
int horaHToSeg(Hora h)
{
    return h.hora*60+h.min*60+h.seg;
}
