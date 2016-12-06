import pygame

from constants import *
from physics_manager import *


"""
This module is responsible for displaying physical objects in the model.
"""

COLORS = [
    (255, 0, 0),
    (0, 255, 0),
    (0, 0, 255),
    (255, 255, 0),
    (0, 255, 255),
    (255, 0, 255),
    (255, 125, 0),
    (255, 0, 125),
    (125, 255, 0),
    (0, 255, 125),
    (125, 0, 255),
    (0, 125, 255),
    (255, 125, 125),
    (125, 255, 125),
    (125, 125, 255),
]


class DisplayManager:
    def __init__(self, phy):
        """
        Initialize display manager.

        :phy: physics manager
        """
        self.phy = phy
        self.screen = None
        self.pause = 0

    def start(self, w, h):
        """
        Initialize graphics.

        :w: width
        :h: height
        """
        s = self
        pygame.init()
        pygame.mixer.quit()
        s.screen = pygame.display.set_mode((w, h), pygame.RESIZABLE)

    def keyboard(self, key):
        if key == pygame.K_SPACE:
            self.pause = not self.pause

    def tick(self):
        """
        Idle function for displaying the model.

        :returns: boolean (whether continue or not)
        """
        # detect pressed keys
        for e in pygame.event.get():
            if e.type == pygame.KEYDOWN:
                if e.key == pygame.K_ESCAPE:
                    return False
                self.keyboard(e.key)
        # redraw
        if self.pause == 1:
            return True
        self.phy.tick()
        color = 0
        self.screen.fill((0, 0, 0))
        new_image = pygame.Surface(self.screen.get_size()).convert()
        for p in self.phy.phyobjs:
            pygame.draw.circle(new_image,
                               COLORS[color],
                               (int(p.x), int(p.y)),
                               int(p.radius / SCALE_FACTOR))
            color = (color + 1) % len(COLORS)
        self.screen.blit(new_image, (0, 0))
        # pygame.display.set_icon(surface)
        pygame.display.flip()
        return True

    def stop(self):
        """Terminate graphics."""
        pygame.quit()
