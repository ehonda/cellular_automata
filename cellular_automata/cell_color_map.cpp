#include "cell_color_map.h"

#include "cell.h"

namespace cellular_automata_mvc {

CellColorMap::Color CellColorMap::getColorForCell(
	const cellular_automata::Cell& cell) const
{
	if (cell.getState() == 0)
		return{ 0xFF, 0xFF, 0xFF, 0xFF };
	else
		return{ 0x00, 0x00, 0x00, 0xFF };
}

Uint32 CellColorMap::getPixelForCell(const cellular_automata::Cell & cell) const
{
	switch (cell.getState())
	{
	case 0:
		return COLOR_WHITE;
	case 1:
		return COLOR_BLACK;
	case 2:
		return COLOR_RED;
	case 3:
		return COLOR_GREEN;
	case 4:
		return COLOR_BLUE;
	default:
		return COLOR_WHITE;
	}
}

}
