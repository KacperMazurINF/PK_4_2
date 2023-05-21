
import pygame
import sys
from time import sleep

from button import Button
from bullet import Bullet
from game_stats import Game_stats
from scoreboard import Scoreboard
from settings import Settings
from spaceship import Spaceship
from invader import Invader
from username import get_user_name

class Spaceship_shooter:
    def __init__(self):

        # Initializing everything needed
        pygame.init()
        username = get_user_name()
        self.screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN) 
        self.settings = Settings()
        self.stats = Game_stats(self)
        self.spaceship = Spaceship(self)
        self.sb = Scoreboard(self, username)
        self.bullets = pygame.sprite.Group()
        self.invaders = pygame.sprite.Group()
        self._create_invaders()  # creating the fleet of invaders
        self.play_button = Button(self, "PLAY")  # creating a button with a message
        self.invader = Invader(self)
        # pygame.display.set_caption(f"{self.username} is playing Spaceship Shooter!")  # showing the name of the game at the top left corner
        

    # Main loop responsible for running the game
    def run_game(self):
        while True:
            self._check_events()

            # Updating positions
            if self.stats.game_active:
                self.spaceship.update()  
                self._update_bullets()
                self._update_invaders()

            self._update_screen()

    # Responds to keyboard and mouse events
    def _check_events(self):
        for event in pygame.event.get():

            # Exiting the game
            if event.type == pygame.QUIT:
                sys.exit()

            # Pressing the LMB
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                self._check_play_button(mouse_pos)
            
            # Pressing keyboard keys
            elif event.type == pygame.KEYDOWN:
                self._check_keydown_events(event)

            # Releasing keyboard keys
            elif event.type == pygame.KEYUP:
                self._check_keyup_events(event)

    # Checking if the play button is clicked
    def _check_play_button(self, mouse_pos):
        button_clicked = self.play_button.rect.collidepoint(mouse_pos)
        if button_clicked and not self.stats.game_active:
            self.start_game()

    # Setting everything up to start a new game
    def start_game(self):
        self.settings.initialize_dynamic_settings()
        self.stats.reset_stats()
        self.stats.game_active = True
        self.sb.prep_score()
        self.sb.prep_level()
        self.sb.prep_lives()

        self.invaders.empty()  # emptying invaders group
        self.bullets.empty()  # emptying sprites group

        self._create_invaders()
        self.spaceship.center_spaceship()

        pygame.mouse.set_visible(False)

    # Informing the program what to do when a specific key is pressed
    def _check_keydown_events(self, event):
        if event.key == pygame.K_RIGHT:
            self.spaceship.moving_right = True
        elif event.key == pygame.K_LEFT:
            self.spaceship.moving_left = True
        elif event.key == pygame.K_UP:
            self.spaceship.moving_up = True
        elif event.key == pygame.K_DOWN:
            self.spaceship.moving_down = True
        elif event.key == pygame.K_q:
            sys.exit()
        elif event.key == pygame.K_SPACE:
            self._fire_bullet()

    # Informing the program what to do when a specific key is released
    def _check_keyup_events(self, event):
        if event.key == pygame.K_RIGHT:
            self.spaceship.moving_right = False
        elif event.key == pygame.K_LEFT:
            self.spaceship.moving_left = False
        elif event.key == pygame.K_UP:
            self.spaceship.moving_up = False
        elif event.key == pygame.K_DOWN:
            self.spaceship.moving_down = False

    # Bullets and their position
    def _update_bullets(self):

        # Updating the bullets location
        self.bullets.update()

        # Removing bullets that passed through the top of the display window
        for bullet in self.bullets.copy():
            if bullet.rect.bottom <= 0:
                self.bullets.remove(bullet)

        self._check_bullet_invader_collision()

    # Cheking for collision between invaders and bullets
    def _check_bullet_invader_collision(self):
        collision = pygame.sprite.groupcollide(self.bullets, self.invaders, True, True)

        # Adding point to score
        if collision:
            for invaders in collision.values():
                self.stats.score += self.settings.invader_points * len(invaders)
            self.sb.prep_score()  # refreshing the score value
            self.sb.check_high_score()  # checking if the score passed the high score

        # If there is no more invaders proceed to the next level
        if not self.invaders:
            self.start_next_level()

    def start_next_level(self):
        self.bullets.empty()  # emptying bullets group
        self._create_invaders()  # creating a new fleet
        self.settings.increase_speed() # incresing difficulty

        self.stats.level += 1
        self.sb.prep_level() # showing new level

    def _fire_bullet(self):

        # If there are less bullets on the screen than the allowed max, we can shoot the next bullet
        if len(self.bullets) < self.settings.bullets_allowed:
            new_bullet = Bullet(self)
            self.bullets.add(new_bullet)

    # invaders and their position
    def _update_invaders(self):
        self._check_fleet_edges()  # Deciding which way to move the fleet 
        self.invaders.update()  # Updating location

        # If the spaceship collides with a invader, lose a life
        if pygame.sprite.spritecollideany(self.spaceship, self.invaders):
            self._spaceship_hit()

        self._check_invader_bottom()

    # Math behind creating a fleet
    def _create_invaders(self):
        invader = Invader(self)
        invader_width, invader_height = invader.rect.size
        available_space_x = self.settings.screen_width - (2 * invader_width)  # space between each invader
        number_invaders_x = available_space_x // (2 * invader_width)  # how many invader can fit next to each other

        spaceship_height = self.spaceship.rect.height
        available_space_y = (self.settings.screen_height - (3 * invader_height) - spaceship_height)  # available vertical space
        number_rows = available_space_y // (2 * invader_height)  #  available number of rows

        # Creating a fleet
        for row_number in range (number_rows):
            for invader_number in range(number_invaders_x):
                self._create_invader(invader_number, row_number)

    # Creating a single invader and placing it in the row
    def _create_invader(self, invader_number, row_number):
        invader = Invader(self)
        invader_width, invader_heigh = invader.rect.size
        invader.x = invader_width + 2 * invader_width * invader_number
        invader.rect.x = invader.x
        invader.rect.y = invader.rect.height + 2 * invader.rect.height * row_number
        self.invaders.add(invader)
 
    # Changing the fleets movement direction if it touched the edge of the screen
    def _check_fleet_edges(self):
        for invader in self.invaders.sprites():
            if invader.check_edges():
                self._change_fleet_direction()
                break

    def _change_fleet_direction(self):
        for invader in self.invaders.sprites():   
            invader.rect.y += self.settings.fleet_drop_speed
        self.settings.fleet_direction *= -1  # changing between 1 and -1

    # Telling the program what to do if the spaceship collided with a invader
    def _spaceship_hit(self):
        # If there are still lives:
        if self.stats.spaceship_left > 0:
                self.stats.spaceship_left -= 1
                self.sb.prep_lives()  # refresh how many lives are left

                self.invaders.empty()  # emptying invaders group
                self.bullets.empty()  # emptying bullets group

                self._create_invaders()  # creasting a new fleet

                self.spaceship.center_spaceship()  # reseting ships position

                sleep(0.5)  # a brief pause

        #If no lives left:
        else:
            self.stats.game_active = False  # stop game
            pygame.mouse.set_visible(True)

    # Checking if a invader passed the bottom of the screen
    def _check_invader_bottom(self):
        screen_rect = self.screen.get_rect()  # setting the screen as a rectangle
        for invader in self.invaders.sprites():
            if invader.rect.bottom >= screen_rect.bottom:  # passing the bottoom
                self._spaceship_hit() 
                break

    # Updating what is shown on the display screen
    def _update_screen(self):
        self.screen.fill(self.settings.bg_color)  # background
        self.spaceship.blitme()  # drawing the spaceship

        # Drawing bullets
        for bullet in self.bullets.sprites():
            bullet.draw_bullet()
        self.invaders.draw(self.screen)  # drawing invaders
        self.sb.show_score()  # showing the score, high score, lives and level

        # Drawing the button at the start of the game
        if not self.stats.game_active:
            self.play_button.draw_button()

        pygame.display.flip()  # refreshing the screen


if __name__ == '__main__':
    ai = Spaceship_shooter()
    ai.run_game()