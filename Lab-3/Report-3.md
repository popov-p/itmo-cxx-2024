# Лабораторная работа №2
**Дисциплина:** Программирование на С++  
**Тема:** Работа со стандартной библиотекой шаблонов.  
**Выполнил:** Попов П.С.  
**Группа:** P4116  
**Преподаватель:** Лаздин А.В.  
**Дата:** 28.11.2024

## Цель работы

1. Создать вектор v1 размером от 500 до 1000 элементов, число элементов не известно до запуска программы. Элементами вектора являются экземпляры класса из Л.Р. №2 имеющие произвольные(случайные) значения. В случае необходимости этот класс должен быть доработан для возможности решать поставленные в этой ЛР задачи.

2. Создать вектор v2, поместив в него последние 200 элементов вектора v1. Рассмотрите решение для произвольных b и e, которые задают позиции первого и последнего копируемых элементов.

3. Сформировать список list1, поместив в него первые n (от 20 до 50) наибольших элементов вектора v1 (указанные элементы должны быть отсортированы до помещения их в список).
4. Сформировать список list2, поместив в него последние n (от 20 до 50) наименьших элементов вектора v2, порядок элементов не важен.
5. Удалить из векторов v1 и v2 перемещенные элементы. Скорректируйте размеры векторов после удаления из них элементов.
6. Для списка list1 найти элемент со средним значением. Перегруппировать элементы списка так, чтобы в начале оказались все элементы, большие среднего значения.
7. Удалите из списка list2 все нечётные элементы (или используйте другой критерий, который однозначно делит экземпляры вашего класса на два непересекающихся множества).
8. Создайте вектор v3 из элементов, которые присутствуют и в векторе v1 и в векторе v2.
9. Для списков list1 и list2 из списка с большим числом элементов удалите первые n так, чтобы оба списка имели бы одинаковый размер. Сформируйте из них список list3, который будет хранить пары <первый элемент списка list1, первый элемент списка list2>, <второй элемент списка list1, второй элемент списка list2>  и т. д.
10. Решите предыдущую задачу для векторов v1 и v2 без предварительного приведения векторов к одному размеру. Пар с пустыми значениями быть не должно.


## Структура программы

`number.h`, `number.cpp` - модифицированный для работы с текущей ЛР класс `Number`. Содержит, как и раньше, числовое значение `int` и строку с текстовым значением `char *`. Заметим, что данной лабораторной работе класс `Number` для упрощения задачи будет хранить вместо истинного текстового описаний строку с рандомно сгенерированным набором символов.

`utilities.h`, `utilities.cpp` - набор реализаций подпунктов текущего задания.

`main.cpp` - точка входа в программу и запуск тестовых сценариев.


## Листинг кода с комментариями
Ниже приведнён код программы с отдельными наиболее важными комментариями к происходящему. 

- Генерация случайного описания для отдельно взятого объекта класса `Number`. Вспомогательная функция.
```cpp
std::string generateRandomString(size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "0123456789";
    const size_t max_index = sizeof(charset) - 1;
    std::string random_string;
    random_string.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        random_string += charset[std::rand() % max_index];
    }

    return random_string;
}
```
- Заполнение вектора размером `vector_size`, выбирающегося случайным образом от `500` до `1000` вне функции.
Строки с описанием генерируются рандомно размера `5`. 
```cpp
std::vector<Number> step1(const size_t& vector_size) {
    std::vector<Number> v1;
    for (size_t i = 0; i < vector_size; ++i) {
        v1.emplace_back(std::rand() % 1001, generateRandomString(5).c_str());
    }
    return v1;
}
```
- Копирование произвольного количества элементов из вектора `v1` в вектор `v2` (который создаётся в этой функции).
```cpp
std::vector<Number> step2(const std::vector<Number>& v1) {
    size_t b = std::rand() % v1.size();
    size_t e = b + 1 + (std::rand() % (v1.size() - b));
    std::vector<Number> v2(v1.begin() + b,
                           v1.begin() + e);
    return v2;
}
```

- Создание листа `l1` по заданному критерию в программе. Сначала случайным образом выбирается размер `n`. Если случайно сгенерированный размер `n` больше, чем размер `v1`, то берётся размер вектора.
Чтобы избежать лишних копирований, выполним `std::partial_sort` прямо внутри вектора по убыванию.
Первые `n` элементов внутри вектора окажутся наибольшими. Из них мы и составим `l1` при помощи `std::copy`.
Вернём из функции размер `n` для дальнейшего использования в п.5.
```cpp
std::pair<std::list<Number>, size_t> step3(std::vector<Number>& v1) {
    auto n = 20 + (std::rand() % (50 - 20 + 1));
    n = std::min(n, static_cast<int>(v1.size()));
    std::partial_sort(v1.begin(), v1.begin() + n, v1.end(), std::greater<Number>());

    std::list<Number> list1;
    std::copy(v1.begin(), v1.begin() + n , std::back_inserter(list1));

    return {list1, n};
}
```
- Отличие от п.3 п.4 заключается в том, что применяется стандартный порядок сортировки по возрастанию. В задании указано, что порядок элементов не важен, главное, чтобы элементы были "последние наименьшие". Поскольку используется определение "наименьшие", то всё равно необходима сортировка. 
Ф-я `std::nth_element` здесь неприменима.  
```cpp
std::pair<std::list<Number>, size_t> step4(std::vector<Number>& v2) {
    auto n = 20 + (std::rand() % (50 - 20 + 1));
    n = std::min(n, static_cast<int>(v2.size()));
    std::partial_sort(v2.begin(), v2.begin() + n, v2.end());

    std::list<Number> list2;
    std::copy(v2.begin(), v2.begin() + n, std::back_inserter(list2));

    return {list2, n};
}
```
- Удаление нужного количества элементов из вектора. Информацию о том, сколько элементов нужно удалить, получаем из п.п. 3-4.
```cpp
void step5(std::pair<std::vector<Number>, size_t> p1,
           std::pair<std::vector<Number>, size_t> p2) {
    p1.first.erase(p1.first.begin(), p1.first.begin() + p1.second);
    p2.first.erase(p2.first.begin(), p2.first.begin() + p2.second);
}
```
- Описание к этому подпункту приведено как комментарий в c++ коде. Перегрузки операторов `+`, `/`. Приложены.
```cpp
void step6(std::list<Number>& l1) {
    Number sum = std::accumulate(l1.begin(), l1.end(), Number{0, "zero"});
    Number average = sum / l1.size();
    std::vector<Number> vec(l1.begin(), l1.end());

    auto partition_point = std::partition(vec.begin(), vec.end(),
                                          [average](const Number& num) {
                                              return num > average;
                                          });

    /* Заметим, что если в п. 3 сразу сделать "правильное" копирование при помощи std:back_inserter(list1),
     * то п.6 выполняется уже автоматически.
     * Для "демонстрации навыков работы с stl" я посчитал среднее значение и определил операторы >, /,
     * однако этого можно было вовсе не делать.
    */
}

Number operator+(const Number& lhs, const Number& rhs) {
    int new_value = lhs.value + rhs.value;

    size_t length_lhs = std::strlen(lhs.text);
    size_t length_rhs = std::strlen(rhs.text);
    size_t new_text_length = (length_lhs + length_rhs) / 2;

    char* new_text = new char[new_text_length + 1];
    for (size_t i = 0; i < new_text_length; ++i) {
        new_text[i] = 'a' + std::rand() % 26;
    }
    new_text[new_text_length] = '\0';

    Number result(new_value, new_text);

    delete[] new_text;

    return result;
}

Number operator/(const Number& lhs, size_t divisor) {
    if (divisor == 0) {
        throw std::runtime_error("Division by zero");
    }

    int new_value = lhs.value / static_cast<int>(divisor);

    char* new_text = new char[std::strlen(lhs.text) + 1];
    std::strcpy(new_text, lhs.text);

    Number result(new_value, new_text);

    delete[] new_text;

    return result;
}
```
- Удаление нечётных элементов из `l2`. Перегрузка операторов приложена.
```cpp
void step7(std::list<Number>& l2) {
    lc2.remove_if([](const Number& num) {
        return num % 2 != 0;
    });
}
bool operator%(const Number& num, int divisor) {
    if (divisor == 0) {
        throw std::invalid_argument("Division by zero is not allowed in operator %");
    }
    return num.value % divisor != 0;
}
```
- Создание вектора `v3` как объединение векторов `v1` и `v2` при помощи `std::set_union`. 

По документации известно, что если вызвать `std::set_union` от несортированных входных контейнеров, то будет `undefined behavior`, поэтому отсортируем входные контейнеры.

```cpp
std::vector<Number> step8(std::vector<Number>& v1, std::vector<Number>& v2) {
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<Number> v3;

    /* std::set_union обязательно требует сортировки */
    std::set_union(v1.begin(), v1.end(),
                   v2.begin(), v2.end(),
                   std::back_inserter(v3));

    return v3;
}
```
- По заданию требуется сократить размер большего `list_{i}` до размера меньшего. Затем сформируем лист пар `list3`. В этой функции необходимо создать копии векторов, т.к. далее по заданию в п.10 требуется неизменённое состояние листов.
```cpp
std::list<std::pair<Number, Number>> step9(const std::list<Number>& l1, const std::list<Number>& l2) {
    auto l1_copy = l1;
    auto l2_copy = l2;

    size_t diff = std::abs(static_cast<int>(l1_copy.size()) - static_cast<int>(l2_copy.size()));

    if (l1_copy.size() > l2_copy.size()) {
        auto it = l1_copy.begin();
        std::advance(it, diff);
        l1_copy.erase(l1_copy.begin(), it);
    } else if (l2_copy.size() > l1_copy.size()) {
        auto it = l2_copy.begin();
        std::advance(it, diff);
        l2_copy.erase(l2_copy.begin(), it);
    }

    std::list<std::pair<Number, Number>> l3;

    std::transform(l1_copy.begin(), l1_copy.end(),
                   l2_copy.begin(), std::back_inserter(l3),
                   [](const Number& n1, const Number& n2) {
                       return std::make_pair(n1, n2);
                   });

    return l3;
}
```
- Рещение предыдущей задачи без приведения векторов к ондому размеру.
```cpp
std::vector<std::pair<Number, Number>> step10(std::list<Number>& l1, std::list<Number>& l2) {
    size_t n = std::min(l1.size(), l2.size());

    auto it1 = l1.begin();
    auto it2 = l2.begin();

    std::vector<std::pair<Number, Number>> list3;

    std::transform(it1, std::next(it1, n), it2, std::back_inserter(list3),
                   [](const Number& n1, const Number& n2) {
                       return std::make_pair(n1, n2);
                   });

    return list3;
}
```
- Наконец, сам запуск подпунктов задания (тест-кейсов).
```cpp
int main () {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    const size_t vector_size = 500 + std::rand() % 501;

    std::vector<Number> v1 = step1(vector_size);
    std::vector<Number> v2 = step2(v1);

    auto l1_pair = step3(v1);
    auto  l2_pair = step4(v2);

    step5({v1, l1_pair.second},
          {v2, l2_pair.second});


    step6(l1_pair.first);
    step7(l1_pair.first);

    step8(v1, v2);
    auto l3 = step9(l1_pair.first, l2_pair.first);
    auto l3_ver3 = step10(l1_pair.first, l2_pair.first);

    return 0;
}
```
## Выводы
Решение задач производилось по следующему алгоритму принятия решений:
1. Минимизируется написание ручных обходов (циклов, итераций и пр.)
2. Максимизируется использование инструментария `STL`.
3. Избегаются лишние создания копий и/или нерациональная растрата ресурсов.
## Исходный код

https://github.com/popov-p/itmo-cxx-2024, папка Lab-3.
