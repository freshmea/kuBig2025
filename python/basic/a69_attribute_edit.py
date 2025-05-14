# descriptor 기술을 하는 자 (기술자.)
import json
from dataclasses import dataclass, field
from pathlib import Path


@dataclass
class StudentData:
    name: str = ""
    korean: int = 0
    math: int = 0
    english: int = 0
    science: int = 0
    art: int = 0
    scores: dict = field(default_factory=dict)
    score_set: list = field(default_factory=list)

    @classmethod
    def from_json(cls, file):
        param_dir = r"/home/aa/kuBig2025/python/basic"
        with open(Path(param_dir) / file, "r", encoding="utf8") as f:
            data: dict = json.loads(f.read())  # dictionary
        subjects = set()
        for item in data:
            subjects.update(item.keys())
        for subject in subjects:
            setattr(cls, subject, 0)  # cls 클래스에 인스턴스 변수공간을 추가!!
        print(subjects)
        print(data)
        return [cls(**item) for item in data]


def main():
    students = StudentData.from_json("params.json")
    for student in students:
        print(student)


if __name__ == "__main__":
    main()
