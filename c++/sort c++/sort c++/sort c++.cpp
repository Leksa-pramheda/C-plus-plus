// sort c++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
using namespace std;

const int max = 1300;

int nop = 0; // Счетчик количества проделанных операций

class Stack
{
    int top; // Указатель на последний элемент
public:

    int a[max]; // Максимальное количество элементов в стеке
    Stack() { top = -1; nop += 1; } // 1
    ~Stack() { top = -1; }
    bool push(int x); // 5
    int pop(); // 3
    bool isEmpty(); // 1
    int length(); // 2
};

bool Stack::push(int x) // 5
{
    if (top >= (max - 1)) // 2
    {
        return false;
    }
    else
    {
        a[++top] = x; // 3
        nop += 5;
        return true;
    }
}

int Stack::pop() // 3
{
    if (top < 0) // 1
    {
        return 0;
    }
    else
    {
        nop += 3;
        return a[top--]; //2
    }
}

bool Stack::isEmpty() // 1
{
    nop += 1;
    return (top < 0); // 1
}

int Stack::length() // 2
{
    nop += 2;
    return top + 1;
} // 2

// —----------------------------------------------------—

Stack soedini(Stack s1, Stack s2) //3+2*(2+8(n-1))=3+4+16n-16=16n-9
{
    class Stack tmp; // 1

    nop += 1;

    while (!s1.isEmpty()) //2+             
    {
        tmp.push(s1.pop()); // (pop+push)*(n-1) (=8n-8) 
        nop += 8;
    }// 8n-6

    while (!tmp.isEmpty()) //2
    {
        s2.push(tmp.pop()); // (pop+push)*(n-1) (=(n-1)*(5+3))
        nop += 8;
    }// 8n-6

    return s2;//1
}

Stack quickSort(Stack s) // 9 + (2 + 19n) + (7+quicksort(n-1)+ 8+quicksort(n-1)+11+2*quicksort(n-1)/2)) * (16n-8)
{  //=11+19n+(16n-8)*(26+2*log(n)+2*log(n-1)/2)
    if (s.length() <= 1) //size+1 =2
    {
        nop += 2;
        return s;//1
    }

    class Stack left; // 1
    class Stack right; // 1
    int dop_elem = s.pop(); // pop+1 (=4)

    nop += 6;

    // Разбиваем стек на 2 стека
    while (!s.isEmpty()) // 2 + (4+7+8) * n =2+19n
    {
        int a = s.pop(); // pop+1 (=4)

        nop += 4;

        if (a < dop_elem) // 1
        {
            left.push(a); // push+1 (=6)
            nop += 7;
        }
        else if (a >= dop_elem) //1+ 1 (=2)
        {
            right.push(a); // push+1 (=6)
            nop += 8;
        }
    }

    // Разбираемся куда поместить dop_elem
    // и рекурсивно продолжаем сортировать
    // 2+
    // 7+quicksort(n-1)+ 8+quicksort(n-1)+11+2*quicksort(n-1)/2
    if (left.isEmpty()) // empty+1 =2
    {
        left.push(dop_elem); // push+1 (=6)
        right = quickSort(right); // 1 + quicksort(n-1)
        nop += 7;
    }
    else if (right.isEmpty()) //(empty+1)=2
    {//+1
        right.push(dop_elem); // push+1 (=6)
        left = quickSort(left); // 1 + quicksort(n-1)
        nop += 8;//
    }
    else // empty+1+1 = 3
    {
        left = quickSort(left); // 1 + quicksort((n-1)/2) 
        right = quickSort(right); // 1 + quicksort((n-1)/2) 
        right.push(dop_elem); // push+1 (=6)
        nop += 11;
    }

    return soedini(left, right); //1+ 16n-9 = 16n-8
}

/*
3 + 8n + 14 + 6n + 11 + 8n + (27 + n/3*(log(n) + log((n-1)/2))) * (8 + 14(n-1)) =
= 28 + 22n + (27 + n/27*(log(n) + log((n-1)/2))) * (14n - 6)
//=11+19n+(16n-8)*(26+2*log(n)+2*log(n-1)/2)
F(n) =11+19n+(16n-8)*(26+2*log(n)+2*log(n-1)/2)
Переводя в нотацию O(n):
O(F(n)) = n*log(n)
*/

int main()
{

    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    Stack s; // 1
    int shet = 0;
    int N = 12000;
    // Заполняем стек рандомными числам
    cout << "До сортировки" << endl;
    int elem = 0;
    for (int i = 1; i <= N; i++)
    {
        elem = rand() % 1000;
        s.push(elem);
        cout << elem << endl;
    } // 2+3n
    clock_t start_time = clock();
    s = quickSort(s); //
    clock_t end_time = clock();
    cout << endl;
    cout << "После сортировки" << endl;
    while (!s.isEmpty())
        cout << s.pop() << endl;
    cout << endl;
    cout << "NOP " << nop << endl;
    //shet++;

    cout << " Колличество отсортированных элементов: " << N << " Время сортировки: " << (double)(end_time - start_time) / ((double)CLOCKS_PER_SEC) << " Колличество операций (N_op): " << nop << endl;

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
