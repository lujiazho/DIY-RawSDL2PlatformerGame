#include "MapParser.h"

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() {
	return Parse("MAP", "assets/maps/longmap.tmx");
}

bool MapParser::Parse(std::string id, std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement(); // root is <map> label
	int rowcount, colcount, tilesize = 0;
	root->Attribute("width", &colcount);
	root->Attribute("height", &rowcount);
	root->Attribute("tilewidth", &tilesize);

	// Parse tile sets
	TilesetsList tilesets;
	GameMap* gamemap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("tileset")) {
			tilesets.push_back(ParseTileset(e));
		}
		if (e->Value() == std::string("layer")) {
			TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
			gamemap->m_MapLayers.push_back(tilelayer);
		}
	}

	m_MapDict[id] = gamemap;
	return true;
}

// Parse <tileset> label
Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID); // get the first tile's index

	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

	// get columns and rows count and tile size
	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSizes);

	// get image file name
	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;
}

// Parse <layer> label
TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetsList tilesets, int tilesize, int rowcount, int colcount) {
	TiXmlElement* data = nullptr;
	// first child is data in the tmx file
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			data = e; // there maybe other data, we only want the right one
			break;
		}
	}

	// Parse Layer tile map
	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
	for (int row = 0; row < rowcount; row++) {
		for (int col = 0; col < colcount; col++) {
			getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good()) { // check the stringstream is normal ¶ÁÐ´Õý³£
				break;
			}
;		}
	}

	return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}

void MapParser::Clean() {
	std::map<std::string, GameMap*>::iterator it;
	for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
		it->second = nullptr;
	}
	m_MapDict.clear();
}