
#include <stdint.h>

static const uint16_t COLS = 80, ROWS = 25;
uint16_t* video_memory_buffer;

enum vga_colors {
	BLACK 		= 0x0000,
	BLUE 		= 0x1 << 8,
	GREEN 		= 0x2 << 8,
	CYAN 		= 0x3 << 8,
	RED 		= 0x4 << 8,
	MAGENTA 	= 0x5 << 8,
	BROWN 		= 0x6 << 8,
	GRAY 		= 0x7 << 8,
	DARK_GRAY  	= 0x8 << 8,
	BRIGTH_BLUE  	= 0x9 << 8,
	BRIGTH_GREEN  	= 0xA << 8,
	BRIGTH_CYAN  	= 0xB << 8,
	BRIGTH_RED 	= 0xC << 8,
	BRIGTH_MAGENTA 	= 0xD << 8,
	BRIGTH_YELLOW	= 0xE << 8,
	WHITE 		= 0xF << 8
};

struct cursor_location {
	uint16_t x;
	uint16_t y;
};

struct console_settings {
	uint16_t colors;
	struct cursor_location cursor_location;
} console_settings;

void setCursorLocation (struct cursor_location cursor_location) {
	console_settings.cursor_location = cursor_location;
}

void setConsoleColors (vga_colors foreground_color, vga_colors background_color) {
	console_settings.colors = foreground_color | (background_color << 4);
}
void initConsole (vga_colors foreground_color, vga_colors background_color,
		    uint16_t cursor_x, uint16_t cursor_y) {
	video_memory_buffer = (uint16_t *) 0xB8000;
	setConsoleColors(foreground_color, background_color);
	setCursorLocation({cursor_x, cursor_y});
}

uint16_t strlen (const char *str) {
	int len = 0;
	while (str[len] != 0) {
		len++;
	}
	return len;
}

void print (const char* str) {
	for (int i=0; str[i] != 0; i++) {
		if (str[i] == '\n') {
			console_settings.cursor_location.y += 1;
			console_settings.cursor_location.x = 0;
			continue;
		}
		if (console_settings.cursor_location.y >= ROWS) {
			for (uint16_t x=0; x<COLS; x++) {
				for (uint16_t y=0; y<ROWS; y++) {
					video_memory_buffer[(COLS*y)+x] = console_settings.colors | ' ';
				}
			}
			setCursorLocation({0, 0});
		}
		video_memory_buffer[(COLS*console_settings.cursor_location.y)+console_settings.cursor_location.x] = console_settings.colors | str[i];
		console_settings.cursor_location.x++;
	}
}

void printLine (const char* str) {
	print(str);
	console_settings.cursor_location.y += 1;
	console_settings.cursor_location.x = 0;
}

void printWelcomeScreen () {
	initConsole(vga_colors::BRIGTH_CYAN, vga_colors::MAGENTA, 0, 0);

	const char *str = "MISO";
	uint16_t x = COLS/2-strlen(str)/2, y = ROWS/2-6; setCursorLocation({x, y});
	print(str);

	str = "Simple kernel";
	x = COLS/2-strlen(str)/2, y = ROWS/2-4; setCursorLocation({x, y}); setCursorLocation({x, y});
	print(str);

}

extern "C" void kernel_main() {
	printWelcomeScreen();
	
	while (1);
}

