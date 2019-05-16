/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "GeneratorConfig.h"

#define MYSERIAL 							Serial
#define FIXFLOAT(f) 						(f + 0.00001)

#define SERIAL_CHAR(x) 						((void)MYSERIAL.write(x))
#define SERIAL_EOL() 						SERIAL_CHAR('\n')

#define SERIAL_PROTOCOLCHAR(x)              SERIAL_CHAR(x)
#define SERIAL_PROTOCOL(x)                  (MYSERIAL.print(x))
#define SERIAL_PROTOCOL_F(x,y)              (MYSERIAL.print(x,y))
#define SERIAL_PROTOCOLLN(x)                do{ MYSERIAL.print(x); SERIAL_EOL(); }while(0)

#define SERIAL_ECHO(x)                 		SERIAL_PROTOCOL(x)
#define SERIAL_ECHOLN(x)               		SERIAL_PROTOCOLLN(x)
#define SERIAL_ECHO_F(x,y)            	 	SERIAL_PROTOCOL_F(x,y)

#define SERIAL_ERROR(x)                		SERIAL_PROTOCOL(x)
#define SERIAL_ERRORLN(x)              		SERIAL_PROTOCOLLN(x)

#define SERIAL_PROTOCOLPAIR_F(pre, value)   SERIAL_PROTOCOLPAIR(pre, FIXFLOAT(value))
#define SERIAL_ECHOPAIR_F(pre,value)        SERIAL_ECHOPAIR(pre, FIXFLOAT(value))
#define SERIAL_ECHOLNPAIR_F(pre, value)     SERIAL_ECHOLNPAIR(pre, FIXFLOAT(value))

#endif // __SERIAL_H__