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

ICONPATH = "../resources/solar.png"


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
        s.width, s.height = Vector(0, 0)
        s.x, s.y = Vector(0, 0)

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
        self.surficon = pygame.image.load(ICONPATH).convert_alpha()

    def transform_coordinates(self, p):
        """
        Transform the coordinates of a physical object.

        :p: physical object / point
        :returns: (x, y)
        """
        if type(p) == PhysicalObject:
            return (
                int(p.x / SCALE_FACTOR) - self.x,
                int(p.y / SCALE_FACTOR) - self.y
            )
        elif type(p) == Vector:
            return (
                int(p[0] / SCALE_FACTOR) - self.x,
                int(p[1] / SCALE_FACTOR) - self.y
            )

    def in_display(self, point):
        """
        Determine whether the point can be seen.

        :point: (x, y) coordinates
        :returns: True or False
        """
        x, y = point
        if x < 0 or x > self.width or \
                y < 0 or y > self.height:
            return False
        return True

    def keyboard(self, key):
        """
        Handle keyboard events.

        :key: key pressed
        """
        s = self
        global SCALE_FACTOR, MIN_MASS
        if key == pygame.K_SPACE:
            self.pause = not self.pause
        elif key == pygame.K_UP:
            s.y -= int(s.height / 10)
        elif key == pygame.K_DOWN:
            s.y += int(s.height / 10)
        elif key == pygame.K_LEFT:
            s.x -= int(s.width / 10)
        elif key == pygame.K_RIGHT:
            s.x += int(s.width / 10)
        elif key == pygame.K_EQUALS:
            SCALE_FACTOR /= 1.05
        elif key == pygame.K_MINUS:
            SCALE_FACTOR *= 1.05
        MIN_MASS = SCALE_FACTOR ** 3

    def put_text(self, text, color, x, y):
        """
        Put the text on the screen.

        :text: message to display
        :color: color of the text
        :x: x-position
        :y: y-position
        """
        s = self
        if not s.in_display((x - s.x, y - s.y)):
            return
        font = pygame.font.SysFont("monospace", 18, bold=True)
        label = font.render(text, 1, color)
        self.screen.blit(label, (
            x - s.x,
            y - s.y
        ))

    def show_status(self):
        """Put status text on the screen."""
        s = self
        color = (255, 255, 255)
        self.put_text("scale factor: %.2E" % SCALE_FACTOR,
                      color, s.x, s.y)
        self.put_text("G: %.7E" % G,
                      color, s.x, s.y + 25)
        self.put_text("number of objects: %d" % len(s.phy.phyobjs),
                      color, s.x, s.y + 50)
        self.put_text("x: %d" % s.x,
                      color, s.width + s.x - 100, s.height + s.y - 50)
        self.put_text("y: %d" % s.y,
                      color, s.width + s.x - 100, s.height + s.y - 25)

    def put_vector(self, surface, init, vector, color):
        """
        Put a vector onto the screen.

        :sorface: surface to put the object on
        :init: initial coordinates
        :vector: vector to put
        :color: color of the vector
        TODO: fix
        """
        s = self
        init = s.transform_coordinates(init)
        if not s.in_display(init):
            return
        vector = s.transform_coordinates(vector)
        print(init)
        print(vector)
        pygame.draw.line(
            surface, color, init,
            [init[0] + vector[0] * 10, init[1] + vector[1] * 10],
            4
        )

    def put_object(self, surface, p, color):
        """
        Put an object on the screen.

        :surface: surface to put the object on
        :p: physical object
        :color: color of the object
        """
        s = self
        coords = s.transform_coordinates(p)
        if not s.in_display(coords):
            return
        pygame.draw.circle(surface,
                           color,
                           coords,
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
                int(p.x / SCALE_FACTOR) - len(text) * 5,
                int(p.y / SCALE_FACTOR + int(p.radius) / SCALE_FACTOR * 1.2)
            )
            color = (color + 1) % len(COLORS)
        self.show_status()
        pygame.display.set_icon(self.surficon)
        pygame.display.flip()
        return True

    def stop(self):
        """Terminate graphics."""
        pygame.quit()
