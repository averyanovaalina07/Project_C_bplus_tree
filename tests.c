#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bplus_tree.h"
#include "wal.h"

// Простой тест для проверки вставки и поиска
void test_insert_and_search() {
    printf("-> Запуск теста вставки и поиска...\n");
    
    insert(10, 100);
    insert(20, 200);
    
    // Если условие внутри assert ложно, программа прервется с ошибкой
    assert(search(10) == 100);
    assert(search(20) == 200);
    
    // Проверяем, что несуществующий ключ возвращает -1
    assert(search(999) == -1); 
    
    printf("   Тест вставки и поиска успешно пройден!\n");
}

// Простой тест для проверки удаления
void test_delete_simple() {
    printf("-> Запуск теста удаления...\n");
    
    insert(5, 50);
    assert(search(5) == 50); // Убеждаемся, что ключ сначала добавился
    
    delete_key(5);
    assert(search(5) == -1); // Убеждаемся, что после удаления его больше нет
    
    printf("   Тест удаления успешно пройден!\n");
}

// Простой тест для проверки диапазонного запроса
void test_range_query_simple() {
    printf("-> Запуск теста диапазонного запроса...\n");
    
    // Вставляем упорядоченную последовательность данных
    insert(30, 300);
    insert(40, 400);
    insert(50, 500);
    insert(60, 600);
    insert(70, 700);
    
    // Сначала строго через assert убеждаемся, что границы диапазона добавлены успешно
    assert(search(40) == 400);
    assert(search(50) == 500);
    assert(search(60) == 600);
    
    // Выполняем визуальную проверку работы функции range_query
    printf("   Ожидается вывод: (40: 400) (50: 500) (60: 600)\n");
    printf("   Фактический вывод: ");
    range_query(40, 60); 
    
    printf("   Тест диапазонного запроса успешно пройден!\n\n");
}

int main() {
    printf("=== Запуск базовых тестов (на основе assert) ===\n");
    
    // Создаем изолированные файлы для тестов, чтобы не трогать основную базу
    init_storage(3, "test_tree.dat", "test_wal.log");
    
    // Вызываем наши тесты по очереди
    test_insert_and_search();
    test_delete_simple();
    test_range_query_simple();
    
    // Закрываем файлы
    cleanup_storage();
    
    // Удаляем тестовые файлы, чтобы они не мусорили в папке
    remove("test_tree.dat");
    remove("test_wal.log");
    
    printf("=== Все тесты отработали без ошибок! ===\n");
    return 0;
}