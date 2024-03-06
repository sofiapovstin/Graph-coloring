#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	GraphColoring::MyForm form;
	Application::Run(% form);
	return 0;
}

System::Void GraphColoring::MyForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	need_color = false;
	Matrix->ColumnCount = 1;    
	Matrix->RowCount = 1;    
	Matrix->AutoResizeColumns(); //корегує ширину стовпців 
	ofstream file("testing.txt", ios::trunc);
	file.close();
	return System::Void();
}

System::Void GraphColoring::MyForm::numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	int dimension = Convert::ToInt32(Dimension->Value);
	Matrix->ColumnCount = dimension;
	Matrix->RowCount = dimension;
	Dimension->Value = Convert::ToDecimal(dimension);
	Matrix->AutoResizeColumns();
	Picture->Invalidate();//зміна малюнку
	return System::Void();
}

System::Void GraphColoring::MyForm::Matrix_Click(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	if (Matrix->CurrentCell->ColumnIndex != Matrix->CurrentCell->RowIndex) {                    //якщо не головна діагональ
		if (Convert::ToInt32(Matrix->CurrentCell->Value) == 1) {                                //якщо зараз значення дорівнює 1
			Matrix->CurrentCell->Value = 0;                                                     //змінити на 0 дану комірку
			Matrix[Matrix->CurrentCell->RowIndex, Matrix->CurrentCell->ColumnIndex]->Value = 0; //змінити на 0 симетричну комірку
		}
		else {                                                                                  //якщо зараз значення дорівнює 0
			Matrix->CurrentCell->Value = 1;                                                     //змінити на 1 дану комірку
			Matrix[Matrix->CurrentCell->RowIndex, Matrix->CurrentCell->ColumnIndex]->Value = 1; //змінити на 1 симетричну комірку
		}
	}

	Picture->Invalidate();
	return System::Void();
}

System::Void GraphColoring::MyForm::Random_Click(System::Object^ sender, System::EventArgs^ e)
{
	int x;
	int dimension = Convert::ToInt32(Dimension->Value);
	Random^ rndGen = gcnew Random();
	if (dimension != 1) {
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				if (i == j) {
					Matrix[i, j]->Value = 0;
				}
				else {
					x = rndGen->Next(0, 2);
					Matrix[i, j]->Value = x;
					Matrix[j, i]->Value = x;
				}
			}
		}
	}
	
	Picture->Invalidate();
	return System::Void();
}

System::Void GraphColoring::MyForm::Start_Click(System::Object^ sender, System::EventArgs^ e)
{
	int dimension = Convert::ToInt32(Dimension->Value);
	bool** matrix = new bool* [dimension];
	for (int i = 0; i < dimension; ++i) {
		matrix[i] = new bool[dimension];
	}
	save_matrix(matrix, dimension);  
	solving(matrix, dimension);
	delete_matrix(matrix, dimension);

	Picture->Invalidate();
	return System::Void();
}

System::Void GraphColoring::MyForm::Picture_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	int colors[10][3] = { {255, 0, 30}, {2, 247, 60}, {14, 17, 227},
		{230, 250, 12}, {250, 7, 153}, {7, 226, 250}, {163, 10, 48},
		{36, 138, 77},	{255, 148, 8}, {163, 33, 255} };

	int dimension = Convert::ToInt32(Dimension->Value);
	double dif = 2 * 3.14 / dimension;//кут зсуву
	TPoint points[10];//Масив точок
	int numbers[10]{};//Масив номерів кольору
	System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 12);
	Pen^ myPen = gcnew Pen(Color::Black);
	SolidBrush^ vertex = gcnew SolidBrush(Color::Black);
	SolidBrush^ edge = gcnew SolidBrush(Color::Black);
	int x0 = 130, y0 = 130;

	double angle = 0;//початковий кут відхилення
	if (need_color) {                                                     
		ifstream f("colors.txt", ios::binary);//відкрити файл з даними про кольори
		int number;                                                       
		for (int i = 0; i < dimension; ++i) {
			f >> number;
			numbers[i] = number;//додання у масив
		}
		f.close();
	}
	if (dimension == 1) {                                                    
		String^ str = "V1";                                               
		e->Graphics->DrawEllipse(myPen, x0, y0, 20, 20);//намалювати вершину
		e->Graphics->FillEllipse(vertex, x0, y0, 20, 20);//заповнити чорним кольором
		e->Graphics->DrawString(str, font, edge, Convert::ToSingle(x0 + 20), Convert::ToSingle(y0 + 20));
		if (need_color) {                                             
			vertex = gcnew SolidBrush(Color::FromArgb(colors[numbers[0]][0], colors[numbers[0]][1], colors[numbers[0]][2]));//задання нового кольору
			e->Graphics->FillEllipse(vertex, x0, y0, 20, 20);    //зафарбування новим кольором
		}
		TPoint p(x0 + 10, y0 + 10);  //створення об'єкту з координатами центру кола як координат вершини
		points[0] = p;                //додавання до масиву
	}
	else {
		for (int i = 0; i < dimension; ++i) {
			String^ str = "V" + Convert::ToString(i + 1);                 
			int x = x0 + 90 * cos(angle);                                 
			int y = y0 + 90 * sin(angle);                                 
			e->Graphics->DrawEllipse(myPen, x, y, 20, 20);               
			e->Graphics->FillEllipse(vertex, x, y, 20, 20);        
			e->Graphics->DrawString(str, font, edge, Convert::ToSingle(x + 20), Convert::ToSingle(y + 20));
			angle += dif;//змінити кут на різницю, задану відповідно до кількості
			if (need_color) {                                          
				vertex = gcnew SolidBrush(Color::FromArgb(colors[numbers[i]][0], colors[numbers[i]][1], colors[numbers[i]][2]));
				e->Graphics->FillEllipse(vertex, x, y, 20, 20); 
			}
			TPoint p(x + 10, y + 10);   //створення об'єкту з координатами центру кола як координат вершини
			points[i] = p;         //додавання до масиву
		}
	}
	for (int i = 0; i < dimension - 1; ++i) {
		for (int j = i + 1; j < dimension; ++j) {
			if (Convert::ToBoolean(Matrix[i, j]->Value)) {     //якщо є з'єднання вершин(true)
				e->Graphics->DrawLine(myPen, points[i].get_x(), points[i].get_y(), points[j].get_x(), points[j].get_y()); //намалювати пряму між ними
			}
		}
	}
	need_color = false;
	return System::Void();
}

void GraphColoring::MyForm::save_matrix(bool** matrix, int dimension)
{
	ofstream file("testing.txt", ios::app);
	for (int i = 0; i < dimension; ++i) {
		for (int j = 0; j < dimension; ++j) {
			matrix[i][j] = Convert::ToBoolean(Matrix[i, j]->Value); //заповнення матриці
			file << matrix[i][j] << " ";                         //збереження матриці у файл
		}
		file << endl;
	}
	file.close();
}

void GraphColoring::MyForm::solving(bool** matrix, int dimension)
{
	if (GreedyButton->Checked) {
		need_color = true;
		ofstream file("testing.txt", ios::app); 
		file << "Greedy:\n";
		file.close();
		Greedy solution(dimension);
		solution.enter_vertices(matrix);
		solution.coloring();
		solution.save_data();
		StreamReader^ file1 = File::OpenText("Statistics.txt");
		Result->Text = file1->ReadToEnd();                         //читання з файлу у вікно інтерфейсу
		file1->Close();
		solution.save_colors();
	}
	else if (MRVButton->Checked) {
		need_color = true;
		ofstream file("testing.txt", ios::app);
		file << "MRV:\n";
		file.close();
		MRV solution(dimension);
		solution.enter_vertices(matrix);
		solution.coloring();
		solution.save_data();
		StreamReader^ file1 = File::OpenText("Statistics.txt"); 
		Result->Text = file1->ReadToEnd();                       
		file1->Close();                                          
		solution.save_colors();
	}
	else if (DegreeButton->Checked) {
		need_color = true;
		ofstream file("testing.txt", ios::app);                
		file << "Degree:\n";                                     
		file.close();
		Degree solution(dimension);
		solution.enter_vertices(matrix);
		solution.coloring();
		solution.save_data();
		StreamReader^ file1 = File::OpenText("Statistics.txt");    
		Result->Text = file1->ReadToEnd();                         
		file1->Close();                                             
		solution.save_colors();
	}
	else {
		Result->Text = "Choose method for coloring!";
	}
}

void GraphColoring::MyForm::delete_matrix(bool** matrix, int dimension)
{
	for (int i = 0; i < dimension; ++i)
		delete[]matrix[i];
	delete[]matrix;
}
