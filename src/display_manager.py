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
        s = self
        s.phy = phy
        s.screen = None
        s.pause = 0
        s.width, s.height = 0, 0

    def start(self):
        """Initialize graphics."""
        s = self
        pygame.init()
        pygame.mixer.quit()
        info = pygame.display.Info()
        s.width, s.height = info.current_w, info.current_h - 60
        s.screen = pygame.display.set_mode(
            (s.width, s.height),
            pygame.RESIZABLE
        )

    def keyboard(self, key):
        """
        Handle keyboard events.

        :key: key pressed
        """
        if key == pygame.K_SPACE:
            self.pause = not self.pause

    def put_text(self, text, color, x, y):
        """
        Put the text on the screen.

        :text: message to display
        :color: color of the text
        :x: x-position
        :y: y-position
        """
        font = pygame.font.SysFont("monospace", 18, bold=True)
        label = font.render(text, 1, color)
        self.screen.blit(label, (x, y))

    def put_object(self, surface, p, color):
        """
        Put an object on the screen.

        :surface: surface to put the object on
        :p: physical object
        :color: color of the object
        """
        pygame.draw.circle(surface,
                           color,
                           (int(p.x), int(p.y)),
                           int(p.radius / SCALE_FACTOR))

    def handle_events(self):
        """
        Handle different events.

        :returns: true or false (termination)
        """
        s = self
        for e in pygame.event.get():
            if e.type == pygame.KEYDOWN:
                if e.key == pygame.K_ESCAPE:
                    return False
                s.keyboard(e.key)
        return True

    def tick(self):
        """
        Idle function for displaying the model.

        :returns: boolean (whether continue or not)
        """
        # detect pressed keys
        s = self
        if not s.handle_events():
            return False
        # redraw
        if s.pause == 1:
            return True
        s.phy.tick()
        color = 0
        s.screen.fill((0, 0, 0))
        new_image = pygame.Surface(s.screen.get_size()).convert()
        for p in s.phy.phyobjs:
            s.put_object(new_image, p, COLORS[color])
            color = (color + 1) % len(COLORS)
        s.screen.blit(new_image, (0, 0))
        color = 0
        for p in s.phy.phyobjs:
            text = "%.2E" % (int(p.mass))
            s.put_text(
                text,
                COLORS[color],
                int(p.x) - len(text) * 5,
                int(p.y + int(p.radius) / SCALE_FACTOR * 1.2)
            )
            color = (color + 1) % len(COLORS)
        # pygame.display.set_icon(surface)
        pygame.display.flip()
        return True

    def stop(self):
        """Terminate graphics."""
        pygame.quit()
