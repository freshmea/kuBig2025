import time

import pygame


class UI(pygame.sprite.Sprite):
    def __init__(self, game):
        super().__init__()
        self.game = game
        self.font = pygame.font.SysFont(None, 50)
        self.image = None
        self.rect = None
        self.start_time = time.time()

    def update(self):
        elapsed_time = time.time() - self.start_time
        ui_text = f"Elapsed Time : {elapsed_time:.2f}, ball Count: {len(self.game.all_sprite)}"
        self.image = self.font.render(ui_text, True, (0, 0, 0))
        self.rect = self.image.get_rect(topleft=(10, 10))

    def draw(self, surface):
        surface.blit(self.image, self.rect)
