#include <iostream>

class Student {
private:
    char *name;
    int age;
    float score;
public:
    char *getName() const {
        return name;
    }

    void setName(char *name) {
        Student::name = name;
    }

    int getAge() const {
        return age;
    }

    void setAge(int age) {
        Student::age = age;
    }

    float getScore() const {
        return score;
    }

    void setScore(float score) {
        Student::score = score;
    }

    void say() {
        std::cout << name << age << score << std::endl;
        printf("%s,%d,%.2f", name, age, score);
    }
};

int main() {
    setlocale(LC_CTYPE, "");
    Student *student = new Student;
    student->setName("wang");
    student->setAge(18);
    student->setScore(100.1);
    student->say();
    return 0;
}