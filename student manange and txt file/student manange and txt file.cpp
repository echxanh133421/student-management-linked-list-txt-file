
#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

// data struct
struct student
{
	
	string name;
	string birthday;
	int id;
	int point;
};

struct NodeStudent
{
	student St;
	struct NodeStudent* next;
};

struct listStudent
{
	NodeStudent* head;
	NodeStudent* tail;
};
// operation on list

void creatlist(listStudent& l)
{
	l.head = NULL;
	l.tail = NULL;
}

NodeStudent* creatNode(student st) 
{
	
	NodeStudent* node = new NodeStudent;
	
	node->St.name = st.name;
	node->St.birthday = st.birthday;
	node->St.id = st.id;
	node->St.point = st.point;
	node->next = NULL;
	return node;
}

void AddTail(listStudent& l, NodeStudent* node)
{
	if (l.head == NULL)
	{
		l.head = node;
		l.tail = node;
	}
	else
	{
		l.tail->next = node;
		l.tail = node;
		
	}
}

//read data from file

void process(student& st)
{
	if (st.name.at(0)=='\n') {
		st.name.erase(st.name.begin());
	}

}

void readFile(ifstream &filein, listStudent &arr)
{
	int number=1;
	filein.open("data.txt", ios::in);
	while (!filein.eof()) {
		student st;
		
		getline(filein, st.name,',');
		getline(filein, st.birthday, ',');
		filein >> st.id;
		char x;
		filein >> x;
		filein >> st.point;
		process(st);
		AddTail(arr,creatNode(st));
		
	}
	filein.close();
}

//  data processing function

void menu()
{
	cout << "\t\tDANH SACH THAO TAC\n";
	cout << "1.in danh sach \n";
	cout << "2.them\n";
	cout << "3.sua \n";
	cout << "4.xoa\n";
	cout << "5.sap xep\n";
	cout << "6.tim kiem\n";
	cout << "7.thong ke\n";
	cout << "8.sao luu\n";
	cout << "9.thoat\n";
	cout << "--------------------------\n";
}

void enterSelect(int& select)
{
	cout << "nhap lua chon: ";
	cin >> select;
}

void show(listStudent l)
{
	if (l.head != NULL)
	{
		NodeStudent* node = l.head;
		cout << "\t+------+-------------------+-------------+------------+--------+\n";
		cout << "\t|STT   |ho va ten          |ngay sinh    |ma so       |diem    |\n";
		cout << "\t+------+-------------------+-------------+------------+--------+\n";
		int i = 1;
		while (node != NULL) {
			
			cout << "\t|" << i <<"     |";
			cout <<setw(19)<<left<<node->St.name<<"|"<<setw(13)<<left<<node->St.birthday<<"|";
			cout << setw(12) << left << node->St.id << "|"<<setw(8)<<left<<node->St.point<<"|\n";
			node = node->next;
			i++;
		}
		cout << "\t+------+-------------------+-------------+------------+--------+\n";
		cout << "--------------------------\n";
		
	}
}

void insert(listStudent l)
{
	student st;
	cout << "[2] them sinh vien:\n";
	cout << "\t(?) nhap ten: ";
	cin.ignore();
	getline(cin, st.name);
	cout << "\t(?) nhap ngay sinh: ";
	getline(cin, st.birthday);
	cout << "\t(?) nhap ma so: ";
	cin >> st.id;
	cout << "\t(?) nhap diem: ";
	cin >> st.point;
	AddTail(l, creatNode(st));
	cout << "\t(!) da them sinh vien\n";
	cout << "--------------------------\n";
}

void edit(listStudent l)
{
	int n;
	cout << "[3] nhap stt sinh vien: ";
	cin >> n;
	NodeStudent* node = l.head;
	cout << "\tsua thong tin sinh vien: " << n << "\n";

	while (--n) {
		node = node->next;

	}
	cin.ignore();
	cout << "\t\t(?) nhap ten: ";
	getline(cin, node->St.name);
	cout << "\t\t(?) nhap ngay sinh: ";
	getline(cin, node->St.birthday);
	cout << "\t\t(?) nhap ma so: ";
	cin >>node->St.id;
	cout << "\t\t(?) nhap diem: ";
	cin >> node->St.point;
	
	cout << "\t(!) da sua thong tin sinh vien\n";
	cout << "--------------------------\n";
}

void deleteStudent(listStudent &l)
{
	int number;
	cout << "\tnhap so thu tu sinh vien muon xoa: ";
	cin >> number;
	NodeStudent* node = l.head;

	if (number == 1)
	{
		l.head = node->next;
	}
	else 
	{
		number--;
		while (--number)
		{
			node = node->next;
		}
		node->next = node->next->next;
	}

	cout << "--------------------------\n";
}


// SORT 

//1. sort name merge sort
// swap function;

void swap(NodeStudent* nodemin, NodeStudent* node)
{
	student st;
	st.name = nodemin->St.name;
	st.point = nodemin->St.point;
	st.birthday = nodemin->St.birthday;
	st.id = nodemin->St.id;

	nodemin->St.name = node->St.name;
	nodemin->St.point = node->St.point;
	nodemin->St.birthday = node->St.birthday;
	nodemin->St.id = node->St.id;

	node->St.name = st.name;
	node->St.point = st.point;
	node->St.birthday = st.birthday;
	node->St.id = st.id;
}

void sort_name_selection(listStudent l)
{
	NodeStudent* node = l.head;

	while (node->next != NULL)
	{
		NodeStudent* nodemin = node;
		NodeStudent* nodenext = node->next;
		while (nodenext != NULL)
		{
			if (nodemin->St.name > nodenext->St.name)
			{
				nodemin = nodenext;
			}
			nodenext = nodenext->next;
		}
		swap(nodemin, node);

		node = node->next;
	}
}

//2.sort point quick sort

void sort_point_selection(listStudent l)
{
	NodeStudent* node = l.head;

	while (node->next != NULL)
	{
		NodeStudent* nodemin = node;
		NodeStudent* nodenext = node->next;
		while (nodenext != NULL)
		{
			if (nodemin->St.point > nodenext->St.point)
			{
				nodemin = nodenext;
			}
			nodenext = nodenext->next;
		}
		swap(nodemin, node);

		node = node->next;
	}
}

void sort(listStudent l)
{
	int select;
	
	cout << "\t1. sap xep theo ten (abc)\n";
	cout << "\t2. sap xep theo diem (tu thap nhat len cao nhat)\n";
	cout << "\t nhap lua chon: ";
	cin >> select;
	if (select == 1)
	{
		sort_name_selection(l);
	}
	else
	{
		sort_point_selection(l);
	}
	show(l);

}

//END SORT

void find(listStudent l)
{
	string check;
	cout << "\tnhap ki tu :";
	cin.ignore();
	getline(cin, check);
	NodeStudent* node = l.head;
	int i = 1;
	cout << "\t+------+-------------------+-------------+------------+--------+\n";
	cout << "\t|STT   |ho va ten          |ngay sinh    |ma so       |diem    |\n";
	cout << "\t+------+-------------------+-------------+------------+--------+\n";
	while (node != NULL)
	{
		if (node->St.name.find(check) != string::npos) {
			cout << "\t|" << i << "     |";
			cout << setw(19) << left << node->St.name << "|" << setw(13) << left << node->St.birthday << "|";
			cout << setw(12) << left << node->St.id << "|" << setw(8) << left << node->St.point << "|\n";
			
			i++;
		}
		node = node->next;
	}
	cout << "\t+------+-------------------+-------------+------------+--------+\n";
	cout << "--------------------------\n";
}

void statistical(listStudent l)
{
	cout << "[7] thong ke:\n";
	NodeStudent* node = l.head;
	
	float sum = 0;
	float max = 0;
	int count=0;
	int Excellent = 0;
	int good = 0;
	int average = 0;
	while (node != NULL)
	{
		sum += node->St.point;
		if (node->St.point > max)
		{
			max = node->St.point;
		}
		count++;
		if (node->St.point >= 8.0)
		{
			Excellent++;
		}
		else if(node->St.point<6.5)
		{
			 average++;
		}
		else
		{
			good++;
		}
		node = node->next;
	}
	cout << "\tdiem trung binh: " << sum / count << "\n";
	cout << "\tdiem cao nhat: " << max << "\n";
	cout << "\tti le sinh vien gioi: " << (float) Excellent / count * 100 << "%\n";
	cout << "\tti le sinh vien kha: " << (float) good / count * 100 << "%\n";
	cout << "\tti le sinh vien trung binh: " << (float) average / count * 100 << "%\n";
	cout << "--------------------------\n";
}

void backup(ofstream& fileout,listStudent l)
{
	fileout.open("data.txt", ios::out);
	NodeStudent* node = l.head;
	while (node != NULL)
	{
		if (node->next != NULL)
		{
			fileout << node->St.name << "," << node->St.birthday << "," << node->St.id << "," << node->St.point << "\n";
		}
		else
		{
			fileout << node->St.name << "," << node->St.birthday << "," << node->St.id << "," << node->St.point ;
		}
		node = node->next;
	}
	cout << "--------------------------\n";
}

//main project

void commandExecution(int& select,listStudent l)
{
	do
	{
		enterSelect(select);
		switch (select)
		{
		case 1: {
			cout << "\tdanh sach hoc sinh\n";
			show(l);
			break;
		}
		case 2: {
			insert(l);
			break;
		}
		case 3: {
			edit(l);
			break;
		}
		case 4: {
			deleteStudent(l);
			break;
		}
		case 5: {
			sort(l);
			break;
		}
		case 6: {
			find(l);
			break;
		}
		case 7: {
			statistical(l);
			break;
		}
		case 8: {
			ofstream fileout;
			backup(fileout, l);
			break;
		}
		case 9: {
			cout << "\t--------cam on----------\n";
			break;
		}
		default: {
			cout << "nhap sai lenh\n";
			cout << "--------------------------\n";
			break;
		}
		}

	} while (select != 9);
}

int main()
{
	ifstream filein;
	listStudent arr;
	creatlist(arr );
	readFile(filein, arr);
	menu();
	int select;
	commandExecution(select,arr);
	return 0;
}