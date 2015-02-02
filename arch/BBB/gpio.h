/* 
 * https://github.com/mrshu/GPIOlib
 * Copyright (c) 2011, Copyright (c) 2011 mr.Shu
 * All rights reserved. 
 * 
 * Modified on 24 June 2012, 11:06 AM
 * File:   gpio.h
 * Author: purinda (purinda@gmail.com)
 * 
 */

#ifndef H
#define	H

#include <cstdio>

class GPIO {
public:

	/* Constants */
	static const int DIRECTION_OUT = 1;
	static const int DIRECTION_IN = 0;
	
	static const int OUTPUT_HIGH = 1;
	static const int OUTPUT_LOW = 0;
		
	GPIO();
	
	/**
	 * 
     * @param port
     * @param DDR
     */
	static void open(int port, int DDR);
	/**
	 * 
     * @param port
     */
	static void close(int port);
	/**
	 * 
     * @param port
     * @param value
     */
	static int read(int port);
	/**
	* 
	* @param port
	* @param value
	*/	
	static void write(int port,int value);	
	
	virtual ~GPIO();
	
private:

};

#endif	/* H */

