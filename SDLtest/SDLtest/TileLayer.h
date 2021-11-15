#ifndef TILELAYER_H
#define TILELAYER_H

#include "Layer.h"
#include <string>
#include <vector>

struct Tileset {
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSizes;
	std::string Name, Source; // tile name, file name
};

using TilesetsList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer: public Layer {
public:
	TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetsList tilesets);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTilemap() { return m_Tilemap; }

	int GetRowCount() { return m_RowCount; }
	int GetColCount() { return m_ColCount; }

private:
	int m_TileSize;
	int m_RowCount, m_ColCount;

	TileMap m_Tilemap;
	TilesetsList m_Tilesets;
};

#endif // TILELAYER_H