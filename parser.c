#include <string.h>
#include "parser.h"

void parse_GPGGA(char *sentence)
{
    char *ptr = sentence;
    int field = 0;
    int idx = 0;

    while(*ptr)
    {
        if(*ptr == ',')
        {
            field++;
            idx = 0;
            ptr++;
            continue;
        }

        if(field == 2 && idx < 11)
        {
            latitude[idx++] = *ptr;
            latitude[idx] = '\0';
        }
        else if(field == 6)
        {
            fix_status = *ptr;
        }

        ptr++;
    }
}

void parse_GPRMC(char *sentence)
{
    char *ptr = sentence;
    int field = 0;
    int idx = 0;

    while(*ptr)
    {
        if(*ptr == ',')
        {
            field++;
            idx = 0;
            ptr++;
            continue;
        }

        // Field 2: Status (A=active/valid, V=void/invalid)
        if(field == 2)
        {
            fix_status = *ptr;
        }
        // Field 3: Latitude (ddmm.mmmm)
        else if(field == 3 && idx < 11)
        {
            latitude[idx++] = *ptr;
            latitude[idx] = '\0';
        }
        // Field 5: Longitude (dddmm.mmmm)
        else if(field == 5 && idx < 11)
        {
            longitude[idx++] = *ptr;
            longitude[idx] = '\0';
        }

        ptr++;
    }
}
