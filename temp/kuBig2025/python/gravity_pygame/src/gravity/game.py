import pygame

from .ball import Ball
from .ui import UI


class Game:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800, 600))
        self.game_active = True
        self.clock = pygame.time.Clock()
        self.fps = 60
        self.all_sprite = pygame.sprite.Group()
        self.ui = UI(self)

    def update(self):
        self.ui.update()
        if len(self.all_sprite) < 20:
            ball = Ball(self)
            self.all_sprite.add(ball)
        self.all_sprite.update()

    def draw(self):
        self.screen.fill((255, 255, 255))
        self.all_sprite.draw(self.screen)
        self.ui.draw(self.screen)
        pygame.display.flip()

    def run(self):
        while True:
            self.clock.tick(self.fps)
            if self.game_active:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit()
                        exit()
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_q:
                            self.game_active = False
                    if event.type == pygame.MOUSEBUTTONDOWN:
                        print("mouse button down")
                        print(event.dict)
                        print(event.dict["pos"][0], event.dict["pos"][1])
                self.update()  # 게임 로직에 필요한 내부 변수...
                self.draw()  # 화면 출력을 담당.
            else:
                break
