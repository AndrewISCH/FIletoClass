#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct Dis {
    std::string name;
    unsigned int code;
};

class Student {
    const unsigned int MAX_DIS = 60;
    int disnumber;
    std::string name, surname;
    struct Marks {
        Dis dis;
        int value;
    };
    Marks* ptr = new Marks[MAX_DIS];
public:

    Student(std::string name, std::string surname);
    ~Student();

    void add(std::string dis, int code, int value);

    bool operator < (Student param) {
        double a = 0;
        double b = 0;
        for (int i = 0; i < this->disnumber; i++) {
            a += this->ptr[i].value;
        }
        a /= this->disnumber;
        for (int i = 0; i < param.disnumber; i++) {
            b += param.ptr[i].value;
        }
        b /= param.disnumber;
        if (a < b) {
            return true;
        }
        return false;
    }
    void operator >>(std::ostream& output_stream) {
        output_stream << this->name << " " << this->surname << "\n";
        for (int i = 0; i < this->disnumber; ++i) {
            output_stream << "Discipline: "
                << this->ptr[i].dis.name
                << "  |  Id: " << this->ptr[i].dis.code
                << "  |  Grade: " << this->ptr[i].value << "\n";
        }
    }
    void getminimal();
};
Student::Student(std::string name, std::string surname) {
    this->name = name;
    this->surname = surname;
    this->disnumber = 0;
}

Student::~Student() {
    delete[] ptr;
    ptr = nullptr;
}

void Student::add(std::string dis, int code, int value) {
    if (!(value >= 0 && value <= 100)) {
        std::cout << "Error! Wrong grade value(must be in range 0 to 100)\n";
        return;
    }
    Marks temp;
    temp.dis.name = dis;
    temp.dis.code = code;
    temp.value = value;
    ptr[disnumber++] = temp;
}

void Student::getminimal() {
    if (disnumber == 0) {
        std::cout << "This student don't have disciplines with grades!\n";
        return;
    }
    int min = 101;
    int min_index;
    for (int i = 0; i < disnumber; i++) {
        if (ptr[i].value < min) {
            min = ptr[i].value;
            min_index = i;
        }
    }
    std::cout << "Discipline " << ptr[min_index].dis.name << " has the lowest grade: " << ptr[min_index].value << "\n";
}

void AddToStudent(std::ifstream& input_file, Student& object) {
    
    std::string line, dispname, dispcode, dispgrade;
    getline(input_file, line);
    while (getline(input_file, line)) {
        std::stringstream ss(line);
        ss >> dispname;
        ss >> dispcode;
        ss >> dispgrade;
        object.add(dispname, stoi(dispcode), stoi(dispgrade));
        if (input_file.eof()) {
            return;
        }
    }

}


int main() {
    Student Andrew("Andrii", "Ischenko");
    std::string way;
    while (true) {
        std::cout << "Please, enter your file way.\n";
        std::cin >> way;
        std::ifstream input_file(way);
        if (!input_file.is_open()) {
            std::cout << "Cant open file for reading. Enter your file way again!\n";
            std::cin.clear();
            continue;
        }
        AddToStudent(input_file, Andrew);
        Andrew.getminimal();
        input_file.close();
        break;
    }
    return 0;
}
