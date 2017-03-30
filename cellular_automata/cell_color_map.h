#pragma once

#include <SDL.h>

//Begin Forward Definitions
namespace cellular_automata {
class Cell;
}
//End Forward Definitions

namespace cellular_automata_mvc {

class CellColorMap {
public:
	struct Color {
		Uint8 r, g, b, a;
	};


	Color getColorForCell(const cellular_automata::Cell& cell) const;
	Uint32 getPixelForCell(const cellular_automata::Cell& cell) const;

private:
	static const Uint32 COLOR_WHITE = 0xFFFFFFFF;
	static const Uint32 COLOR_BLACK = 0xFF000000;
	static const Uint32 COLOR_RED = 0xFF0000FF;
	static const Uint32 COLOR_GREEN = 0xFF00FF00;
	static const Uint32 COLOR_BLUE = 0xFFFF0000;
};

}
