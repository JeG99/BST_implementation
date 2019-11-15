#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "BST.h"

int main() {

  BST arbol1;

  arbol1.add(4);
  arbol1.add(1);
  arbol1.add(6);
  arbol1.add(2);
  arbol1.add(9);
  arbol1.add(7);
  arbol1.add(5);
  arbol1.add(-1);
  arbol1.add(3);

/*
  BST arbolon(arbol);
  arbol.remove(6);
  arbol.add(12);
  
  arbol.add(-2);
  arbol.add(8);
  arbol.add(-2);
  arbol.add(6);

  BST arbolVacio;
  arbolVacio.add(3);

  BST copiaArbol(arbol);
  std::cout << std::boolalpha << (copiaArbol == arbolon) << '\n';

  BST copiaCopiaArbol(copiaArbol);
  copiaCopiaArbol.add(46);
*/
  
  BST arbol2;
  arbol2.add(4);
  arbol2.add(1);
  arbol2.add(6);
  arbol2.add(2);
  arbol2.add(9);
  arbol2.add(7);
  arbol2.add(5);
  arbol2.add(-1);
  arbol2.add(3);

  arbol2.add(12);
  arbol2.remove(6);
  arbol2.add(8);
  std::cout << std::boolalpha << (arbol1 == arbol2) << '\n' << arbol2.maxWidth() << '\n';  

  return 0;
}