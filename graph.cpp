#include "graph.h"

Vertex::Vertex() {                            //конструктор
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

void Vertex::set_color(int с) {
	color = с;
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

void Vertex::add_colored_neighbor(int c) {    //додати зайнятий сусідами колір
	for (int i = 0; i < edges; i++) {         //прохід по іншим сусідам
		if (neighbors[i]->get_color() != c)   //якщо новий зайнятий колір-параметр ще не зустрічався серед сусідів:
			colored_neighbors++;              //збільшити кількість зайнятих кольорів
	}
}

Algorithm::Algorithm(int n) {                 //констуктор
	vertices = new Vertex[n];                 //створення динамічного масиву вершин графа
	v_size = n;                               //збереження кількості вершин
}

Algorithm::~Algorithm() {                     //деструктор
	delete[]vertices;                         
}

void Algorithm::enter_vertices(bool** matrix) {                               //внесення даних про вершини
	for (int i = 0; i < v_size; i++) {
		for (int j = 0; j < v_size; j++) {
			if (matrix[i][j])                                                 //якщо значення комірки true (тобто 1), то вершини з'єднані
				vertices[i].add_neighbor(vertices + j);                     
		}
		vertices[i].set_number(i + 1);             
	}
}

void Algorithm::save_data() {                                                 //виведення даних у файл
	ofstream OutFile("testing.txt", ios::app);                                
	for (int i = 0; i < v_size; ++i) {                                     
		OutFile << "Vertex " << vertices[i].get_number() << "\n";         
		OutFile << "Amount of neighbors: " << vertices[i].get_edges() << "\n";
		OutFile << "Color: " << vertices[i].get_color() + 1 << "\n";     
	}
	OutFile.close();
}

void Algorithm::paint(int i, int& change_c, bool change = true) {   //фарбування вершини
	int free_color = 0;                                             //вільний колір
	bool found_color = false;                                       //чи знайдено вільний колір
	int j = 0;                                                      //номер кольору
	while (j < v_size && !found_color) {                            //перегляд кольорів
		if (change)
			change_c++;//інкрементація статистичних даних щодо кількості змін кольору загалом
		found_color = true;                                        
		for (int x = 0; x < vertices[i].get_edges(); ++x) {         //переглядаємо усіх суміжних вершин
			if (vertices[i].neighbors[x]->get_color() == j)         //якщо колір зайнятий
				found_color = false;                                //колір не підходить
		}
		free_color = j;                                             //потрібний колір
		j++;
	}
	if (change)
		vertices[i].set_color(free_color);     
	else
		change_c = free_color;    
}

void Algorithm::save_colors() {//запис порядку кольорів для графічного розфарбування
	ofstream file( "colors.txt");
	for (int i = 0; i < v_size; ++i) {
		int c = vertices[i].get_color();
		file << c << ' ';
	}
	file.close();                               
}

MRV::MRV(int n): Algorithm(n) {}	

void MRV::coloring() {                                            //розфарбування MRV
	vector<int> nums;                                             //вектор з номерами нерозфарбованих вершин
	int calls = 0;                                                //лічильник рекурсій
	int changing_less = 0;                                        //лічильник зміни вершини, обрана як найконфліктніша
	int changing_color = 0;                                       //лічильник зміни кольору
	for (int i = 0; i < v_size; ++i) {
		nums.push_back(i);                                        //заповнення вектору
	}
	ofstream file("Statistics.txt");
	file << "MRV.\nRange of colored vertexes is next:\n";         
	file.close();
	recursive(nums, calls, changing_less, changing_color);  //викликаємо рекурсію для нерозфарбованих вершин
	ofstream f("Statistics.txt", ios::app);                
	f << "Amount of recurses: " << calls << "\nAmount of times we changed vertex choice: " << changing_less;
	f << "\nAmount of times we changed the color to try: " << changing_color << "\n";
	f.close();
}

void MRV::recursive(vector<int>& nums, int& calls, int& change, int& change_c) { //рекурсивне вирішення
	calls++;                                     //інкрементуємо кількість рекурсивних викликів
	ofstream file("Statistics.txt", ios::app);  
	if (nums.size() == 1) {                      //якщо вершина для розгляду одна
		change++;                              
		paint(nums[0], change_c);           
		file << "Vertex " << nums[0] + 1 << "\n";
		return;                                  //виходимо із функції
	}
	else {
		int less_c = 0;                          //беремо мінімальний номер вершини розфарбування
		change++;                               
		for (int i = 1; i < nums.size(); i++) {
			if (vertices[nums[i]].get_colored() > vertices[nums[less_c]].get_colored()) { //за кількістю сусідніх кольорів
				less_c = i;                      //якщо вершина має більше, задаємо її як потенційний вибір
				change++;               
			}
		}
		int needed_amount = vertices[nums[less_c]].get_edges(); //кількість сусідів обраної вершини, яку фарбуватимемо
		int needed_color;                                       //колір, у який фарбуватимемо
		paint(nums[less_c], needed_color, false);              
		for (int i = 0; i < needed_amount; i++) {             
			vertices[nums[less_c]].neighbors[i]->add_colored_neighbor(needed_color);
		}
		paint(nums[less_c], change_c);                        //фарбуємо вершину
		file << "Vertex " << nums[less_c] + 1 << "-> ";         
		nums.erase(nums.begin() + less_c);                    //видалення з розгляду розфарбованої вершини
		file.close();                                        
		recursive(nums, calls, change, change_c);  
	}
}

Degree::Degree(int n) :Algorithm(n) {}         //конструктор
void Degree::coloring() {                      
	vector<int> nums;                          //вектор з номерами нерозфарбованих вершин у масиві
	for (int i = 0; i < v_size; ++i) {
		nums.push_back(i);                     //заповнення вектору
	}
	ofstream file("Statistics.txt");          
	file << "Degree.\nRange of colored vertexes is next:\n";
	file.close();                             
	int calls = 0;                             //скільки разів спрацьовує рекурсія
	int changing_max = 0;                      //скільки разів змінюється вершина, обрана як вершина з найбільшим степенем
	int changing_color = 0;                    //скільки разів програма обирала колір для перевірки, чи він підходить
	recursive(nums, calls, changing_max, changing_color);//рекурсія для нерозфарбованих вершин
	ofstream f("Statistics.txt", ios::app);   
	f << "Amount of recurses: " << calls << "\nAmount of times we changed vertex choice: " << changing_max;
	f << "\nAmount of times we changed the color to try: " << changing_color << "\n";
	f.close();                               
}
 
void Degree::recursive(vector<int>& nums, int& calls, int& change, int& change_c) { 
	calls++;                                  
	ofstream file("Statistics.txt", ios::app);
	if (nums.size() == 1) {                    //якщо вершина для розгляду одна
		change++;                              
		paint(nums[0], change_c);           
		file << "Vertex " << nums[0] + 1 << "\n";   
		return;                                //виходимо із функції
	}
	int max = 0;
	change++;                                               
	for (int i = 1; i < nums.size(); ++i) {
		if (vertices[nums[i]].get_edges() > vertices[nums[max]].get_edges()) {//за кількістю сусідів
			max = i;                                         //якщо вершина має більше, задаємо її як потенційний вибір
			change++;                                       
		}
	}
	paint(nums[max], change_c);                            //розфарбування вершини
	file << "Vertex " << nums[max] + 1 << "-> ";          
	nums.erase(nums.begin() + max);                          //видалення з розгляду розфарбованої вершини
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
	for (int i = 0; i < v_size; ++i) {             //вершини фарбуватимуться по порядку
		if (i == v_size - 1)                            //якщо остання вершина, вкінці не буде виведено стрілку
			Statistics << "Vertex " << i + 1 << "\n"; 
		else
			Statistics << "Vertex " << i + 1 << "->";
		paint(i, changing_color);                    //обрання для конкретної вершини кольору для фарбування
	}
	Statistics << "Amount of times we changed the color to try: " << changing_color << "\n";
	Statistics.close();
}