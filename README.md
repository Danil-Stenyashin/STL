# Circular List 

Реализация циклического списка в стиле STL C++20.

## Особенности

- Компилятор с поддержкой C++20
- CMake 3.10+
- Google Test 

## Сборка и тестирование

```bash
mkdir build && cd build
cmake -DBUILD_TESTS=ON ..
make
ctest --output-on-failure
