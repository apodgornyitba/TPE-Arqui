#include <rtc.h>
#include <lib.h>

//obtenemos los bits sinificativos de RTC
static unsigned int cast(unsigned char time)
{
    return (time >> 4) * 10 + (time & 0x0F);
}

int DateTime(unsigned int selector)
{
    switch (selector)
    {
    case SEC:
        return cast(RTC(SECONDS));
    case MIN:
        return cast(RTC(MINUTES));
    case HOUR:
        return cast(RTC(HOURS)) + TIME_ZONE;
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