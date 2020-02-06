#include <stdio.h>
#include <stdarg.h>
#include "mod_lcd.h"
/*
void foo(char *fmt, ...) {

	va_list ap;
	int d;
    char c, *p, *s;
    va_start(ap, fmt);
    while (*fmt)
    	switch(*fmt++) {
    	case 's':            string
    		s = va_arg(ap, char *);
    		printf("string %s\n", s);
    		break;
    	case 'd':            int
    		d = va_arg(ap, int);
    		printf("int %d\n", d);
    		break;
    	case 'c':            char
    		 Aqui es necesaria una conversion forzada
    		 * * de tipos ya que va_arg solo toma tipos
    		 * totalmente `ascendidos'.
    		c = (char) va_arg(ap, char);
            printf("char %c\n", c);
            break;
    	}
    va_end(ap);
}*/

/*void lcdWrite(char *varinput,...){
	va_list ap;
	float varinput_float;
	uint16_t varinput_int16;
	uint32_t varinput_int32;
	uint64_t varinput_int64;
    char *varinput_string;
    va_start(ap, varinput);
    while (*varinput)
    	switch(*varinput++) {
       	case 'varinput_string':            string
       		varinput_string = va_arg(ap, char *);
        	break;
		case 'varinput_int16':            int
			varinput_int16 = va_arg(ap, int);
			break;
		case 'varinput_float':
			varinput_float = va_arg(ap, float);
			break;
        }
        va_end(ap);
 }*/
