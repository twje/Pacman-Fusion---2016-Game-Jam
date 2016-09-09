/*
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include "Utilities.h"
#include "SharedContext.h"
#include <SFML/Window.hpp>

enum Sheet{ Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256, Num_Layers = 4 };
using TileID = unsigned int;

// Forward declaration
namespace Tmx
{
    class Map;
}

struct TileInfo{
    TileInfo():
    m_id(-1),
	m_name(""),
	m_friction(0, 0),
	m_deadly(false),
	m_texture(""),
	m_sprite(nullptr)
	{}

	sf::Sprite* m_sprite;
	TileID m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;
	std::string m_texture;
};

struct Tile{
    Tile():
    m_warp(false),
    m_solid(false),
    m_properties(new TileInfo)
    {}

	TileInfo* m_properties;
	bool m_warp;
	bool m_solid;
    sf::VertexArray* m_verts;
    sf::Texture* m_texture;
};

using TileMap = std::unordered_map<TileID, Tile*>;
using TileSet = std::unordered_map<TileID, TileInfo*>;

class Map{
public:
	Map(SharedContext* l_context);
	~Map();

	Tile* GetTile(unsigned int l_x, unsigned int l_y, unsigned int l_layer);
	TileInfo* GetDefaultTile();

	unsigned int GetTileSize()const;
	const sf::Vector2u& GetMapSize()const;
	const sf::Vector2f& GetPlayerStart()const;
	int GetPlayerId()const;

	void LoadMap(const std::string& l_path);
	int getLayerCount();

	void Update(float l_dT);
	void Draw(unsigned int l_layer);

private:
	void PurgeMap();
	void PurgeTileSet();

	TileSet m_tileSet;
	TileMap m_tileMap;

	TileInfo m_defaultTile;

	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	SharedContext* m_context;
    int m_playerId;

	Tmx::Map* m_map;
	Tile m_temp;
};
*/
