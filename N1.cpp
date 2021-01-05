#include <conio.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct element {
	char simvol;
	element *next;
};

typedef element *_element;
_element Head = NULL;

// Создание узла
_element CreateElement (char NewSimvol){
	_element NewElement = new element;
	NewElement->simvol = NewSimvol;
	NewElement->next = NULL;
	return NewElement;
}

// Добавление узла в начало списка
void AddFirst (_element &Head, _element NewElement){
	NewElement->next = Head;
	Head = NewElement;
}

// Добавление узла после заданного
void AddAfter (_element p, _element NewElement){
	NewElement->next = p->next;
	p->next = NewElement;
}

// Добавление узла в конец списка
void AddLast (_element &Head, _element NewElement){
	_element q=Head;
	if (Head==NULL){
		AddFirst(Head, NewElement);
		return;
	}
	while (q->next)
		q=q->next;
	AddAfter (q, NewElement);	
}

// Добавление узла в середину списка
void AddMiddle(_element &Head, _element NewElement, int n){
	_element p = Head;
	for(int i = 0; i < n/2-1; i++){
		p = p->next;
	}
	AddAfter(p, NewElement);
}

// Добавление узла перед заданным
void AddBefore (_element &Head, _element p, _element NewElement){
	_element q = Head;
	if (Head == p){
		AddFirst (Head, NewElement);
		return;
	}
	while (q and q->next!=p)
		q=q->next;
	if (q)
		AddAfter(q, NewElement);
}

// Удаление узла
void DeleteElement(_element &Head, char c){
	_element prev = 0;
	_element q = Head;
	int flag = -1;
	while (q){
    	_element next = q->next;
    	if (q->simvol == c){
        	if (prev){
        		flag = 1;
				prev->next = next;
			}
        	delete q;
    	}
    	else{
        	prev = q;
    	}
    	q = next;
	}
	if (flag == -1)
		cout << "Элемемент не найден!";
}

// Удаление всего
void DeleteAll(_element &Head, char c){
	_element prev = 0;
	_element q = Head;
	while (q){
    	_element next = q->next;
    	if (q->simvol == c){
        	if (prev){
        		prev->next = next;
			}
        	delete q;
    	}
    	else{
        	prev = q;
    	}
    	q = next;
	}
}

void udalit_inf(_element &nach,_element pered){
	int vibor_el = 1;
	_element konec=nach;
	for(int i=0;i<vibor_el-1;i++){
			pered=pered->next;
	}
	if (nach==pered)
		nach=pered->next;
	else {
		while (konec and konec->next != pered)
			konec=konec->next;
		if (konec== NULL)
			return;
		konec->next=pered->next;	
	}
	delete pered;
}

// Чтение из файла
void ReadFromFile(int flag, int N){
	ifstream in("input.txt");
	string line;
	while (getline(in, line))
    {
		_element node = CreateElement(line[0]);
		if (flag == 1)
			AddLast(Head, node);
		if (flag == 2)
			AddFirst(Head, node);
		if (flag == 3)
			AddMiddle(Head, node, N);
	}
	in.close();
}

// Генерация случайных символов
void Generate(int flag, int N){
	srand(time(NULL));
	for (int i = 0; i < N; i++){
		_element node = CreateElement(char(rand() % (32) + 33 ));
		if (flag == 1)
			AddLast(Head, node);
		if (flag == 2)
			AddFirst(Head, node);
		if (flag == 3)
			AddMiddle(Head, node, N);
	}
}

// Вывод
void Show(int flagDEL){
	//if (flagDEL == 1){
		//cout << "Списко пуст!";
	//}
	//else {
		_element node = Head;
		while (node){
			cout << node->simvol<< " ";
			node = node->next;	
		}
	//}
}

// Сортировка по заданию
void Sort(){
	_element node = Head;
	while (node){
		_element _node = Head;
		while(_node){
			if (((int)(node->simvol) == 65) || ((int)(node->simvol) == 69) ||  
			((int)(node->simvol) == 73) || ((int)(node->simvol) == 79) ||  
			((int)(node->simvol) == 85) || ((int)(node->simvol) == 97) ||  
			((int)(node->simvol) == 101) || ((int)(node->simvol) == 105) ||  
			((int)(node->simvol) == 111) || ((int)(node->simvol) == 117) ||  
			((int)(node->simvol) == 128) ||	((int)(node->simvol) == 133) ||  
			((int)(node->simvol) == 136) ||	((int)(node->simvol) == 142) ||  
			((int)(node->simvol) == 147) ||	((int)(node->simvol) == 155) ||  
			((int)(node->simvol) == 157) ||	((int)(node->simvol) == 158) ||  
			((int)(node->simvol) == 159) ||	((int)(node->simvol) == 160) || 
			((int)(node->simvol) == 165) || ((int)(node->simvol) == 168) || 
			((int)(node->simvol) == 174) || ((int)(node->simvol) == 227) ||  
			((int)(node->simvol) == 235) || ((int)(node->simvol) == 237) ||  
			((int)(node->simvol) == 238) ||	((int)(node->simvol) == 239) ||  
			((int)(node->simvol) == 240) ||	((int)(node->simvol) == 241) )

				swap(_node->simvol, node->simvol);
			_node = _node->next;
		}
		node = node->next;
	}
}

// Поиск по заданию
void Find(){
	_element node = Head;
	int c = 1;
	while(node){
		if ((int)(node->simvol) == 46){
			cout << "Номер первого знака «.» - " << c;
			return;
		}
		node = node->next;
		c++;
	}
	cout << "Не найдено ни одного символа «.»";
}

int main(){
	setlocale(LC_ALL, "Russian");
	int flag = 0, flagDEL = -1;
	int N = 0;
		
	while (flag != 8){
		cout << "Ввдеите действие:"<< endl;
		cout << "1 - добавить в конец"<< endl;
		cout << "2 - добавить в начало"<< endl;
		cout << "3 - добавить в середину"<< endl;
		cout << "4 - Поиск"<< endl;
		cout << "5 - Сортировка"<< endl;
		cout << "6 - Показать"<< endl;
		cout << "7 - Удаление"<< endl;
		cout << "8 - Выход"<< endl;
	
		cin >> flag;
		char c;
		int flag2 = -1;
		_element node;

		if (flag == 1){
			cout << endl;
			cout << "	1 - ввести"<< endl;
			cout << "	2 - добавить из файла"<< endl;
			cout << "	3 - добавить случайные"<< endl;
			cin >> flag2;
			if (flag2 == 1){
				cout << "Введите символ ";
				cin >> c;
				node = CreateElement(c);
				AddLast(Head, node);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 2){
				ReadFromFile(flag, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 3){
				cout << "Сколько букв сгенерировать?" << endl;
				cin >> N;
				Generate(flag, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			system("pause");
		}
		if (flag == 2){
			cout << endl;
			cout << "	1 - ввести"<< endl;
			cout << "	2 - добавить из файла"<< endl;
			cout << "	3 - добавить случайные"<< endl;
			cin >> flag2;
			if (flag2 == 1){
				cout << "Введите символ ";
				cin >> c;
				node = CreateElement(c);
				AddFirst(Head, node);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 2){
				ReadFromFile(flag, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 3){
				cout << "Сколько букв сгенерировать?" << endl;
				cin >> N;
				Generate(flag, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			system("pause");
		}
		if (flag == 3){
			cout << endl;
			cout << "	1 - ввести"<< endl;
			cout << "	2 - добавить из файла"<< endl;
			cout << "	3 - добавить случайные"<< endl;
			cin >> flag2;
			if (flag2 == 1){
				cout << "Введите символ ";
				cin >> c;
				node = CreateElement(c);
				AddMiddle(Head, node, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 2){
				ReadFromFile(flag, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 3){
				cout << "Сколько букв сгенерировать?" << endl;
				cin >> N;
				Generate(flag, N);
				flagDEL = -1;
				Show(flagDEL);
				cout << endl;
			}
			system("pause");
		}
		if (flag == 4){
			Show(flagDEL);
			cout << endl;
			Find();
			cout << endl;
			system("pause");
		}
		if (flag == 5){
			cout << "Сортировка: в начало все гласные, остальные в конец:" << endl;
			Sort();
			Show(flagDEL); 
			cout << endl;
			system("pause");
		}
		if (flag == 6){
			Show(flagDEL); 
			cout << endl;
			system("pause");
		}
		if (flag == 7){
			cout << endl;
			cout << "	1 - удалить 1 символ"<< endl;
			cout << "	2 - удалить все"<< endl;
			cin >> flag2;
			if (flag2 == 1){
				cout << "Введите символ ";
				cin >> c;
				DeleteElement(Head, c);
				Show(flagDEL);
				cout << endl;
			}
			if (flag2 == 2){
				_element node = Head;
				while (node){
					DeleteAll(Head, node->simvol);
					node = node->next;
				}
				udalit_inf(Head, Head);
				cout << "Список очищен!";
				cout << endl;
				flagDEL = 1;
			}
			system("pause");
		}	
		system("cls");
	}
	system("pause");
	return 0;
}


