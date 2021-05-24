#include <rtc.h>
#include <lib.h>

//define para los valores de RTC
#define SECONDS 0x00
#define MINUTES 0x02
#define HOURS   0x04
#define DAYS    0x07
#define MONTHS  0x08
#define YEARS   0x09
//constante que marca la diferencia horaria para poder obtener la hora de Argentina
#define TIME_ZONE 3

//define para switch-case
#define SEC   0
#define MIN   1
#define HOUR  2
#define DAY   3
#define MONTH 4
#define YEAR  5

unsigned char RTC(unsigned char mode);

//obtenemos los bits sinificativos de RTC
static unsigned int cast(unsigned char time)
{
    return (time >> 4) * 10 + (time & 0x0F);
}

int DateTime(unsigned int selector) {
    switch (selector)
    {
    case SEC:
        return cast(RTC(SECONDS));
    case MIN:
        return cast(RTC(MINUTES));
    case HOUR:
        return cast(RTC(HOURS)) - TIME_ZONE;
    case DAY:
        return cast(RTC(DAYS));
    case MONTH:
        return cast(RTC(MONTHS));
    case YEAR:
        return cast(RTC(YEARS));
    default:
        return -1;
    }
}