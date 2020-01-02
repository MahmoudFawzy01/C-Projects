/*
 *  BIT_MATH.H
 *
 *  Created on: july 8, 2019
 *  
 *	Author: Mahmoud Fawzy
 */
 
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BITIT(VAR,BIT_NUMBER)	(VAR) |= (1<<BIT_NUMBER)
#define CLR_BIT(VAR,BIT_NUMBER)	(VAR) &= ~(1<<BIT_NUMBER)
#define TOGGLE_BIT(VAR,BIT_NUMBER)	(VAR) ^= (1<<BIT_NUMBER)
#define ASSIGN_BIT(VAR,BIT_NUMBER,VALUE) 	(VAR) = ((VAR&(~(1<<BIT_NUMBER)))|(VALUE<<BIT_NUMBER))
#define GET_BIT(VAR,BIT_NUMBER) 			((VAR>>BIT_NUMBER) & 0x01)

#endif /* BIT_MATH_H_ */