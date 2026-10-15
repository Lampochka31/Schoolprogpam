#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <clocale>
using namespace std;

struct Student {
    string fio, group;
    vector<int> grades;
};

struct Group {
    string name;
};

vector<Student> students;
vector<Group> groups;

int findStudent(string fio) {
    for (int i = 0; i < students.size(); i++)
        if (students[i].fio == fio) return i;
    return -1;
}

int findGroup(string name) {
    for (int i = 0; i < groups.size(); i++)
        if (groups[i].name == name) return i;
    return -1;
}

double average(const Student& s) {
    if (s.grades.empty()) return 0;
    double sum = 0;
    for (int g : s.grades) sum += g;
    return sum / s.grades.size();
}

void addStudent() {
    Student s;
    cout << "ФИО: ";
    getline(cin, s.fio);
    cout << "Группа: ";
    getline(cin, s.group);

    if (findStudent(s.fio) != -1 || findGroup(s.group) == -1) {
        cout << "Ошибка данных!\n";
        return;
    }

    students.push_back(s);
    cout << "Студент добавлен.\n";
}

void editStudent() {
    string fio;
    cout << "ФИО студента: ";
    getline(cin, fio);
    int i = findStudent(fio);

    if (i == -1) {
        cout << "Студент не найден.\n";
        return;
    }

    cout << "Новое ФИО: ";
    getline(cin, students[i].fio);
    cout << "Новая группа: ";
    getline(cin, students[i].group);

    if (findGroup(students[i].group) == -1) {
        cout << "Группа не найдена, изменение отменено.\n";
        return;
    }
    cout << "Данные изменены.\n";
}

void deleteStudent() {
    string fio;
    cout << "ФИО студента: ";
    getline(cin, fio);
    int i = findStudent(fio);

    if (i == -1) cout << "Студент не найден.\n";
    else {
        students.erase(students.begin() + i);
        cout << "Студент удален.\n";
    }
}

void addGroup() {
    string name;
    cout << "Название группы: ";
    getline(cin, name);

    if (name.empty() || findGroup(name) != -1)
        cout << "Группа уже существует или название пустое.\n";
    else {
        groups.push_back({ name });
        cout << "Группа добавлена.\n";
    }
}

void editGroup() {
    string name, newName;
    cout << "Старая группа: ";
    getline(cin, name);
    int i = findGroup(name);

    if (i == -1) {
        cout << "Группа не найдена.\n";
        return;
    }

    cout << "Новое название: ";
    getline(cin, newName);

    if (newName.empty() ||
        (newName != name && findGroup(newName) != -1)) {
        cout << "Некорректное название.\n";
        return;
    }

    groups[i].name = newName;
    for (Student& s : students)
        if (s.group == name) s.group = newName;

    cout << "Группа изменена.\n";
}

void deleteGroup() {
    string name;
    cout << "Название группы: ";
    getline(cin, name);
    int i = findGroup(name);

    if (i == -1) {
        cout << "Группа не найдена.\n";
        return;
    }

    for (const Student& s : students)
        if (s.group == name) {
            cout << "В группе есть студенты!\n";
            return;
        }

    groups.erase(groups.begin() + i);
    cout << "Группа удалена.\n";
}

void addGrade() {
    string fio;
    cout << "ФИО студента: ";
    getline(cin, fio);
    int i = findStudent(fio);

    if (i == -1) {
        cout << "Студент не найден.\n";
        return;
    }

    int grade;
    cout << "Оценка (2-5): ";
    cin >> grade;
    cin.ignore(10000, '\n');

    if (grade >= 2 && grade <= 5) {
        students[i].grades.push_back(grade);
        cout << "Оценка добавлена.\n";
    }
    else cout << "Неверная оценка.\n";
}

void showStudentAverage() {
    string fio;
    cout << "ФИО студента: ";
    getline(cin, fio);
    int i = findStudent(fio);

    if (i == -1) cout << "Студент не найден.\n";
    else if (students[i].grades.empty())
        cout << "У студента нет оценок.\n";
    else
        cout << fixed << setprecision(2)
        << "Средний балл: " << average(students[i]) << '\n';
}

void showGroupAverage() {
    string name;
    cout << "Название группы: ";
    getline(cin, name);

    if (findGroup(name) == -1) {
        cout << "Группа не найдена.\n";
        return;
    }

    double sum = 0;
    int count = 0;

    for (const Student& s : students)
        if (s.group == name && !s.grades.empty()) {
            sum += average(s);
            count++;
        }

    if (count == 0) cout << "Нет оценок.\n";
    else cout << fixed << setprecision(2)
        << "Средний балл группы: " << sum / count << '\n';
}

void statistics() {
    string name;
    cout << "Название группы: ";
    getline(cin, name);

    if (findGroup(name) == -1) {
        cout << "Группа не найдена.\n";
        return;
    }

    int excellent = 0, good = 0, other = 0, empty = 0, total = 0;

    for (const Student& s : students) {
        if (s.group != name) continue;
        total++;

        if (s.grades.empty()) {
            empty++;
            continue;
        }

        double a = average(s);
        if (a >= 4.5) excellent++;
        else if (a >= 3.5) good++;
        else other++;
    }

    cout << "Всего студентов: " << total
        << "\nОтличники: " << excellent
        << "\nХорошисты: " << good
        << "\nОстальные: " << other
        << "\nБез оценок: " << empty << '\n';
}

void showStudents() {
    for (const Student& s : students) {
        cout << "\n" << s.fio << " | " << s.group << " | ";
        if (s.grades.empty()) cout << "нет оценок";
        else {
            for (int g : s.grades) cout << g << " ";
            cout << "| Средний балл: " << average(s);
        }
        cout << '\n';
    }
}

void showGroups() {
    for (const Group& g : groups) {
        int count = 0;
        for (const Student& s : students)
            if (s.group == g.name) count++;
        cout << g.name << " | Студентов: " << count << '\n';
    }
}

void init() {
    groups = { {"БД-1-25"}, {"ИС-2-25"} };
    students = {
        {"Иванов Иван Иванович", "БД-1-25", {5,5,5,5}},
        {"Петров Петр Петрович", "БД-1-25", {4,4,5,4}},
        {"Сидоров Алексей Сергеевич", "БД-1-25", {3,3,4,3}},
        {"Смирнова Анна Ивановна", "ИС-2-25", {5,4,5,5}}
    };
}

int main() {
    setlocale(LC_ALL, "");
    init();
    int n;

    do {
        cout << "\n--- МЕНЮШКА ---\n"
            << "1. Добавить студента\n"
            << "2. Изменить студента\n"
            << "3. Удалить студента\n"
            << "4. Добавить группу\n"
            << "5. Изменить группу\n"
            << "6. Удалить группу\n"
            << "7. Добавить оценку\n"
            << "8. Средний балл студента\n"
            << "9. Средний балл группы\n"
            << "10. Статистика группы\n"
            << "11. Список студентов\n"
            << "12. Список групп\n"
            << "0. Выход\n"
            << "Выбор: ";
        cin >> n;
        cin.ignore(10000, '\n');

        switch (n) {
        case 1: addStudent(); break;
        case 2: editStudent(); break;
        case 3: deleteStudent(); break;
        case 4: addGroup(); break;
        case 5: editGroup(); break;
        case 6: deleteGroup(); break;
        case 7: addGrade(); break;
        case 8: showStudentAverage(); break;
        case 9: showGroupAverage(); break;
        case 10: statistics(); break;
        case 11: showStudents(); break;
        case 12: showGroups(); break;
        case 0: cout << "Выход.\n"; break;
        default: cout << "Нет такого пункта.\n";
        }
    } while (n != 0);

    return 0;
}
