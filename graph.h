#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Vertex {
	int edges;                       //������� �����
	int color;                       //����� ������� �������
	int num;                         //����� �������
	int colored_neighbors;           //������� ������������ ������� ������ (���������������, ���� ��������� MRV)
public:
	Vertex** neighbors;              //����� ��������� �� �������, ����� ����, � ���������� ����� ����� ������
	Vertex();                        
	void add_neighbor(Vertex*);      //������ ��������-�����, �� ��������� �� ��������, ��� ���� �������
	void set_color(int);             //������ ����
	void set_number(int);            //������ ����� �������
	int get_color();                 //�������� �������� �������
	int get_edges();                 //�������� �������� ������� ����� ���������� ��������
	int get_number();                //�������� �������� ������
	int get_colored();               //�������� ������� �������� ������� �������. ��������������� ��� MRV
	void add_colored_neighbor(int);  //������ �������� ����, ���� �� ���� ����� � ����� ��������. ��� MRV
};

class Algorithm {                    //����������� ����� ��� �������������
protected:
	Vertex* vertices;                //�������� �� ��������� ����� ������ �����
	int v_size;                      //����� ������(������� ������ �����)
public:
	Algorithm(int);                  //����������� � ����������(������� ������)
	~Algorithm();                    //����������
	void enter_vertices(bool**);     //�������� ������ � ����� �������� �� �������, �������� �� ��������
	virtual void coloring() = 0;     //���������� �������, �� ����� ����
	void save_data();                //���������� ����� � ����
	void paint(int, int&, bool);     //���� ���� ��� ������������� ������, �� �������� �� ������ ��������, �������
	void save_colors();              //����� � ���� ������� �������(��������������� ��� ���������� �������������)
};

class Greedy : public Algorithm {
public:
	Greedy(int);                     //�����������
	void coloring();                 //��������� ������������ ������ �������� �����
};

class MRV : public Algorithm {
public:
	MRV(int);                                      //�����������
	void coloring();                               //��������� ������������ ������ �������� �����
	void recursive(vector<int>&, int&, int&, int&);//����������� ���� �������� ��� ���������� �������
};

class Degree : public Algorithm {
public:
	Degree(int);                                    //�����������
	void coloring();                                //��������� ������������ ������ �������� �����
	void recursive(vector<int>&, int&, int&, int&); //����������� ���� �������� ��� ���������� �������

};

class TPoint {                      //������� �� ���������� ������������
	int x, y;                       //����������
public:
	TPoint();
	TPoint(int, int);               //�����������, �� ������ ���������� �� ���������
	int get_x();                    //�������� �
	int get_y();                    //�������� �
};