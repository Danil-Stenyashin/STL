# Circular List 

Реализация циклического списка в стиле STL C++20.

## Особенности

- Компилятор с поддержкой C++20
- CMake 3.10+
- Google Test 
- Все стандартные методы и итераторы
- Полная безопасность исключений
- Юнит тесты 

## 📦 Требования
```
| Компонент - Минимальная версия |
| Компилятор      | GCC 10+      |
| CMake           | 3.10+        |
| Google Test     | 1.11+        |
```

## Основные методы
```
Метод	          |       Описание	    | Сложность
push_back(val)    |    Добавление в конец   | O(1)
push_front(val)   |    Добавление в начало  | O(1)
pop_back()        |    Удаление с конца	    | O(1)
insert(pos, val)  |    Вставка элемента     | O(1)*
erase(pos)	  |    Удаление элемента    | O(1)
sort()	          |    Сортировка           | O(n logn)
```

# Клонирование репозитория
git clone https://github.com/Danil-Stenyashin/STL.git

cd STL

## Сборка и тестирование

```bash
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
ctest --output-on-failure
