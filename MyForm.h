#pragma once
#include "graph.h"
namespace GraphColoring {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::Threading;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^ GreedyButton;
	private: System::Windows::Forms::RadioButton^ MRVButton;
	private: System::Windows::Forms::RadioButton^ DegreeButton;
	private: System::Windows::Forms::RichTextBox^ Result;
	private: System::Windows::Forms::NumericUpDown^ Dimension;
	private: System::Windows::Forms::Label^ Label;
	private: System::Windows::Forms::DataGridView^ Matrix;
	private: System::Windows::Forms::GroupBox^ Choice;
	private: System::Windows::Forms::PictureBox^ Picture;
	private: System::Windows::Forms::Button^ Start;
	private: System::Windows::Forms::Button^ Generate;



	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->GreedyButton = (gcnew System::Windows::Forms::RadioButton());
			this->MRVButton = (gcnew System::Windows::Forms::RadioButton());
			this->DegreeButton = (gcnew System::Windows::Forms::RadioButton());
			this->Result = (gcnew System::Windows::Forms::RichTextBox());
			this->Dimension = (gcnew System::Windows::Forms::NumericUpDown());
			this->Label = (gcnew System::Windows::Forms::Label());
			this->Matrix = (gcnew System::Windows::Forms::DataGridView());
			this->Choice = (gcnew System::Windows::Forms::GroupBox());
			this->Picture = (gcnew System::Windows::Forms::PictureBox());
			this->Start = (gcnew System::Windows::Forms::Button());
			this->Generate = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Dimension))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Matrix))->BeginInit();
			this->Choice->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Picture))->BeginInit();
			this->SuspendLayout();
			// 
			// GreedyButton
			// 
			this->GreedyButton->AutoSize = true;
			this->GreedyButton->Font = (gcnew System::Drawing::Font(L"Rockwell", 12));
			this->GreedyButton->Location = System::Drawing::Point(23, 50);
			this->GreedyButton->Name = L"GreedyButton";
			this->GreedyButton->Size = System::Drawing::Size(123, 31);
			this->GreedyButton->TabIndex = 1;
			this->GreedyButton->TabStop = true;
			this->GreedyButton->Text = L"Greedy";
			this->GreedyButton->UseVisualStyleBackColor = true;
			// 
			// MRVButton
			// 
			this->MRVButton->AutoSize = true;
			this->MRVButton->Font = (gcnew System::Drawing::Font(L"Rockwell", 12));
			this->MRVButton->Location = System::Drawing::Point(23, 87);
			this->MRVButton->Name = L"MRVButton";
			this->MRVButton->Size = System::Drawing::Size(90, 31);
			this->MRVButton->TabIndex = 2;
			this->MRVButton->TabStop = true;
			this->MRVButton->Text = L"MRV";
			this->MRVButton->UseVisualStyleBackColor = true;
			// 
			// DegreeButton
			// 
			this->DegreeButton->AutoSize = true;
			this->DegreeButton->Font = (gcnew System::Drawing::Font(L"Rockwell", 12));
			this->DegreeButton->Location = System::Drawing::Point(24, 124);
			this->DegreeButton->Name = L"DegreeButton";
			this->DegreeButton->Size = System::Drawing::Size(122, 31);
			this->DegreeButton->TabIndex = 3;
			this->DegreeButton->TabStop = true;
			this->DegreeButton->Text = L"Degree";
			this->DegreeButton->UseVisualStyleBackColor = true;
			// 
			// Result
			// 
			this->Result->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->Result->Font = (gcnew System::Drawing::Font(L"Rockwell", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Result->Location = System::Drawing::Point(440, 548);
			this->Result->Name = L"Result";
			this->Result->Size = System::Drawing::Size(450, 357);
			this->Result->TabIndex = 4;
			this->Result->Text = L"";
			// 
			// Dimension
			// 
			this->Dimension->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->Dimension->Font = (gcnew System::Drawing::Font(L"Yu Gothic UI", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Dimension->Location = System::Drawing::Point(291, 49);
			this->Dimension->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->Dimension->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->Dimension->Name = L"Dimension";
			this->Dimension->Size = System::Drawing::Size(111, 39);
			this->Dimension->TabIndex = 5;
			this->Dimension->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->Dimension->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->Dimension->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// Label
			// 
			this->Label->AutoSize = true;
			this->Label->Font = (gcnew System::Drawing::Font(L"Rockwell", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Label->Location = System::Drawing::Point(88, 48);
			this->Label->Name = L"Label";
			this->Label->Size = System::Drawing::Size(178, 36);
			this->Label->TabIndex = 6;
			this->Label->Text = L"Dimension:";
			// 
			// Matrix
			// 
			this->Matrix->AllowUserToAddRows = false;
			this->Matrix->AllowUserToDeleteRows = false;
			this->Matrix->AllowUserToResizeColumns = false;
			this->Matrix->AllowUserToResizeRows = false;
			this->Matrix->BackgroundColor = System::Drawing::SystemColors::Window;
			this->Matrix->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->Matrix->ColumnHeadersVisible = false;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::MenuBar;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Rockwell", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle1->NullValue = L"0";
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::ScrollBar;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::Desktop;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->Matrix->DefaultCellStyle = dataGridViewCellStyle1;
			this->Matrix->GridColor = System::Drawing::Color::DarkGray;
			this->Matrix->Location = System::Drawing::Point(82, 95);
			this->Matrix->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Matrix->MultiSelect = false;
			this->Matrix->Name = L"Matrix";
			this->Matrix->ReadOnly = true;
			this->Matrix->RowHeadersVisible = false;
			this->Matrix->RowHeadersWidth = 62;
			this->Matrix->RowTemplate->Height = 28;
			this->Matrix->Size = System::Drawing::Size(320, 435);
			this->Matrix->TabIndex = 7;
			this->Matrix->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::Matrix_Click);
			// 
			// Choice
			// 
			this->Choice->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->Choice->Controls->Add(this->GreedyButton);
			this->Choice->Controls->Add(this->MRVButton);
			this->Choice->Controls->Add(this->DegreeButton);
			this->Choice->Font = (gcnew System::Drawing::Font(L"Rockwell", 14));
			this->Choice->Location = System::Drawing::Point(82, 615);
			this->Choice->Name = L"Choice";
			this->Choice->Size = System::Drawing::Size(320, 179);
			this->Choice->TabIndex = 8;
			this->Choice->TabStop = false;
			this->Choice->Text = L"Choose a method:";
			// 
			// Picture
			// 
			this->Picture->BackColor = System::Drawing::SystemColors::Window;
			this->Picture->Location = System::Drawing::Point(440, 49);
			this->Picture->Name = L"Picture";
			this->Picture->Size = System::Drawing::Size(450, 481);
			this->Picture->TabIndex = 9;
			this->Picture->TabStop = false;
			this->Picture->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::Picture_Paint);
			// 
			// Start
			// 
			this->Start->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->Start->Font = (gcnew System::Drawing::Font(L"Rockwell", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Start->Location = System::Drawing::Point(82, 816);
			this->Start->Name = L"Start";
			this->Start->Size = System::Drawing::Size(320, 89);
			this->Start->TabIndex = 10;
			this->Start->Text = L"Start";
			this->Start->UseVisualStyleBackColor = false;
			this->Start->Click += gcnew System::EventHandler(this, &MyForm::Start_Click);
			// 
			// Generate
			// 
			this->Generate->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->Generate->Font = (gcnew System::Drawing::Font(L"Rockwell", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Generate->Location = System::Drawing::Point(82, 548);
			this->Generate->Name = L"Generate";
			this->Generate->Size = System::Drawing::Size(320, 44);
			this->Generate->TabIndex = 12;
			this->Generate->Text = L"Generate random matrix";
			this->Generate->UseVisualStyleBackColor = false;
			this->Generate->Click += gcnew System::EventHandler(this, &MyForm::Random_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(962, 953);
			this->Controls->Add(this->Generate);
			this->Controls->Add(this->Start);
			this->Controls->Add(this->Picture);
			this->Controls->Add(this->Choice);
			this->Controls->Add(this->Matrix);
			this->Controls->Add(this->Label);
			this->Controls->Add(this->Dimension);
			this->Controls->Add(this->Result);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Graph coloring";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Dimension))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Matrix))->EndInit();
			this->Choice->ResumeLayout(false);
			this->Choice->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Picture))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: bool need_color;
	private: void save_matrix(bool**, int);
	private: void solving(bool**, int);
	private: void delete_matrix(bool**, int);
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Matrix_Click(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
	private: System::Void Random_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Start_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Picture_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
};
}
