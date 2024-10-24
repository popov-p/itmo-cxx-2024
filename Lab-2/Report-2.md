# Лабораторная работа №2
**Дисциплина:** Программирование на С++  
**Тема:** Работа с памятью. Работа с конструкторами/деструктором языка C++. Перегрузка операторов.   
**Выполнил:** Попов П.С.  
**Группа:** P4116  
**Преподаватель:** Лаздин А.В.  
**Дата:** 23.10.2024

## Цель работы
1. Необходимо спроектировать класс, реализующий хранение данных, связанных с экземпляром класса в динамической памяти. 
2. Для данного класса реализовать все необходимые конструкторы, включая конструкторы копирования и перемещения, деструктор.
3. Написать программу, осуществляющую работу с экземплярами разработанного класса, которая должна демонстрировать:
    - создание статических и динамических экземпляра класса, стандартного вектора в стиле Си, написать функцию для обработки данного вектора;
    - передача экземпляров класса в функцию, и возврат экземпляра из функции; включая вариант с передачей и возвратом значений типа ссылки на класс;
    - продемонстрировать работу с разработанным классом, создавая вектора и списки экземпляров класса, используя стандартные классы vector и list длиной от 5 до 10.

## Структура программы
`number.cpp` `number.h` - разработанный класс `Number` по заданию.
`test.cpp`, `test.h` - файлы с "тестовыми" функциями (примерам работы с разработанным классом).
## Пример работы программы
```
[pavel@pavel-lt build]$ ./Lab-2 
Number stackNumber(100, "one hundred")
Constructor
--------------------------------------------------------
Number staticNumber(100, "one hundred")
Constructor
--------------------------------------------------------
Number* dynamicNumber = new Number(200, "two hundred")
Constructor
--------------------------------------------------------
Number* numberArray = new Number[size] ... (c-style)
Constructor
Constructor
Constructor
Default constructor
--------------------------------------------------------
std::cout << numberArray[0] << std::endl;
(<<) Value: 1, Text: One
--------------------------------------------------------
delete[] numberArray;
Destructor
Destructor
Destructor
Destructor
--------------------------------------------------------
createVector(size), processVector(...), deleteVector(...) (c-style)
Default constructor
Default constructor
Default constructor
Default constructor
Constructor
Assignment operator (move)
Destructor
Constructor
Assignment operator (move)
Destructor
Constructor
Assignment operator (move)
Destructor
Constructor
Assignment operator (move)
Destructor
---
Value: 10, Text: Ten
Value: 20, Text: Twenty
Value: 30, Text: Thirty
Value: 30, Text: Fourty
---
Destructor
Destructor
Destructor
Destructor
--------------------------------------------------------
std::vector<Number> numbers = createVector()
Constructor
Move constructor
Destructor
---
Constructor
Move constructor
Move constructor
Destructor
Destructor
---
Constructor
Move constructor
Move constructor
Destructor
Move constructor
Destructor
Destructor
---
Constructor
Move constructor
Destructor
---
Constructor
Move constructor
Move constructor
Destructor
Move constructor
Destructor
Move constructor
Destructor
Move constructor
Destructor
Destructor
---
--------------------------------------------------------
processVector(numbers)
Value: 1, Text: one
Value: 2, Text: two
Value: 3, Text: three
Value: 4, Text: four
Value: 5, Text: five
--------------------------------------------------------
numbers.push_back(stackNumber)
Copy constructor
--------------------------------------------------------
numbers.push_back(*dynamicNumber)
Copy constructor
--------------------------------------------------------
std::list<Number> numberList = {Number(10, "ten"), Number(20, "twenty"), Number(30, "thirty")}
Constructor
Constructor
Constructor
Copy constructor
Copy constructor
Copy constructor
Destructor
Destructor
Destructor
--------------------------------------------------------
for (auto& num : numberList) { num.print(); }
Value: 10, Text: ten
Value: 20, Text: twenty
Value: 30, Text: thirty
--------------------------------------------------------
Number returnedByValue = processVal(stackNumber)
Copy constructor
Value: 100, Text: one hundred
Move constructor
Destructor
--------------------------------------------------------
Number& returnedByReference = processRef(*dynamicNumber)
Value: 200, Text: two hundred
--------------------------------------------------------
delete dynamicNumber
Destructor
--------------------------------------------------------
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
Destructor
```
## Комментарии к результату.
0. В целом, для меня механика работы конструкторов, деструктора и операторов понятна.
1. Деструкторы вызываются в порядке обратном определению переменных.
2. Интересно отметить участок кода программы, создающий c++ контейнер вектор переменных типа `Number`.
    - Вектор - это динамический массив с автоматическим менеджментом памяти.
    - Внутри вектора реализована такая механика: если контейнер заполнен до некоторого пороговоро значения (доподлинно неизвестно, какое, вроде бы 60%), то вызывается переаллокация всего содержимого вектора на размер (насколько я знаю, x2 от того, что был до переаллокации.)
    - `push_back(<arg>)` вызывает конструктор копирования. Это не всегда желаемое поведение. Если копирование нужно избежать, используем `emplace_back(<arg>)`.

## Исходный код

https://github.com/popov-p/itmo-cxx-2024, папка Lab-2.
