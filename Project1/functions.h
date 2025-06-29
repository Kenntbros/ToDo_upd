#pragma once
#include <iostream>
#include <fstream>
#include <String>
#include <vector>
#include <limits>

using namespace std;
struct ToDo { // структура ну это и так понятно я думаю :-)
	string name;
	string date;
	string description;
	bool is_complete; // это для определения выполнено или нет, true - если выполнено и false - если не выполнено
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(); // функция для очистки буфера ввода(взял с интернета)
}

void add_ToDo(vector<ToDo>& todolist, string file_todo) {
	// добавление в массив новой задачи
	ToDo newTask;
	cout << "Введите название задачи: ";
	getline(cin, newTask.name);
	cout << "Введите  дату (ДД.ММ.ГГГГ): ";
	getline(cin, newTask.date);
	cout << "Введите описание: ";
	getline(cin, newTask.description);
	newTask.is_complete = false; // по умолчанию не выполнена задача поэтому false
	todolist.push_back(newTask); // добавление в массив 

	//теперь добавление в файл
	ofstream outFile(file_todo, ios::app); // открытие файла 
	if (!outFile) { // проверяем удалось ли открыть файл для записи
		cout << "Ошибка!"; 
		return; // завершает программу при ошибке
	}
	outFile << newTask.name << "\n";
	outFile << newTask.date << "\n";
	outFile << newTask.description << "\n";
	outFile << newTask.is_complete << "\n";
	outFile.close();
	cout << "Задача успешно добавлена!\n";
}



void rewriteTaskFile(vector<ToDo>& todolist,string file_todo) { //  вспомогательная функция для полного перезаписывания файла
    ofstream outFile(file_todo); 
    if (!outFile) {
        cout << "Ошибка при открытии файла для записи.\n";
        return;
    }

    for (const auto& task : todolist) {
        outFile << task.name << "\n";
        outFile << task.date << "\n";
        outFile << task.description << "\n";
        outFile << task.is_complete << "\n";
    }

    outFile.close();
}

void displaytask(vector<ToDo>& todolist) {
    // проверяем пуст ли список задач
    if (todolist.empty()) {
        cout << "Список задач пуст.\n";
        return; // выход из функции если нет задач
    }

    cout << "\n=== СПИСОК ВСЕХ ЗАДАЧ ===\n";
    cout << "--------------------------------------------------\n";
    // проходим по всем задачам в векторе
    for (size_t i = 0; i < todolist.size(); ++i) {
        cout << "ID: " << i + 1 << "\n";
        cout << "Название: " << todolist[i].name << "\n";
        cout << "Дата исполнения: " << todolist[i].date << "\n";
		cout << "Описание: " << todolist[i].description << "\n";
        // выводим статус выполнения (тернарный оператор для выбора текста)
        cout << "Статус: " << (todolist[i].is_complete ? "✅ Выполнено" : "❌ Не выполнено") << "\n";
        cout << "--------------------------------------------------\n";
    }
    // выводим общее количество задач
    cout << "Всего задач: " << todolist.size() << "\n\n";
}

void edittodo(vector<ToDo>& todolist, string file_todo) {
    if (todolist.empty()) {
        cout << "Список задач пуст.\n";
        return;
    }

    // показываем все задачи с нумерацией
    displaytask(todolist);

    // запрашиваем ID задачи для редактирования
    cout << "Введите ID задачи для редактирования: ";
    size_t id;
    cin >> id;
    clearInputBuffer();

    // проверяем корректность ID
    if (id < 1 || id > todolist.size()) {
        cout << "Неверный ID задачи.\n";
        return;
    }

    // получаем ссылку на редактируемую задачу
    ToDo& task = todolist[id - 1];

    // редактирование названия
    cout << "Текущее название: " << task.name << endl;
    cout << "Введите новое название (или оставьте пустым чтобы сохранить текущее): ";
    string input;
    getline(cin, input);
    if (!input.empty()) {
        task.name = input;
    }

    // редактирование даты
    cout << "Текущая дата исполнения: " << task.date << endl;
    cout << "Введите новую дату (ДД.ММ.ГГГГ) (или оставьте пустым): ";
    getline(cin, input);
    if (!input.empty()) {
        task.date = input;
    }

    // редактирование описания
    cout << "Текущее описание: " << task.description << endl;
    cout << "Введите новое описание (или оставьте пустым): ";
    getline(cin, input);
    if (!input.empty()) {
        task.description = input;
    }

    // редактирование статуса
    cout << "Текущий статус: " << (task.is_complete ? "Выполнено" : "Не выполнено") << endl;
    cout << "Изменить статус? (1 - да, 0 - нет): ";
    int statusChoice;
    cin >> statusChoice;
    clearInputBuffer();

    if (statusChoice == 1) {
        task.is_complete = !task.is_complete;
    }

    // сохраняем изменения в файл
    rewriteTaskFile(todolist, file_todo);

    cout << "Задача успешно обновлена!\n";
}

void markTaskCompleted(vector<ToDo>& todolist, string file_todo) {
    if (todolist.empty()) {
        cout << "Список задач пуст.\n";
        return;
    }

    // показываем все задачи
    displaytask(todolist);

    // запрашиваем ID задачи
    cout << "Введите ID задачи для изменения статуса: ";
    size_t id;
    cin >> id;
    clearInputBuffer();

    // проверяем корректность ID
    if (id < 1 || id > todolist.size()) {
        cout << "Неверный ID задачи.\n";
        return;
    }

    // изменяем статус задачи
    ToDo& task = todolist[id - 1];
    task.is_complete = !task.is_complete; // Переключаем статус

    // сообщаем о результате
    cout << "Задача \"" << task.name << "\" теперь помечена как "
        << (task.is_complete ? "выполненная" : "не выполненная") << ".\n";

    // сохраняем изменения в файл
    rewriteTaskFile(todolist, file_todo);
}

void loadtasksFile(vector<ToDo>& todolist, string file_todo) {
    ifstream inFile(file_todo);
    if (!inFile) {
        cout << "Файл не найден. Будет создан новый при сохранении.\n";
        return;
    }

    todolist.clear();
    string line;
    ToDo task;
    while (getline(inFile, task.name) &&
        getline(inFile, task.date) &&
        getline(inFile, task.description)) {
        inFile >> task.is_complete;
        inFile.ignore();
        todolist.push_back(task);
    }
    inFile.close();
    cout << "Задачи загружены из файла!\n";
}

void delete_ToDo(vector<ToDo>& todolist, string file_todo) {
	if (todolist.empty()) {
		cout << "Список задач пуст\n";
		return;

	}
    displaytask(todolist);
    cout << "Введите ID задачи для удаления: ";

    size_t id;
    cin >> id;
    clearInputBuffer();

    if (id < 1 || id > todolist.size()) {
        cout << "Неверный ID задачи.\n";
        return;
    }

    // удаляем задачу из массива
    todolist.erase(todolist.begin() + id - 1);

    // перезаписываем весь файл с обновленным списком
    rewriteTaskFile(todolist, file_todo);

    cout << "Задача успешно удалена из списка и файла!\n";


}
void searchTasks(const vector<ToDo>& todolist) { // поиск задач
    cout << "Введите текст для поиска: ";
    string query;
    getline(cin, query);
    bool found = false;
    for (const auto& task : todolist) {
        if (task.name.find(query) != string::npos ||
            task.description.find(query) != string::npos) {
            // вывод заголовка при первом совпадении
            if (!found) {
                cout << "\nРезультаты поиска:\n";
                cout << "----------------------------------------\n";
                found = true;
            }
            // вывод информации о задаче
            cout << "Название: " << task.name << "\n";
            cout << "Описание: " << task.description << "\n";
            cout << "Дата: " << task.date << "\n";
            cout << "Статус: " << (task.is_complete ? "Выполнено" : "Не выполнено") << "\n";
            cout << "----------------------------------------\n";
        }
    }
    if (!found) {
        cout << "Задачи с таким текстом не найдены.\n";
    }
}
void showStatistics(const vector<ToDo>& todolist) {
    int completed = 0;
    for (const auto& task : todolist) {
        if (task.is_complete) completed++; // если задание выполнено то добовляеться в статистику
    }
    cout << "----------------------------------------\n";
    cout << "Всего задач: " << todolist.size() << endl;
    cout << "Выполнено: " << completed << endl;
    cout << "Осталось: " << todolist.size() - completed << endl;
    cout << "Процент выполнения: "
        << (todolist.empty() ? 0 : (100 * completed / todolist.size()))
        << "%" << endl;
    cout << "----------------------------------------\n";
}
void createBackup(const vector<ToDo>& todolist) {
    // создаем имя файла с текущей датой-временем
    string backupFile = "backup_" + to_string(time(0)) + ".txt";

    // открываем файл для записи
    ofstream backup(backupFile);
    if (!backup) {
        cout << "Ошибка создания резервной копии!\n";
        return;
    }

    // записываем все задачи в файл в том же формате, что и в основном файле
    for (const auto& task : todolist) {
        backup << task.name << "\n";
        backup << task.date << "\n";
        backup << task.description << "\n";
        backup << task.is_complete << "\n";
    }
    backup.close();
    cout << "Резервная копия успешно создана: " << backupFile << "\n";
}