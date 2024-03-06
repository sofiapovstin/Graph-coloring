#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Vertex {
	int edges;                       //кількість ребер
	int color;                       //Номер кольору вершини
	int num;                         //номер вершини
	int colored_neighbors;           //кількість зафарбованих суміжних вершин (використовується, якщо обирається MRV)
public:
	Vertex** neighbors;              //масив покажчиків на вершини, суміжні даній, у загальному масиві самих вершин
	Vertex();                        
	void add_neighbor(Vertex*);      //додати покажчик-сусіда, що переданий як параметр, для даної вершини
	void set_color(int);             //задати колір
	void set_number(int);            //задати номер вершини
	int get_color();                 //отримати значення кольору
	int get_edges();                 //отримати значення кількості ребер сполучених вершиною
	int get_number();                //отримати значення номеру
	int get_colored();               //отримати кількість зайнятих сусідами кольорів. Використовується для MRV
	void add_colored_neighbor(int);  //додати зайнятий колір, якщо ще немає сусіда з таким кольором. Для MRV
};

class Algorithm {                    //абстрактний класс для розфарбування
protected:
	Vertex* vertices;                //покажчик на загальний масив вершин графа
	int v_size;                      //розмір масиву(кількість вершин графа)
public:
	Algorithm(int);                  //конструктор з параметром(кількістю вершин)
	~Algorithm();                    //деструктор
	void enter_vertices(bool**);     //внесення вершин у масив відповідно до матриці, переданої як параметр
	virtual void coloring() = 0;     //абстрактна функція, що фарбує граф
	void save_data();                //збереження даних у файл
	void paint(int, int&, bool);     //шукає колір для розфарбування обраної, та переданої як перший параметр, вершини
	void save_colors();              //запис у файл порядок кольорів(використовується для графічного розфарбування)
};

class Greedy : public Algorithm {
public:
	Greedy(int);                     //конструктор
	void coloring();                 //реалізація абстрактного методу базового класу
};

class MRV : public Algorithm {
public:
	MRV(int);                                      //конструктор
	void coloring();                               //реалізація абстрактного методу базового класу
	void recursive(vector<int>&, int&, int&, int&);//рекурсивний вибір наступної для фарбування вершини
};

class Degree : public Algorithm {
public:
	Degree(int);                                    //конструктор
	void coloring();                                //реалізація абстрактного методу базового класу
	void recursive(vector<int>&, int&, int&, int&); //рекурсивний вибір наступної для фарбування вершини

};

class TPoint {                      //вершини на графічному представленні
	int x, y;                       //координати
public:
	TPoint();
	TPoint(int, int);               //конструктор, що приймає координати як параметри
	int get_x();                    //отримати х
	int get_y();                    //отримати у
};