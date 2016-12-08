    
/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2014-2016  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef CONFIG_H
#define	CONFIG_H

#if defined(__SDCC_PIC18F4620)
#define _18F4620
#endif

#if defined(_18F452)
#include"config_452.h"
#endif
#if defined(_18F4520)
#include"config_4520.h"
#endif
#if defined(_18F4620)  
#include"config_4620.h"
#endif
#if defined(_18F4550)
#include"config_4550.h"
#endif
#if defined(_16F877A)
#include"config_877A.h"
#endif
#if defined(_16F777)
#include"config_777.h"
#endif
#if defined(_18F45K50)
#include"config_45k50.h"
#endif

#endif	/* CONFIG_H */
