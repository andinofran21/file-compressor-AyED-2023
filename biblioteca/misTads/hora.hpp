#include<iostream>
#include <ctime>
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

Hora horaActual()
{
    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);

    Hora horaActual;
    horaActual.hora = tiempo->tm_hour;
    horaActual.min = tiempo->tm_min;
    horaActual.seg = tiempo->tm_sec;

    return horaActual;
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

double horaToHora(Hora h)
{
    double horas = (double)(h.hora + h.min/60 + h.seg/3600); 
    return (double)horas;
}

int horaToMin(Hora h)
{
    return h.hora*60+h.min+h.seg/60;
}
int horaToSeg(Hora h)
{
    return h.hora*60+h.min*60+h.seg;
}

Hora horaDiff(Hora horaInicio, Hora horaFinal) {
    int segundosInicio = horaToSeg(horaInicio);
    int segundosFinal = horaToSeg(horaFinal);

    int diferenciaSegundos = segundosFinal - segundosInicio;

    // Manejar el caso si la hora final es anterior a la hora inicial
    if (diferenciaSegundos < 0) {
        diferenciaSegundos += 24 * 3600; // Sumar un día en segundos (24 horas * 3600 segundos/hora)
    }

    int horas = diferenciaSegundos / 3600;    // Obtener la cantidad de horas
    diferenciaSegundos %= 3600;               // Actualizar los segundos restantes
    int minutos = diferenciaSegundos / 60;    // Obtener la cantidad de minutos
    diferenciaSegundos %= 60;                 // Obtener los segundos restantes

    return hora(horas, minutos, diferenciaSegundos); // Devolver la diferencia como una estructura Hora
}
