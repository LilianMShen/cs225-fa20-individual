/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    MosaicCanvas* canvas = new MosaicCanvas(rows, columns);

    //map tileAverageColorPoints to their respective tiles
    std::map<Point<3>, int> tileMap;
    vector<Point<3>> tiles(theTiles.size());
    for (int i = 0; i < (int) theTiles.size(); i++) {
        tiles[i] = convertToXYZ(theTiles[i].getAverageColor());
        tileMap[tiles[i]] = i;
        //tileMap.insert(pair<Point<3>, int>(tiles[i], i));
    }
    
    KDTree<3> tileTree(tiles);
    Point<3> regionAverage;
    Point<3> bestTile;
    TileImage* bestTileImage;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            regionAverage = convertToXYZ(theSource.getRegionColor(i, j));

            bestTile = tileTree.findNearestNeighbor(regionAverage);
            bestTileImage = &theTiles[tileMap[bestTile]];
            canvas->setTile(i, j, bestTileImage);
        }
    }

    return canvas;
}

