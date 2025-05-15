import random

import pygame


class Ball:
    def __init__(self):
        self.x = random.randint(0, 800)
        self.y = random.randint(0, 600)
        self.radius = random.uniform(50, 100)
        self.color = (
            random.randint(0, 255),
            random.randint(0, 255),
            random.randint(0, 255),
        )
        self.vel = (random.randint(-10, 10), random.randint(-10, 10))

    def update(self):
        self.x += self.vel[0]
        self.y += self.vel[1]
        if self.x < 0:
            self.x = 800
        if self.x > 800:
            self.x = 0
        if self.y < 0:
            self.y = 600
        if self.y > 600:
            self.y = 0


class Game:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((800, 600))
        self.game_active = True
        self.clock = pygame.time.Clock()
        self.fps = 60
        self.balls = [Ball() for _ in range(5)]

    def update(self):
        for ball in self.balls:
            ball.update()

    def update_screen(self):
        self.screen.fill((255, 255, 255))
        for ball in self.balls:
            pygame.draw.circle(self.screen, ball.color, (ball.x, ball.y), ball.radius)
        pygame.display.flip()

    def run(self):
        while True:
            self.clock.tick(self.fps)
            if self.game_active:
                for event in pygame.event.get():
                    if event.type == pygame.QUIT:
                        pygame.quit()
                        exit()
                self.update()  # 게임 로직에 필요한 내부 변수...
                self.update_screen()  # 화면 출력을 담당.
            else:
                break
