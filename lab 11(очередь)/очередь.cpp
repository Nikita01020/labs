#include <iostream>
using namespace std;

template <typename T>
struct Node
{
	T data;//данные
	Node<T>* next;//указатель на следующий элемент
};

template <typename T>
struct Queue
{
	int size = 0;//размер
	Node<T>* head = NULL;//указатель на голову
	Node<T>* tail = NULL;//указатель на хвост
};

template <typename T>
void init_queue(Queue<T>& q, const T& value)
{
	Node<T>* new_node = new Node<T>();//резервируем память под первый элемент
	new_node->data = value;//в поле ключа присваиваем передаваемое значение
	q.head = new_node;//первый элемент - единственный
	q.tail = new_node;//поэтому указатели указывают на него
	q.size = 1;//всего один элемент
}

template <typename T>
void push(Queue<T>& q, const T& value)
{
	if (q.head != NULL)
	{
		Node<T>* new_node = new Node<T>();//резервируем память под новый элемент
		q.size++;//увеличиваем размер очереди на 1
		new_node->data = value;//в поле ключа присваиваем передаваемое значение
		new_node->next = NULL;//последний элемент ни на что не указывает
		q.tail->next = new_node;//предпоследний элемент указывает на последний
		q.tail = new_node;//указатель на последний элемент теперь указывает на новый
	}
	else
	{
		init_queue(q, value);
	}
}

template <typename T>
void new_queue(Queue<T>& q, const int& n)
{
	T a;
	for (int i = 1; i <= n; i++)
	{
		cout << "Введите элемент: ";
		cin >> a;
		push(q, a);//вводим элемент и вставляем в конец очереди
	}
}

template <typename T>
void print_queue(Queue<T>& q)
{
	Node<T>* tmp = q.head;//указатель на первый элемент
	cout << "начало -> ";
	while (tmp != NULL)//пока не дойдём до последнего элемента
	{
		cout << tmp->data << " -> ";//обращаемся к полю элемента и выводим значение
		tmp = tmp->next;//переходим к следующему элементу
	}
	cout << "конец" << endl;
}

template <typename T>
void pop(Queue<T>& q)
{
	Node<T>* tmp = q.head;//указатель на первый элемент
	q.head = q.head->next;//голова теперь следующий элемент
	q.size--;//кол-во стало меньше на 1
	delete tmp;//очищаем память
}

template <typename T>
void delete_key(Queue<T>& q, const T& k)
{
	int i = 1;
	while (i <= q.size)//пока не пройдём полный "круг"
	{
		if (q.head->data == k)//если первый элемент равен ключу
		{
			pop(q);//удаляем его
			/*не нужно увеличивать счётчик, т.к. размер уже стал на 1 меньше*/
		}
		else//иначе переставляем элемент в конец очереди
		{
			push(q, q.head->data);
			pop(q);
			i++;
		}
	}
}

template <typename T>
void insert(Queue<T>& q, const int& count, const int& number)
{
	int i = 1;
	while (i < number)//пока не дойдём до нужного элемента
	{
		push(q, q.head->data);
		pop(q);//переставляем элементы с головы в хвост
		i++;
	}
	T a;
	for (int j = 1; j <= count; j++)
	{
		cout << "Введите элемент для добавления: ";
		cin >> a;
		push(q, a);//добавляем count новых элементов
	}
	for (i; i <= q.size - count; i++)//чтобы первый элемент оказался на своём месте
	{
		push(q, q.head->data);
		pop(q);//переставляем элементы с головы в хвост
	}
}

template <typename T>
void delete_queue(Queue<T>& q)
{
	while (q.head != NULL)//пока не дойдём до последнего элемента
	{
		pop(q);//удаляем элемент, очищаем память
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	Queue<char> q;
	int n;

	do
	{
		cout << "Введите кол-во элементов в очереди: ";
		cin >> n;//вводим количество элементов
	} while (n <= 0);//количество должно быть больше 0

	new_queue(q, n);//создаём очередь
	cout << endl;
	print_queue(q);//выводим на экран

	cout << endl << "Введите ключ элемента, который необходимо удалить: ";
	char key;
	cin >> key;

	delete_key(q, key);//удаление
	cout << endl;
	print_queue(q);//выводим на экран

	int number;
	do
	{
		cout << endl << "Введите номер элемента, перед которым нужно вставить элементы: ";
		cin >> number;
	} while (number <= 0 || number > q.size);

	cout << endl << "Введите кол-во элементов для добавления: ";
	int count;
	cin >> count;

	insert(q, count, number);//вставка
	cout << endl;
	print_queue(q);//выводим на экран


	delete_queue(q);//очищение памяти
	cout << "Завершено." << endl;
	print_queue(q);
	return 0;
}

