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

	//Blue Palet
	/*static const Uint32 COLOR_WHITE = 0xFF8F8284;
	static const Uint32 COLOR_BLACK = 0xFFA88B04;
	static const Uint32 COLOR_RED = 0xFF3D2913;
	static const Uint32 COLOR_GREEN = 0xFF7AFFCB;
	static const Uint32 COLOR_BLUE = 0xFFFF0000;*/

	//Grey Palet
	/*static const Uint32 COLOR_WHITE = 0xFFFFFFFF;
	static const Uint32 COLOR_BLACK = 0xFF000000;
	static const Uint32 COLOR_RED = 0xFF7F7F7F;
	static const Uint32 COLOR_GREEN = 0xFF7AFFCB;
	static const Uint32 COLOR_BLUE = 0xFFFF0000;*/

	//Brownish Palet
	/*static const Uint32 COLOR_WHITE = 0xFF170505;
	static const Uint32 COLOR_BLACK = 0xFF365CCF;
	static const Uint32 COLOR_RED = 0xFF8BC8EF;
	static const Uint32 COLOR_GREEN = 0xFF7AFFCB;
	static const Uint32 COLOR_BLUE = 0xFFFF0000;*/

	////Schlangentraeger I
	//static const Uint32 COLOR_WHITE = 0xFF173EA6;
	//static const Uint32 COLOR_BLACK = 0xFF71A7E3;
	//static const Uint32 COLOR_RED = 0xFF080B1C;
	//static const Uint32 COLOR_GREEN = 0xFFFDF9F4;
	//static const Uint32 COLOR_BLUE = 0xFFFF0000;
};

}
