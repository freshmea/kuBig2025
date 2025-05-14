from dataclasses import dataclass


@dataclass
class StudentData:
    name: str
    korean: int
    math: int
    english: int
    science: int
    num: int = 4


class Student:
    def __init__(self, arg: StudentData):
        self.name = arg.name
        self.korean = arg.korean
        self.math = arg.math
        self.english = arg.english
        self.science = arg.science
        self.num = arg.num

    def student_get_sum(self):
        return self.korean + self.math + self.english + self.science

    def student_get_average(self):
        return self.student_get_sum() / self.num

    def student_to_string(self):
        return f"{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}"


class GraduateStudent:
    def __init__(self, arg: StudentData):
        self.name = arg.name
        self.korean = arg.korean
        self.math = arg.math
        self.english = arg.english
        self.science = arg.science
        self.num = arg.num

    def student_get_sum(self):
        return self.korean + self.math + self.english + self.science

    def student_get_average(self):
        return self.student_get_sum() / self.num

    def student_to_string(self):
        return f"{self.name}\t{self.student_get_sum()}\t{self.student_get_average()}"


def main():
    students = []
    graduateStudents = []
    with open("/home/aa/kuBig2025/python/basic/students.txt", "r") as f:
        while data := f.readline():
            split_data = data.split()
            students.append(
                Student(
                    StudentData(
                        split_data[0],
                        int(split_data[1]),
                        int(split_data[2]),
                        int(split_data[3]),
                        int(split_data[4]),
                    )
                )
            )
            graduateStudents.append(
                GraduateStudent(
                    StudentData(
                        split_data[0],
                        int(split_data[1]),
                        int(split_data[2]),
                        int(split_data[3]),
                        int(split_data[4]),
                    )
                )
            )

    for student in students:
        print(student.student_to_string())
    for student in graduateStudents:
        print(student.student_to_string())


if __name__ == "__main__":
    main()
