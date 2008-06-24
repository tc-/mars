#ifndef MAP_H
#define MAP_H

#include <vector>

namespace world
{

class MapTile
{
	public:

		MapTile() {}

	protected:

};

class Map
{
	public:
		Map( const unsigned int& width, const unsigned int& height );
		~Map();

		MapTile& get( const unsigned int& x, const unsigned int& y );

	protected:

		void setSize( const unsigned int& width, const unsigned int& height );

		std::vector< std::vector<MapTile*> > m_tiles;

};

}

#endif // MAP_H
