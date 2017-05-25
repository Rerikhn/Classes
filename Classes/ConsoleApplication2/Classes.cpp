// ConsoleApplication2.cpp: определ€ет точку входа дл€ консольного приложени€.
//

/*—оздать класс дл€ хранени€ одномерных целочисленных массивов.
ќбеспечить возможность задани€ количества элементов и базововй индексации.
«апрограммировать методы поиска элементов и сортировки. ѕерегрузить операции
дл€ сложени€ и вычитани€ векторов. ѕерегрузить операцию индексировани€ (т.к.
оператор вз€ти€ индекса может по€вл€тьс€ как слева, так и справа от оператора присваивани€,
то функци€ должна возвращать int&) с проверкой допустимости индекса.
*/

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
const int White = system("color 70");
template <typename Type>
class Arrays{
private:
	Type *elements;
	int count, index;
public:
	Arrays(int cnt = 1, int indx = 0) {
		count = cnt;
		index = indx;
		elements = (Type*)calloc(count, sizeof(Type));
		elements -= index;
	}
	Arrays(Type mas[], int cnt) {
		count = cnt;
		index = 0;
		elements = (Type*)calloc(count, sizeof(Type));
		elements -= index;
		for (int i = 0; i < cnt; i++) {
			elements[i + index] = mas[i];
		}
	}
	Arrays(const Arrays &obj) {
		count = obj.count;
		index = obj.index;
		elements = (Type*)calloc(count, sizeof(Type));
		elements -= index;
		for (int i = obj.index; i < obj.count + obj.index; i++) {
			elements[i] = obj.elements[i];
		}
	}
	~Arrays(){}
	void print();
	void setrnd(Type, Type);
	Type* search(Type);
	void sortup();
	void sortdown();
	Type& Arrays<Type>::operator[](int j);
	friend ostream& operator<<(ostream &str, const  Arrays<Type> &object) {
		str << endl << "Current options: count = " << object.count << ", index = " << object.index << endl;
		str << "[";
		for (int i = object.index; i < object.count + object.index - 1; i++) {
			str << object.elements[i] << "; ";
		}
		str << object.elements[object.count + object.index - 1] << "]" << endl;
		return str;
	}
	friend Arrays<Type> operator-(const Arrays<Type> &x, const Arrays<Type> &y) {
		if (x.count != y.count)
			throw "Error, unequal size";
		else{
			Arrays z(x.count, 0);
			for (int i = 0; i < z.count; ++i)
			{
				z.elements[i] = x.elements[i + x.index] - y.elements[i + y.index];
			}
			return z;
		}
	}
	friend Arrays<Type> operator+(const Arrays<Type> &x, const Arrays<Type> &y) {
		if (x.count != y.count)
			throw "Error, unequal size";
		else {
			Arrays z(x.count, 0);
			for (int i = 0; i < z.count; ++i){
				z.elements[i] = x.elements[i + x.index] + y.elements[i + y.index];
			}
			return z;
		}
	}
};

template<typename Type>
Type& Arrays<Type>::operator[](int j) {
	if (j < index || j >= count + index)
		throw "Error, unequal index ";
	else
		return elements[j];
}

template<typename Type>
void Arrays<Type>::print() {  
	cout << endl << "Current options: count = " << count << ", index = " << index << endl;
	cout << "[";
	for (int i = index; i < count + index - 1; i++) {
		cout << elements[i] << "; ";
	}
	cout << elements[count + index - 1] << "]" << endl;
}

template<typename Type>
void Arrays<Type>::setrnd(Type a, Type b) { //заполнение
		for (int i = index; i < count + index; i++){
			elements[i] = (Type)((double)rand() / RAND_MAX* (b - a) + a);
		}
}

template<typename Type>
Type* Arrays<Type>::search(Type key) { //поиск по ключу
	for (int i = index; i < count + index; i++){
		if (elements[i] == key)
			return &elements[i];
	}
	return NULL;
}

template<typename Type>
void Arrays<Type>::sortdown() { //по убыванию
	Type temp;
	for (int i = index; i < count + index - 1; i++){
		for (int j = i + 1; j < count + index; j++){
			if (elements[i] < elements[j]){
				temp = elements[i];
				elements[i] = elements[j];
				elements[j] = temp;
			}
		}
	}
}

template<typename Type>
void Arrays<Type>::sortup() { //по возрастанию
	Type temp;
	for (int i = index; i < count + index - 1; i++){
		for (int j = i + 1; j < count + index; j++){
			if (elements[i] > elements[j]){
				temp = elements[i];
				elements[i] = elements[j];
				elements[j] = temp;
			}
		}
	}
}

int main()
{
	try {
		srand(time(NULL));
		int count, index, key, a, b;
		ofstream fout("text_here.txt");
		do {
			cout << "Set new options: count and index = ";
			cin >> count >> index;
		} while (count <= 0);
		cout << "Set range from a to b: ";
		cin >> a >> b;
		Arrays <int> Two(count, index);
		Two.setrnd(a, b);
		fout << Two;
		Arrays<float> One(count, index);
		One.setrnd(a, b);
		fout << One;
		Arrays <int> Three(Two);
		fout << Three;
		int mas[6] = { 1, 2, 3, 4, 5, 6 };
		Arrays<int> Four(mas, 6);
		fout << Four;
		One.sortup();
		One.print();
		Arrays<int> z(Two);
		z = Two + Three;
		z.print();
		Arrays<int> y(Two);
		y = Two - Three;
		fout << y;
		cout << "Enter key number to search: ";
		cin >> key;
		if (Two.search(key)){
			fout << "Find " << endl;
		}
		else fout << "Not find key: "<<key<<endl;
		fout.close();
	}
	catch (char* message){
		cout <<endl<< message<<endl;
	}
	system("text_here.txt");
	system("exit");
	return 0;
}

