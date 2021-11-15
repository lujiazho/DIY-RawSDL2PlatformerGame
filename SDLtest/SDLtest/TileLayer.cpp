#include "TileLayer.h"
#include "TextureManager.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetsList tilesets): 
	m_TileSize(tilesize), m_RowCount(rowcount), m_ColCount(colcount), m_Tilemap(tilemap), m_Tilesets(tilesets){
	// [tilemap] is the map or the image of one layer; because one layer includes a map and a set of tilesets

	for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
		TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/maps/" + m_Tilesets[i].Source);
	}
}

void TileLayer::Render() {
	for (unsigned int i = 0; i < m_RowCount; i++) {
		for (unsigned int j = 0; j < m_ColCount; j++) {
			int tileID = m_Tilemap[i][j];
			
			if (tileID == 0) { // 0 represents there is no tile
				continue;
			}
			else {
				int index = 0;
				if (m_Tilesets.size() > 1) {
					for (unsigned int k = 1; k < m_Tilesets.size(); k++) {
						if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID) {
							tileID -= m_Tilesets[k].FirstID;
							index = k;
							break;
						}
					}
				}
				Tileset ts = m_Tilesets[index];
				int tileRow = tileID / ts.ColCount;
				int tileCol = tileID - tileRow * ts.ColCount;

				TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSizes, j * ts.TileSizes, i * ts.TileSizes, tileRow, tileCol);
			}
		}
	}
}
void TileLayer::Update() {

}