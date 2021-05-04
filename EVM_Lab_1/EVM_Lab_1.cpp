#include <iostream>
#include <typeinfo>	
#include <Windows.h>
#include <cstdlib>

using namespace std;

const long long ONE = 1;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

union DoubleUnion
{
	double doubleValue;
	long long intValue;
};

template <typename T>
void invertByte(T& value);									// Инвертировать биты числа
template <typename T>
void input(T& value);										// Задать значение переменной

void showDouble(long long value);							// Вывести бинарное предствление типа double
void showChar(char value);									// Вывести бинарное предствление типа char
void invertMenu(char& charValue, long long& doubleValue);	// Отобразить меню выбора типа переменной для инвертирования битов



int main()
{
	setlocale(0, "");
	char ch;
	DoubleUnion doubleUnion;

	input(ch);
	input(doubleUnion.doubleValue);
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
		if (value & (ONE << byteNumber)) value ^= (ONE << byteNumber);
		else value |= (ONE << byteNumber);
	}
}

void showDouble(long long value)
{
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
}

void showChar(char value)
{
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
void input(T& value)
{
	cout << "Введите значение " << typeid(value).name() << ": ";
	cin >> value;
	cout << "Представление " << typeid(value).name() << " в памяти ЭВМ:" << endl;
	if (sizeof(value) == 1) showChar(value);
	else showDouble(value);
	cout << endl << endl;
}
