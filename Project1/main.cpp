#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "functions.h"


using namespace std;
const string file_todo = "todo_list.txt";

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<ToDo> todolist;
    while (true) {
        cout << "\n=== ToDo List Меню ===\n";
        cout << "1. Добавить задачу\n";
        cout << "2. Показать все задачи\n";
        cout << "3. Отметить задачу как выполненную\n";
        cout << "4. Редактировать задачу\n";
        cout << "5. Удалить задачу\n";
        cout << "6. Загрузить задачи из файла\n";
        cout << "7. Поиск задачи\n";
        cout << "8. Статистика\n";
        cout << "9 Резервная копия\n";
        cout << "10. Выход\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;
        cin.ignore(); // Очистка буфера после ввода числа

        switch (choice) {
        case 1: // Добавление задачи
            add_ToDo(todolist, file_todo);
            break;

        case 2: // Показать все задачи
            displaytask(todolist);
            break;

        case 3: // Отметить как выполненную
            markTaskCompleted(todolist, file_todo);
            break;

        case 4: // Редактировать задачу
            edittodo(todolist, file_todo);
            break;

        case 5: // Удалить задачу
            delete_ToDo(todolist, file_todo);
            break;

        case 6: // Загрузить из файла
            loadtasksFile(todolist, file_todo);
            break;
        case 7: // Поиск задачи
            searchTasks(todolist);
            break;
        case 8: // Показ статистики
            showStatistics(todolist);
            break;
        case 9: // Создание резервной копии
            createBackup(todolist);
            break;
        case 10: // Выход
            return 0; // Завершение программы

        default: // Неверный ввод
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}
