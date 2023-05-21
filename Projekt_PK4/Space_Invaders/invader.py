import pygame
from pygame.sprite import Sprite

# A class for showing on the screen a invader
class Invader(Sprite):
    def __init__(self, ai_game):
        super().__init__()
        self.screen = ai_game.screen
        self.settings = ai_game.settings

        self.image = pygame.image.load("Space_Invaders/images/Pixel_invader.png")  # image of the invader
        self.rect = self.image.get_rect()  # setting the image as a rectangle

        self.rect.x = self.rect.width  # space between invaders equal to the width of one invader
        self.rect.y = self.rect.height # space above invaders equal to the height of one invader
        self.x = float(self.rect.x)  # tracking the horizontal position of a invader

    # Information for the program if an invader has touched an edge of the display window
    def check_edges(self):
        screen_rect = self.screen.get_rect()
        if self.rect.right >= screen_rect.right or self.rect.left <= 0:
            return True

    # Deciding which way to move the invader
    def update(self):
        self.x += (self.settings.invader_speed * self.settings.fleet_direction)
        self.rect.x = self.x  # updating its position

