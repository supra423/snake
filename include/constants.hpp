#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <raymath.h>
#define DEFAULT_WINDOW_WIDTH 1200
#define DEFAULT_WINDOW_HEIGHT 900
#define WINDOW_TITLE "supra's snake game"
#define FPS 60

#define BORDER_THICKNESS 1
#define BORDER_WIDTH 800
#define BORDER_HEIGHT 800
constexpr Vector2 BORDER_POS = (Vector2){(DEFAULT_WINDOW_WIDTH - BORDER_WIDTH) / 2.0f, (DEFAULT_WINDOW_HEIGHT - BORDER_HEIGHT) / 2.0f};

#define ROWS 20
#define COLS 20

constexpr int MAP_CELL_SIZE = ((BORDER_WIDTH / ROWS) + (BORDER_HEIGHT / COLS)) / 2;
#define INNER_CELL_SIZE 32.0f

#define BORDER_OFFSET 10.0f

#define CELL_CORNER_LINE_LENGTH 6.0f

constexpr Vector2 DYNAMIC_OFFSET(Vector2 center) {
	return (Vector2){center.x - DEFAULT_WINDOW_WIDTH / 2.0f, center.y - DEFAULT_WINDOW_HEIGHT / 2.0f};
}

#define SNAKE_SEGMENT_SIZE 20.0f

constexpr Vector2 SNAKE_STARTING_POSITION = (Vector2){BORDER_POS.x + 360, BORDER_POS.y + 360};

#define MOVE_INTERNAL 0.15f

#define SCORE_FONT_SIZE 50.0f
#endif
