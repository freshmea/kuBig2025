# uv init
# uv add pygame
# uv run src/main.py

from gravity import Game


def main():
    print("안녕하세요! pygmae main 입니다.")
    game = Game()
    game.run()


if __name__ == "__main__":
    main()
