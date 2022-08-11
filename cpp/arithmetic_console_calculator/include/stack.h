#pragma once

#include <cassert> 
#include <iostream>
 
#include <iomanip> 
 
template <typename T>
class Stack
{
private:
    T *stackPtr;                      
    const int size;                   
    int top;                          
public:
    Stack(int = 10);                 
/*    Stack(const Stack<T> &);*/          
    ~Stack();                         
 
    inline void push(const T & );     
    inline T pop();                   
    inline void printStack();         
    inline const T &Peek() const; 
    inline int getStackSize() const;  
    inline T *getPtr() const;         
    inline int getTop() const;        
};
 
template <typename T>
Stack<T>::Stack(int maxSize) :
    size(maxSize) 
{
    stackPtr = new T[size]; 
    top = -1; 
}
 
//template <typename T>
//Stack<T>::Stack(const Stack<T> & otherStack) :
//    size(otherStack.getStackSize()) 
//{
//    stackPtr = new T[size]; 
//    top = otherStack.getTop();
// 
//    for(int ix = 0; ix < top; ix++)
//        stackPtr[ix] = otherStack.getPtr()[ix];
//}
 
template <typename T>
Stack<T>::~Stack()
{
    delete [] stackPtr; 
}
 

template <typename T>
inline void Stack<T>::push(const T &value)
{
	top++;
	if (top>=size)
		throw "Stack overflow";
	stackPtr[top] = value; 

}
 
template <typename T>
inline T Stack<T>::pop()
{ 
	if (top<0)
		throw "Stack is already empty"; 
	--top;
	return stackPtr[top+1];
}
 

template <class T>
inline const T &Stack<T>::Peek() const
{
  return stackPtr[top]; 
}

//template <typename T>
//inline void Stack<T>::printStack()
//{
//    for (int ix = top - 1; ix >= 0; ix--)
//        cout << "|" << setw(4) << stackPtr[ix] << endl;
//}
 
template <typename T>
inline int Stack<T>::getStackSize() const
{
    return size;
}
 
//// вернуть указатель на стек (для конструктора копирования)
//template <typename T>
//inline T *Stack<T>::getPtr() const
//{
//    return stackPtr;
//}
 
template <typename T>
inline int Stack<T>::getTop() const
{
    return top;
}
