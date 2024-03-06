#include "graph.h"

Vertex::Vertex() {                            //�����������
	edges = 0;                                
	color = -1;
	num = 0;
	colored_neighbors = 0;
	neighbors = nullptr;
}

void Vertex::add_neighbor(Vertex* neighbor) {
	Vertex** temp = new Vertex * [edges + 1];
	for (int i = 0; i < edges; ++i) {
		temp[i] = neighbors[i];
	}
	temp[edges] = neighbor;
	delete[] neighbors;
	neighbors = temp;
	edges++;
}

void Vertex::set_color(int �) {
	color = �;
}

void Vertex::set_number(int n) {
	num = n;
}

int Vertex::get_color() {
	return color;
}

int Vertex::get_edges() {
	return edges;
}

int Vertex::get_number(){
	return num;
}

int Vertex::get_colored() {
	return colored_neighbors;
}

void Vertex::add_colored_neighbor(int c) {    //������ �������� ������� ����
	for (int i = 0; i < edges; i++) {         //������ �� ����� ������
		if (neighbors[i]->get_color() != c)   //���� ����� �������� ����-�������� �� �� ���������� ����� �����:
			colored_neighbors++;              //�������� ������� �������� �������
	}
}

Algorithm::Algorithm(int n) {                 //����������
	vertices = new Vertex[n];                 //��������� ���������� ������ ������ �����
	v_size = n;                               //���������� ������� ������
}

Algorithm::~Algorithm() {                     //����������
	delete[]vertices;                         
}

void Algorithm::enter_vertices(bool** matrix) {                               //�������� ����� ��� �������
	for (int i = 0; i < v_size; i++) {
		for (int j = 0; j < v_size; j++) {
			if (matrix[i][j])                                                 //���� �������� ������ true (����� 1), �� ������� �'�����
				vertices[i].add_neighbor(vertices + j);                     
		}
		vertices[i].set_number(i + 1);             
	}
}

void Algorithm::save_data() {                                                 //��������� ����� � ����
	ofstream OutFile("testing.txt", ios::app);                                
	for (int i = 0; i < v_size; ++i) {                                     
		OutFile << "Vertex " << vertices[i].get_number() << "\n";         
		OutFile << "Amount of neighbors: " << vertices[i].get_edges() << "\n";
		OutFile << "Color: " << vertices[i].get_color() + 1 << "\n";     
	}
	OutFile.close();
}

void Algorithm::paint(int i, int& change_c, bool change = true) {   //���������� �������
	int free_color = 0;                                             //������ ����
	bool found_color = false;                                       //�� �������� ������ ����
	int j = 0;                                                      //����� �������
	while (j < v_size && !found_color) {                            //�������� �������
		if (change)
			change_c++;//������������� ������������ ����� ���� ������� ��� ������� �������
		found_color = true;                                        
		for (int x = 0; x < vertices[i].get_edges(); ++x) {         //����������� ��� ������� ������
			if (vertices[i].neighbors[x]->get_color() == j)         //���� ���� ��������
				found_color = false;                                //���� �� ��������
		}
		free_color = j;                                             //�������� ����
		j++;
	}
	if (change)
		vertices[i].set_color(free_color);     
	else
		change_c = free_color;    
}

void Algorithm::save_colors() {//����� ������� ������� ��� ���������� �������������
	ofstream file( "colors.txt");
	for (int i = 0; i < v_size; ++i) {
		int c = vertices[i].get_color();
		file << c << ' ';
	}
	file.close();                               
}

MRV::MRV(int n): Algorithm(n) {}	

void MRV::coloring() {                                            //������������� MRV
	vector<int> nums;                                             //������ � �������� ��������������� ������
	int calls = 0;                                                //�������� �������
	int changing_less = 0;                                        //�������� ���� �������, ������ �� �������������
	int changing_color = 0;                                       //�������� ���� �������
	for (int i = 0; i < v_size; ++i) {
		nums.push_back(i);                                        //���������� �������
	}
	ofstream file("Statistics.txt");
	file << "MRV.\nRange of colored vertexes is next:\n";         
	file.close();
	recursive(nums, calls, changing_less, changing_color);  //��������� ������� ��� ��������������� ������
	ofstream f("Statistics.txt", ios::app);                
	f << "Amount of recurses: " << calls << "\nAmount of times we changed vertex choice: " << changing_less;
	f << "\nAmount of times we changed the color to try: " << changing_color << "\n";
	f.close();
}

void MRV::recursive(vector<int>& nums, int& calls, int& change, int& change_c) { //���������� ��������
	calls++;                                     //������������ ������� ����������� �������
	ofstream file("Statistics.txt", ios::app);  
	if (nums.size() == 1) {                      //���� ������� ��� �������� ����
		change++;                              
		paint(nums[0], change_c);           
		file << "Vertex " << nums[0] + 1 << "\n";
		return;                                  //�������� �� �������
	}
	else {
		int less_c = 0;                          //������ ��������� ����� ������� �������������
		change++;                               
		for (int i = 1; i < nums.size(); i++) {
			if (vertices[nums[i]].get_colored() > vertices[nums[less_c]].get_colored()) { //�� ������� ������ �������
				less_c = i;                      //���� ������� �� �����, ������ �� �� ����������� ����
				change++;               
			}
		}
		int needed_amount = vertices[nums[less_c]].get_edges(); //������� ����� ������ �������, ��� �������������
		int needed_color;                                       //����, � ���� �������������
		paint(nums[less_c], needed_color, false);              
		for (int i = 0; i < needed_amount; i++) {             
			vertices[nums[less_c]].neighbors[i]->add_colored_neighbor(needed_color);
		}
		paint(nums[less_c], change_c);                        //������� �������
		file << "Vertex " << nums[less_c] + 1 << "-> ";         
		nums.erase(nums.begin() + less_c);                    //��������� � �������� ������������ �������
		file.close();                                        
		recursive(nums, calls, change, change_c);  
	}
}

Degree::Degree(int n) :Algorithm(n) {}         //�����������
void Degree::coloring() {                      
	vector<int> nums;                          //������ � �������� ��������������� ������ � �����
	for (int i = 0; i < v_size; ++i) {
		nums.push_back(i);                     //���������� �������
	}
	ofstream file("Statistics.txt");          
	file << "Degree.\nRange of colored vertexes is next:\n";
	file.close();                             
	int calls = 0;                             //������ ���� ��������� �������
	int changing_max = 0;                      //������ ���� ��������� �������, ������ �� ������� � ��������� ��������
	int changing_color = 0;                    //������ ���� �������� ������� ���� ��� ��������, �� �� ��������
	recursive(nums, calls, changing_max, changing_color);//������� ��� ��������������� ������
	ofstream f("Statistics.txt", ios::app);   
	f << "Amount of recurses: " << calls << "\nAmount of times we changed vertex choice: " << changing_max;
	f << "\nAmount of times we changed the color to try: " << changing_color << "\n";
	f.close();                               
}
 
void Degree::recursive(vector<int>& nums, int& calls, int& change, int& change_c) { 
	calls++;                                  
	ofstream file("Statistics.txt", ios::app);
	if (nums.size() == 1) {                    //���� ������� ��� �������� ����
		change++;                              
		paint(nums[0], change_c);           
		file << "Vertex " << nums[0] + 1 << "\n";   
		return;                                //�������� �� �������
	}
	int max = 0;
	change++;                                               
	for (int i = 1; i < nums.size(); ++i) {
		if (vertices[nums[i]].get_edges() > vertices[nums[max]].get_edges()) {//�� ������� �����
			max = i;                                         //���� ������� �� �����, ������ �� �� ����������� ����
			change++;                                       
		}
	}
	paint(nums[max], change_c);                            //������������� �������
	file << "Vertex " << nums[max] + 1 << "-> ";          
	nums.erase(nums.begin() + max);                          //��������� � �������� ������������ �������
	file.close();                                           
	recursive(nums, calls, change, change_c);       
}

TPoint::TPoint()
{
	x = 0;
	y = 0;
}

TPoint::TPoint(int x0, int y0) {
	x = x0;
	y = y0;
}

int TPoint::get_x() {
	return x;
}

int TPoint::get_y() {
	return y;
}

Greedy::Greedy(int n) :Algorithm(n) {}

void Greedy::coloring()
{
	ofstream Statistics("Statistics.txt");
	Statistics << "Greedy. Range of colored vertexes is next:\n";
	int changing_color = 0;
	for (int i = 0; i < v_size; ++i) {             //������� ��������������� �� �������
		if (i == v_size - 1)                            //���� ������� �������, ����� �� ���� �������� ������
			Statistics << "Vertex " << i + 1 << "\n"; 
		else
			Statistics << "Vertex " << i + 1 << "->";
		paint(i, changing_color);                    //������� ��� ��������� ������� ������� ��� ����������
	}
	Statistics << "Amount of times we changed the color to try: " << changing_color << "\n";
	Statistics.close();
}