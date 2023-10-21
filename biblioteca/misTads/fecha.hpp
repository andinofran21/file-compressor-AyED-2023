#include <iostream>
#include <time.h>
#include "../biblioteca/funciones/strings.hpp"
using namespace std;

struct Fecha
{
    int dia;
    int mes;
    int anio;
};

// retorna la fecha actual
void _getDate(int &d, int &m, int &a)
{
    // fecha actual expresada en segundos
    time_t timestamp;
    time(&timestamp);

    // separo la fecha actual en atributos
    struct tm *fechaActual = localtime(&timestamp);
    d = fechaActual->tm_mday;
    m = fechaActual->tm_mon + 1;
    a = fechaActual->tm_year + 1900;
}

// funcion de inicializacion d,m,a
Fecha fecha(int d, int m, int a)
{
    return {d, m, a};
}

// funcion de inicializacion que retorna la fecha actual
Fecha fecha()
{
    int d, m, a;
    _getDate(d, m, a);
    return fecha(d, m, a);
}

// funcion de inicializacion (string)+formato
Fecha fecha(string f, string formato)
{
    int dia;
    int mes;
    int anio;

    if (length(f) > 8)
    {
        if (formato == "aaaa/mm/dd") // aaaa/mm/dd
        {
            dia = stringToInt(substring(f, 8));
            mes = stringToInt(substring(f, 5, 7));
            anio = stringToInt(substring(f, 0, 4));
        }
        else // dd/mm/aaaa
        {
            dia = stringToInt(substring(f, 0, 2));
            mes = stringToInt(substring(f, 3, 5));
            anio = stringToInt(substring(f, 6));
        }
    }
    else
    {
        if (formato == "aaaammdd")
        {
            dia = stringToInt(substring(f, 6));
            mes = stringToInt(substring(f, 4, 6));
            anio = stringToInt(substring(f, 0, 4));
        }
        else
        {
            dia = stringToInt(substring(f, 0, 2));
            mes = stringToInt(substring(f, 2, 4));
            anio = stringToInt(substring(f, 4));
        }
    }

    return {dia, mes, anio};
}

// funcion de inicializacion (int)+formato
Fecha fecha(int f, string formato)
{
    string sf = intToString(f);
    return fecha(sf, formato);
}

// retorna el dia
int fechaGetDia(Fecha f)
{
    return f.dia;
}

// retorna el mes
int fechaGetMes(Fecha f)
{
    return f.mes;
}

// retorna el anio
int fechaGetAnio(Fecha f)
{
    return f.anio;
}

// modifica el dia
void fechaSetDia(Fecha &f, int d)
{
    f.dia = d;
}

// modifica el mes
void fechaSetMes(Fecha &f, int m)
{
    f.mes = m;
}

// modifica el anio
void fechaSetAnio(Fecha &f, int a)
{
    f.anio = a;
}

// convierte la estructura fecha en una cadena separado por sep
string fechaToString(Fecha f, char sep)
{
    string sDia = to_string(f.dia);
    string sMes = to_string(f.mes);
    string sAnio = to_string(f.anio);

    return sDia + sep + sMes + sep + sAnio;
}

// convierte la estructura fecha en una cadena separado por '/'
string fechaToString(Fecha f)
{
    return fechaToString(f, '/');
}

bool fechaEsAnioBisiesto(Fecha f)
{
    int a = f.anio;
    return a % 4 == 0 || (a % 400 == 0 && a % 100 != 0);
}

int fechaDiasDelMes(Fecha f)
{
    int nDias = 31;

    if (f.mes == 4 || f.mes == 6 || f.mes == 9 || f.mes == 11)
    {
        nDias = 30;
    }
    else
    {
        if (f.mes == 2)
        {
            nDias = 28;
            if (fechaEsAnioBisiesto(f))
            {
                nDias = 29;
            }
        }
    }

    return nDias;
}

// retorna true o false si la fecha esta bien puesta
bool fechaValidar(Fecha f)
{
    bool fOk = false;

    if (f.mes >= 1 && f.mes <= 12)
    {

        int nDias = fechaDiasDelMes(f);
        if (f.dia >= 1 && f.dia <= nDias)
        {
            fOk = true;
        }
    }

    return fOk;
}

// añade anios a la fecha
void fechaAddAnios(Fecha &f, int a)
{
    f.anio += a;
}

// añade meses a la fecha
void fechaAddMeses(Fecha &f, int m)
{
    int meses = (f.mes + m) % 12;
    ;
    int anios = (f.mes + m) / 12;

    fechaAddAnios(f, anios);
    f.mes = meses;
}

// añade dias a la fecha (recordatorio: me costo un huevo)
int fechaAddDias(Fecha &f, int d)
{
    int diasDelMes = fechaDiasDelMes(f);
    int dias = (f.dia + d) % diasDelMes;

    if (diasDelMes <= d)
    {
        fechaAddMeses(f, 1);
        d = fechaAddDias(f, d - diasDelMes);
    }

    f.dia += d;
    if (f.dia > diasDelMes)
    {
        fechaAddMeses(f, 1);
        f.dia = dias;
    }

    return 0;
}

// retorna true si f1 es mayor que f2
bool fechaEsMayor(Fecha f1, Fecha f2)
{
    bool ret = false;
    if (f1.anio > f2.anio)
    {
        ret = true;
    }
    else
    {
        if (f1.mes > f2.mes)
        {
            ret = true;
        }
        else
        {
            if (f1.dia > f2.mes)
            {
                ret = true;
            }
        }
    }

    return ret;
}

int _getDayWeek(Fecha &fecha)
{
    int mes, anio, a, y, m, d;

    mes = fecha.mes;
    anio = fecha.anio;

    if (mes < 3)
    {
        mes += 12;
        anio--;
    }

    a = anio / 100;
    y = anio - 100 * a;
    m = mes;
    d = fecha.dia;

    int resultado = (d + ((13 * (m + 1)) / 5) + y + (y / 4) + (a / 4) - 2 * a) % 7;

    if (resultado < 0)
    {
        resultado += 7;
    }

    return resultado;
}

// retorna el dia de la semana (lun/mar/mier/juev/sab/dom)
string fechaDiaDeLaSemana(Fecha f)
{
    string dia;
    switch (_getDayWeek(f))
    {
    case 0:
        dia = "sábado.";
        break;
    case 1:
        dia = "domingo.";
        break;
    case 2:
        dia = "lunes.";
        break;
    case 3:
        dia = "martes.";
        break;
    case 4:
        dia = "miércoles.";
        break;
    case 5:
        dia = "jueves.";
        break;
    case 6:
        dia = "viernes.";
        break;
    default:
        std::cout << "día no válido.";
        break;
    }

    return dia;
}

// retorna el nombre del mes
string fechaNombreDelMes(Fecha f)
{
    string mes;
    switch (f.mes)
    {
    case 1:
        mes = "Enero.";
        break;
    case 2:
        mes = "Febrero.";
        break;
    case 3:
        mes = "Marzo.";
        break;
    case 4:
        mes = "Abril.";
        break;
    case 5:
        mes = "Mayo.";
        break;
    case 6:
        mes = "Junio.";
        break;
    case 7:
        mes = "Julio.";
        break;
    case 8:
        mes = "Agosto.";
        break;
    case 9:
        mes = "Septiembre.";
        break;
    case 10:
        mes = "Octubre.";
        break;
    case 11:
        mes = "Noviembre.";
        break;
    case 12:
        mes = "Diciembre.";
        break;
    default:
        std::cout << "mes no válido.";
        break;
    }

    return mes;
}

// calcula la edad a partir de determinada fecha
int fechaCalcularEdad(Fecha &fechaNacimiento, Fecha &f)
{
    int edad = f.anio - fechaNacimiento.anio;

    // Verificar si todavía no se ha cumplido el día y mes de nacimiento en el año actual
    if (f.mes < fechaNacimiento.mes ||
        (f.mes == fechaNacimiento.mes && f.dia < fechaNacimiento.dia))
    {
        edad--;
    }

    return edad;
}

// calcula la edad a partir de la fecha actual
int fechaCalcularEdad(Fecha fechaNacimiento)
{
    Fecha fechaActual = fecha();
    return fechaCalcularEdad(fechaNacimiento, fechaActual);
}