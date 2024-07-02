//
// Created by Admin on 19/06/2024.
//

#ifndef QUICKTILEMAP_QUICKTILEMAP_H
#define QUICKTILEMAP_QUICKTILEMAP_H


#define  ID_RECTANGLE     0
#define  ID_POINT         1
#define  ID_POLYGON       2
#define  ID_POLYLINE      3
#define  ID_ELLIPSE       4
#define  ID_TEXT          5
#define  ID_GID           6


/**
 * if you set Texture packer, to "Trim Sprite name" to enabled all sprites are "0000", "0001", etc
 * else Uncomment below if you want to use 0000.png or 0000.jpg
 * default is all sprite name's have "No" extension name
 **/
//#define USE_EXTENSION  ".png"
//#define USE_EXTENSION  ".jpg"

//Uncomment to Put Everything in one layer or node using Z Order and No Node's
#define USE_Z_ORDER

#define ID_TILE_MAP_NODE  100000000
#include "SmartNode.h"

using namespace ax;

class QuickTileMap : public Node {

public:
    bool init() override;
    static Node* createNode();
    CREATE_FUNC(QuickTileMap);



    /******* My XML Functions ************/
    std::vector<std::string> StripToVector( std::string dataStream );
    std::vector<std::string> StringToVector( std::string string, char token );
    std::map<std::string,std::string> StripToMap( std::string dataStream );
    std::vector<std::string> ExtractData(const std::string& input , bool includeFirstTag = 0);

    //My XML tools

    std::string GetFirstTag( std::string& stringTag);
    std::string GetFirstTagLeveSpace( std::string& stringTag);
    bool IsStrippable(const std::string& stringTag);
    int  GetXmlIndents(const std::string& str);
    std::string CleanXmlSting(std::string xmlTag);
    std::string TrimXmlSting(const std::string& str, const std::string& whitespace = " \t");
    std::vector<std::string> ConcatenateData(std::vector<std::string>& rawData);
    void DecryptTileData( SmartNode* node);
    float MapTo(float x, float in_min, float in_max, float out_min, float out_max);
    Color4B HTMLtoColour(std::string hexValue);
    unsigned long Hex2Dec(std::string hex);
    Sprite * CreateAnimation( SmartNode*  node  );
    std::vector<SmartNode*> GetPropertiesAsVector( SmartNode * node );
    std::vector<SmartNode*> GetAllPropertiesAsVector( SmartNode * node );


    /******* Tilemap Variables ************/
    std::string mapFileName;
    bool  LoadMap(std::string fileName);

    /******* Tilemap Processing ************/
    SmartNode *root;         // Root of SmartNode
    SmartNode *map;          // Shortcut to map Node
    SmartNode *tileSet;      // Shortcut to Tileset

    void BuildTileMap(void);

    QuickTileMap() {
    }

    ~QuickTileMap() {
        delete root;
    }


    //Helper Functions
    Sprite * GetAnimation( SmartNode*  node );
    Label*   CreateTextLabel( std::string text );
    Label*   CreateTextLabel( std::string text , std::string fontSpriteName , std::string fontFileName );
    Color4B  GetObjectColour( SmartNode* node );
    void     AddExtraDataToNodes( void );


    Size visibleSize;
    Vec2 origin;
    Rect safeArea;
    Vec2 safeOrigin;

};


#endif //QUICKTILEMAP_QUICKTILEMAP_H
