//
//  PortMap.h
//  coastline
//
//  Created by 荣徽 贺 on 14-7-5.
//
//
#ifndef coastline_PortMap_h
#define coastline_PortMap_h

#define MAX_MAP_HEIGHT_TILES 100
#define MAX_MAP_WIDTH_TILES  100

char* g_PortCoordArray[MAX_MAP_WIDTH_TILES][MAX_MAP_HEIGHT_TILES] = {};

//Add the port image file here
void InitPortCoordArray()
{
    g_PortCoordArray[6][9] = "Lisbon.png";
}

#endif
