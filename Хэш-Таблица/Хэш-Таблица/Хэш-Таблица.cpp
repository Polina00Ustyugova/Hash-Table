#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <ctime>
using namespace std;

bool is_created = false; // Создан ли список
// Сттруктура Человек
struct Human
{
	string name = ""; // ФИО
	string date = ""; // дата рождения
	string ID = ""; // ID
	Human* next = nullptr; // указатель на на следующий элемент

	void OutputHuman() // Вывести данные о человеке
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		cout << "Имя: " << this->name << endl;
		cout << "Дата рождения: " << this->date << endl;
		cout << "ID: " << this->ID << endl;
	}
	void Copied(Human* copy) // Скопировать данные о человеке
	{
		// копирование данных всех полей структуры в переданный объект класса
		this->name = copy->name; 
		this->date = copy->date;
		this->ID = copy->ID;
		this->next = nullptr;
	}
};

struct list // Структура списка
{
	Human* first = nullptr; // Указатель на 0
	int size = 0; // Размер списка
};
/*string date_generator(string date)
{
	srand(time(NULL));
	const string fill = "0123456789";
	for (int i = 1; i <= 10; i++) date += fill[rand() % 10];
	return date;
}*/

list* make_list(int n) // создание списка
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string name, date = "", id;
	Human* p = new Human, * r; // Создание новго объекта класса
	getline(cin, name);
	cout << "Введите имя: ";
	getline(cin, name);
	p->name = name;
	cout << "Дата рождения: ";
	getline(cin, date);
	p->date = date;
	cout << "Введите ID: ";
	getline(cin, id);
	p->ID = id;
	p->next = nullptr;
	list* l = new list; // Создание списка
	l->first = p;
	l->size = n;

	for (int i = 1; i < n; i++) {
		r = new(Human);
		getline(cin, name);
		cout << "Введите имя: ";
		getline(cin, name);
		r->name = name;
		cout << "Дата рождения: ";
		getline(cin, date);
		r->date = date;
		cout << "Введите ID: ";
		getline(cin, id);
		r->ID = id;
		p->next = r;
		r->next = nullptr;
		p = r;
	}
	return l; 
}


void add_point(list* l, int k) // Добавить новый элемент класса в список
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	k--;
	string name, date, id;
	Human* one = new Human;
	getline(cin, name);
	cout << "Введите имя: ";
	getline(cin, name);
	one->name = name;
	cout << "Дата рождения: ";
	getline(cin, date);
	one->date = date;
	cout << "Введите ID: ";
	getline(cin, id);
	one->ID = id;

	if (k == 0) 
	{
		one->next = l->first;
		l->first = one;
		l->size++;
		return;
	}

	Human* temp = l->first;
	for (int i = 0; i < k - 1 && temp->next != nullptr; i++) temp = temp->next; // ищет предыдущий заданному номеру элемента узел
	one->next = temp->next;
	if (temp->next == nullptr) one->next = nullptr;
	temp->next = one;
	l->size++;
	return;
}

void del_point(list* l, int k) // Удаляет элемент под заданным номером
{
	k--;
	Human* p = l->first;
	if (k == 0) {
		l->first = l->first->next;
		if (l->first == nullptr) return;
		delete p;
		l->size--;
		return;
	}
	for (int i = 0; i < k - 1 && p != nullptr; i++, p = p->next); // ищет предыдущий элемент 
	if (p == nullptr || p->next == nullptr) return;
	Human* r = p->next; 
	p->next = r->next; 
	delete r;
	l->size--;
	r = p->next; 
	return;
}

void delete_list(list* l) // Удалить список
{
	int size = l->size;
	for (int i = size; i > 0; i--) del_point(l, i);
}

void print_list(list* l) // Вывести список на экран
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (l->size == 0) 
	{
		cout << "Список пустой\n" << endl;
		return;
	}
	Human* pep = l->first;
	for (int i = 0; i < l->size; i++) // Вывод списка на экран через цикл
	{
		pep->OutputHuman();
		cout << "-----------------------------" << endl;
		pep = pep->next;
	}
	cout << endl;
}

void printINfile(list* l, string path) // Печать в файл
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())  cout << "Error" << endl; 
	else 
	{
		Human* p = l->first;
		for (int i = 0; i < l->size; i++) 
		{
			if (i + 1 != l->size) // Чтобы при восстановлении энтер не считывался как ещё один элемент списка
			{
				fout << p->name << endl;
				fout << p->date << endl;
				fout << p->ID << endl;
				p = p->next;
			}
			else
			{
				fout << p->name << endl;
				fout << p->date << endl;
				fout << p->ID;
				p = p->next;
			}
		}
		cout << "Информация была сохранена!" << endl;
	}
	fout.close();
}

list* readFROMfile(string path) // Чтение информации из файла
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin;
	fin.open(path);
	list* l = new(list);
	if (!fin.is_open()) cout << "Error" << endl; 
	else 
	{
		string name, date, id;
		Human* p, * r;
		p = new (Human);
		fin >> name >> date >> id;
		p->name = name;
		p->date = date;
		p->ID = id;
		p->next = nullptr;
		l->first = p;
		l->size++;
		while (!fin.eof()) 
		{ 
			name = ""; date = ""; id = ""; // Значения затираются для записи новых
			fin >> name >> date >> id;
			r = new(Human);
			r->name = name;
			r->date = date;
			r->ID = id;
			p->next = r;
			r->next = nullptr;
			p = r;
			l->size++;
		}
		cout << "Информация была восстановлена!" << endl;
	}
	fin.close();
	return l;
}

int hash_func(string one, int size)
{
	float num;
	// stoi() преобразует последовательность символов в str в значение типа int и возвращает значение
	num = stoi(one.substr(0, 2)) + stoi(one.substr(3, 5)) + stoi(one.substr(6, 10)); // Метод substr() возвращает указанное количество символов из строки, начиная с указанной позиции (сначала указывается позиция, затем количество)
	num = (int)num % size; // Число, полученное с помощью функции stoi(), делится на размер таблицы
	return (int)num;
}
// Метод открытой адресации
Human** open_address_method(list* l, int* coliz)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size = l->size, pos;
	Human* one = l->first;
	Human** table = new Human* [size];
	for (int i = 0; i < size; i++) table[i] = new Human; // Для каждого элемента массива (таблицы) создаётся объект класса

	for (int i = 0; i < size; i++) {
		pos = hash_func(one->date, size); // Позиция в таблице (индекс в массиве) опеределяется с помощью хэш функции
		if (table[pos]->date == "") // Если позиция пуста, то сюда записывается значение
		{
			table[pos] = one;
			one = one->next; // Указатели на следующие 
		}
		else 
		{
			coliz++;
			while (table[pos]->date != "") // Поиск свободной позиции в таблице
			{
				pos++;
				if (pos >= size) pos = pos - size; // если достигнут конец таблицы, позиции начинают проверяться с первой
			}
			table[pos] = one;
			one = one->next;
		}
	}
	return table;
}
// Метод цепочек
Human** chain_method(list* l, int* coliz) 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size = l->size, pos;
	Human* curr = l->first;
	Human* pep = new Human, * r;
	Human** table = new Human * [size];
	for (int i = 0; i < size; i++) table[i] = new Human;
	pep->Copied(curr);
	for (int i = 0; i < size; i++) {
		pos = hash_func(curr->date, size);

		if (table[pos]->date == "") {
			table[pos] = pep;
		}
		else {
			r = table[pos];
			pep->next = r;
			table[pos] = pep;

		}
		pep = new Human;
		if (curr->next != nullptr) {
			curr = curr->next;
			pep->Copied(curr);
		}

	}
	return table;
}

void print_hash(Human** table, int size, int type) 
{
	if (type == 1) for (int i = 0; i < size; i++) 
	{
		cout << i << ":\n";
		table[i]->OutputHuman();
		cout << "-----------------------------" << endl;
	}
	else 
	{
		for (int i = 0; i < size; i++) 
		{
			cout << i << ":\n";
			Human* pep = table[i];
			do 
			{
				pep->OutputHuman();
				pep = pep->next;
				cout << endl;
			} while (pep != nullptr);
			cout << "-----------------------------" << endl;
		}
	}
}
list* people;
void menu(const int c) 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int* coliz2 = new(int);
	coliz2 = 0;
	string path = "myFile.txt";

	if (c > 1 && c < 9 && !is_created) // если списка ещё нет
	{ 
		cout << "Чтобы взаимодействовать со списком, требуется его создать или восстановить" << endl;
		return;
	}
	switch (c)
	{
	case 1:
	{
		string choice;
		if (is_created)
		{
			cout << "Список уже существует. Создав новый, старый будет утерян. Вы уверены, что хотите создать новый?" << endl;
			getline(cin, choice);
			getline(cin, choice);
			if (choice == "Нет" || choice == "No") break;
		}
		int n;
		cout << "Введите размер списка: ";
		cin >> n;
		people = make_list(n);
		is_created = true;
		break;
	}
	case 2:
	{
		print_list(people);
		int k;
		cout << "Введите поизицию, на которую хотите вставить элемент: ";
		cin >> k;
		add_point(people, k);
		print_list(people);
		break;
	}
	case 3:
	{
		print_list(people);
		int n;
		cout << "Введите позицию элемента, который желаете удалить: ";
		cin >> n;
		del_point(people, n);
		print_list(people);
		break;
	}
	case 4:
		print_list(people);
		break;
	case 5:
		printINfile(people, path);
		break;
	case 6:
	{
		cout << "Список был удалён" << endl;
		delete_list(people);
		is_created = false;
		break;
	}
	case 7:
	{
		int* coliz1 = new(int);
		coliz1 = 0;
		string date; 
		int pos = 0, counter = 0;
		Human** table = open_address_method(people, coliz1);
		print_hash(table, people->size, 1);
		cout << "Введите дату рождения: ";
		getline(cin, date); 
		getline(cin, date);
		while (date.length() != 10)
		{
			cout << "Введите дату рождения: ";
			getline(cin, date);
		}
		pos = hash_func(date, people->size);
		if (table[pos]->date == date)
		{
			table[pos]->OutputHuman();
		}
		else
		{
			while (table[pos]->date != date && counter < people->size)
			{
				pos++; counter++;
				if (pos >= people->size) pos = pos - people->size;
			}
			if (counter < people->size) table[pos]->OutputHuman();
			else cout << "Заданный элемент не был найден" << endl;
		}
		cout << "Количество возникших коллизий: " << coliz1 << endl;
		break;
	}
	case 8:
	{
		string date; int pos; bool flag = false;
		Human** table = chain_method(people, coliz2);
		print_hash(table, people->size, 2);
		cout << "Введите дату рождения: ";
		getline(cin, date); getline(cin, date);
		while (date.length() != 10)
		{
			cout << "Введите дату рождения: ";
			getline(cin, date);
		}
		pos = hash_func(date, people->size);
		Human* pep = table[pos];
		while (!flag && pep != nullptr)
		{
			if (pep->date == date) flag = true;
			else pep = pep->next;
		}
		if (flag) pep->OutputHuman();
		else cout << "Not found" << endl;
		break;
	}
	case 9:
	{
		people = new list;
		people = readFROMfile(path);
		if (people->first == nullptr) cout << "Файл пуст" << endl;
		else is_created = true;
		break;
	}
	default:
	{
		delete_list(people);
		exit(777);
	}
	}
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) 
	{
		system("pause");
		system("cls");
		cout << "1. Создать список" << endl;
		cout << "2. Добавить элемент на заданную позицию" << endl;
		cout << "3. Удалить элемент" << endl;
		cout << "4. вывести список на экран" << endl;
		cout << "5. Сохранить данные в файл" << endl;
		cout << "6. Удалить список" << endl;
		cout << "7. Метод открытой адресации" << endl;
		cout << "8. Метод цепочек" << endl;
		cout << "9. Восстановить список из файла" << endl;

		cout << "Введите номер операции: ";
		int c;
		cin >> c;
		system("cls");
		menu(c);
	}
	return 0;
}
