#include <iostream>
#include <typeinfo>	
#include <Windows.h>
#include <cstdlib>

using namespace std;

const long long ONE = 1;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

union DoubleUnion
{
	double doubleValue = 0; // запись
	long long intValue; // чтение
};

template <typename T>
void invertByte(T& value);									// Инвертировать биты числа
template <typename T>
T input(T value);										// Задать значение переменной

void invertMenu(char& charValue, long long& doubleValue);	// Отобразить меню выбора типа переменной для инвертирования битов
const void showDouble(long long value);
const void showChar(char value);


int main()
{
	setlocale(0, "");
	char ch = '0';
	DoubleUnion doubleUnion;

	ch = input(ch);
	showChar(ch);
	doubleUnion.doubleValue = input(doubleUnion.doubleValue);
	showDouble(doubleUnion.intValue);
	cout << endl;
	system("pause");

	invertMenu(ch, doubleUnion.intValue);
}

template <typename T>
void invertByte(T& value)
{
	cout << "Введите количество бит для инвертирования (от 1 до " << sizeof(value) * 8 << "): ";
	int bytesAmount;
	cin >> bytesAmount;
	for (int i = bytesAmount; i > 0; i--)
	{
		cout << "Осталось " << i << " бит(а)" << endl;
		cout << "Введите номер бита от 0 до " << sizeof(value) * 8 - 1 << ": ";
		int byteNumber;
		cin >> byteNumber;
		value ^= (ONE << byteNumber);
	}
}

const void showDouble(long long value)
{
	cout << "Представление double в памяти ЭВМ:" << endl;
	bool rank;
	for (int byteNumber = 63; byteNumber >= 0; byteNumber--)
	{
		rank = value & (ONE << byteNumber);
		if (byteNumber == 62)
		{
			cout << "  ";
			SetConsoleTextAttribute(h, 14);
		}
		if (byteNumber == 51)
		{
			cout << "  ";
			SetConsoleTextAttribute(h, 9);
		}
		if (byteNumber % 4 == 0)
		{
			cout << rank << " ";
		}
		else
		{
			cout << rank;
		}
	}
	SetConsoleTextAttribute(h, 7);
	cout << endl << endl;
}

const void showChar(char value)
{
	cout << "Представление char в памяти ЭВМ:" << endl;
	bool rank;
	for (int byteNumber = 15; byteNumber >= 0; byteNumber--)
	{
		rank = value & (1U << byteNumber);
		if (byteNumber == 14)
		{
			cout << "  ";
			SetConsoleTextAttribute(h, 14);
		}
		if (byteNumber % 4 == 0)
		{
			cout << rank << " ";
		}
		else
		{
			cout << rank;
		}
	}
	SetConsoleTextAttribute(h, 7);
	cout << endl << endl;
}

void invertMenu(char& charValue, long long& doubleValue)
{
	char answer = '0';
	while (1)
	{
		system("CLS");
		cout << "Выберите тип переменной (введите целое число от 1 до 3):" << endl;
		cout << "1. Char" << endl;
		cout << "2. Double" << endl;
		cout << "3. Выход" << endl;
		answer = getchar();
		switch (answer)
		{
		case '1':
			system("CLS");
			invertByte(charValue);
			cout << endl << "Инвертировано:" << endl;
			showChar(charValue);
			cout << endl;
			system("pause");
			break;
		case '2':
			system("CLS");
			invertByte(doubleValue);
			cout << endl << "Инвертировано:" << endl;
			showDouble(doubleValue);
			cout << endl;
			system("pause");
			break;
		case '3':
			exit(0);
			break;
		}
	}
}

template <typename T>
T input(T value)
{
	cout << "Введите значение " << typeid(value).name() << ": ";
	cin >> value;
	return value;
}
