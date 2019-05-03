#ifndef MYSWAP_H
#define MYSWAP_H
/*///////////////////////////////
	Author: Jacob Vanderkarr
	Date: 4/19/19

	File: MySwap.h

	Purpose: Implementation of 
		templated swap function
*////////////////////////////////
template <typename T>
void Swap(T & first, T & second)
{
	T temp = first;
	first = second;
	second = temp;
}
#endif // !MYSWAP_H