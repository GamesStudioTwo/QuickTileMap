//
// Created by Admin on 19/06/2024.
//


#include "QuickTileMap.h"


/**************************************************************************************************
 * createNode                                                                                     *
 **************************************************************************************************
 * Axmol create() function                                                                        *
  **************************************************************************************************/
Node* QuickTileMap::createNode() {
    return QuickTileMap::create();
}

/**************************************************************************************************
 * init                                                                                           *
 **************************************************************************************************
 * Axmol init function call                                                                       *
 **************************************************************************************************/
bool QuickTileMap::init()  {
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() ) {
        return false;
    }

    setTag(ID_TILE_MAP_NODE);
    setName("ID_TILE_MAP_NODE");


    visibleSize = _director->getVisibleSize();
    origin = _director->getVisibleOrigin();
    safeArea = _director->getSafeAreaRect();
    safeOrigin = safeArea.origin;

    return true;
}


/**************************************************************************************************
 * MapTo                                                                                          *
 **************************************************************************************************
 * Remaps coordinates to another coordinate system                                                *
 * so we can map from 0.0 to 1.0 -> 0 to 255 or 0.0 to 1.0 -> 0.0 to -255 to reverse coordinates  *
 * used in things like setting setOpacity 0 to 255, sprite->setAnchorPoint that use 0 to 1        *
 **************************************************************************************************/
float QuickTileMap::MapTo(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



/**************************************************************************************************
* Hex2Dec                                                                                         *
***************************************************************************************************
* Hex2Dec Converter                                                                               *
* returns a Color3B                                                                               *
**************************************************************************************************/
unsigned long QuickTileMap::Hex2Dec(std::string hex)
{
    unsigned long result = 0;
    for (int i=0; i < hex . length ( ); i++ ) {
        if ( hex [ i ] >= 48 && hex [ i ] <= 57 ) {
            result += ( hex [ i ] -48 ) *pow (16,hex . length ( ) -i -1 );
        } else if ( hex [ i ] >= 65 && hex [ i ] <= 70 ) {
            result += ( hex [ i ] -55 ) *pow (16,hex . length ( ) -i -1);
        } else if ( hex [ i ] >= 97 && hex [ i ] <= 102 ) {
            result += ( hex [ i ] -87 ) *pow (16,hex . length ( ) -i -1);
        }
    }
    return result;
}

/*************************************************************************************************
** HTML to Colour Convert                                                                       **
**************************************************************************************************
** @param  HTMLtoColour("#000000");           // Black                                          **
** @return Color3B from a HEX or Html  format                                                   **
**************************************************************************************************
** Takes your Hex number and turns it into that colour                                          **
*************************************************************************************************/
Color4B QuickTileMap::HTMLtoColour(std::string hexValue) {
    if( hexValue.size() == 7 ) {
        float red = Hex2Dec(hexValue.substr(1, 2));
        float green = Hex2Dec(hexValue.substr(3, 2));
        float blue = Hex2Dec(hexValue.substr(5, 2));
        return Color4B(red, green, blue,1);
    } else {
            float alpher = Hex2Dec(hexValue.substr(1, 2));
            float red = Hex2Dec(hexValue.substr(3, 2));
            float green = Hex2Dec(hexValue.substr(5, 2));
            float blue = Hex2Dec(hexValue.substr(7, 2));
            return Color4B(red, green, blue , alpher);
    }
}


/**************************************************************************************************
 * TrimXmlSting                                                                                   *
 **************************************************************************************************
 * trims spaces from left side of a string                                                        *
 **************************************************************************************************/
std::string QuickTileMap::TrimXmlSting(const std::string& str, const std::string& whitespace) {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) return ""; // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}


/**************************************************************************************************
 * CleanUP                                                                                        *
 **************************************************************************************************
 * Cleans up an XML string for reading                                                            *
 **************************************************************************************************/
std::string QuickTileMap::CleanXmlSting(std::string xmlTag) {
    std::string result = xmlTag;
    // Remove characters <?\r\n> from the beginning and end
    const char charsToRemove[] = "<\r\n>?"; // Include the question mark
    for (char c : charsToRemove) {
        result.erase(std::remove(result.begin(), result.end(), c), result.end());
    }
    while (!result.empty() && std::isspace(result.back())) {
        result.pop_back();
    }
    return result;
}



/**************************************************************************************************
 * StringToVector                                                                                 *
 **************************************************************************************************
 * Split a string and returns a vector of strings separated by a token                            *
 * @param string, token                                                                           *
 * @return std::vector<String>                                                                    *
 * usage auto myVector = StringToVector(textString,',');                                          *
 * you will use it when it come's to getting polygon or ployline's , etc for physics & stuff      *
 **************************************************************************************************/
std::vector<std::string> QuickTileMap::StringToVector( std::string string, char token )
{
    std::vector<std::string> vectorStruct;
    std::stringstream input(string);
    std::string intermediate;
    while ( getline(input, intermediate, token) ) {
        vectorStruct.push_back(intermediate);
    }
    return vectorStruct;
}


/**************************************************************************************************
 * StripToVector                                                                                  *
 **************************************************************************************************
 * Strips a string to std::vector<std::string>data in the format                                  *
 * TAG                                                                                            *
 * DATA                                                                                           *
 * so you can compare the tag in a loop                                                           *
 * for(int i =0; i < data.size(); i+=2 ) {                                                        *
 * TAG[i] = "THE TAG";                                                                            *
 * TAG[i+1] = "YOUR DATA";                                                                       *
 * }                                                                                              *
 *************************************************************************************************/
std::vector<std::string> QuickTileMap::StripToVector( std::string dataStream )
{
    std::vector<std::string> tileSetTags = StringToVector(dataStream , '=');
    std::string tmp;
    for ( auto &obj : tileSetTags ) {
        tmp += obj.c_str();
    }
    tileSetTags.clear();
    tileSetTags = StringToVector(tmp , '"');
    tileSetTags[0] = tileSetTags[0].substr(tileSetTags[0].find_first_of(' '),tileSetTags[0].size());
    tileSetTags.pop_back();
    for ( auto &obj : tileSetTags ) {
        obj.erase(obj.begin(), std::find_if(obj.begin(), obj.end(), [](int ch) {  return !std::isspace(ch); }));
    }
    return tileSetTags;
}


/**************************************************************************************************
 * ExtractData                                                                                    *
 **************************************************************************************************
 * Extracts data and puts it in to the storage, in node                                           *
 *  XML example, <objectgroup id="5" name="Object Layer 2"/>                                      *
 *  storage["id"] = "5"                                                                           *
 *  storage["name"] = "Object Layer 2"                                                            *
 *  to get data from storage * yourNode->getKeyAsInt("id");                                       *
 *                             yourNode->getKeyAsSting("name");                                   *
 **************************************************************************************************/
std::vector<std::string> QuickTileMap::ExtractData(const std::string& input , bool includeFirstTag)
{
    std::vector<std::string>result;
    std::vector<std::string>finalResult;
    std::string buffer;
    size_t startPos =  input.find_first_of( ' ' );

    if( includeFirstTag ) {
        result.push_back(buffer);
    }

    size_t nextPos2;
    size_t nextPos3;
    for( ;; ) {
        startPos = input.find_first_of(' ', startPos);
        if( startPos == -1 ) {
            break;
        }

        nextPos2 = input.find_first_of('"', startPos);
        if( nextPos2 == -1 ) {
            break;
        } else {
            buffer = input.substr(startPos + 1, nextPos2 - 2 - startPos);
            result.push_back(buffer);
        }

        nextPos3 = input.find_first_of('"', nextPos2 + 1);
        if( input[ nextPos3 +1] != ' ') {
            size_t temp = nextPos3;
            nextPos3 = input.find_first_of('"', nextPos3 + 1);
            if( nextPos3 == -1 ) {
                nextPos3 = temp;
                buffer = input.substr(nextPos2+1, nextPos3-1 - nextPos2);
                result.push_back(buffer);
            }
        } else {
            buffer = input.substr(nextPos2+1, nextPos3-1 - nextPos2);
            result.push_back(buffer);
        }
        startPos = nextPos3;
    }
    return result;
}


/**************************************************************************************************
 * StripToMap                                                                                     *
 **************************************************************************************************
 * this function rips data in to storage on SmartNode                                             *
 * height, width , image, tile, etc                                                               *
 * float myFloat node->getKeyAsFloat( "width" );                                                  *
 *************************************************************************************************/
std::map<std::string,std::string> QuickTileMap::StripToMap( std::string dataStream )
{
    dataStream = TrimXmlSting(dataStream);
    std::vector<std::string> tileSetTags = ExtractData( dataStream );
    std::map<std::string,std::string>returnMap;
    for ( int i=0; i <tileSetTags.size(); i+=2 ) {
        returnMap[tileSetTags[i]] = tileSetTags[i + 1];
    }
    return returnMap;
}


/**************************************************************************************************
 * GetFirstTag                                                                                    *
 **************************************************************************************************
 * Gets first tag at the begin of xml, map, tileset, properties, animation, objectgroup, layer,etc*
 **************************************************************************************************/
std::string QuickTileMap::GetFirstTag( std::string& stringTag) {
    size_t firstNonSpace = stringTag.find_first_not_of(' ');
    if (firstNonSpace == std::string::npos) {
        return ""; // Return an empty string if there are only spaces
    }
    size_t end = stringTag.find(' ', firstNonSpace);
    return stringTag.substr(firstNonSpace, end - firstNonSpace);
}


/**************************************************************************************************
 * IsStrippable                                                                                   *
 **************************************************************************************************
 * checks to see if xml is a strippable line used for storage map                                 *
 **************************************************************************************************/
bool QuickTileMap::IsStrippable(const std::string& stringTag) {
    return stringTag.find('"') != std::string::npos;
}

/**************************************************************************************************
 * GetXmlIndents                                                                                  *
 **************************************************************************************************
 * returns the indent spaces the in xml                                                           *
 **************************************************************************************************/
int QuickTileMap::GetXmlIndents(const std::string& str) {
    size_t pos = str.find_first_not_of(' ');
    return (pos == std::string::npos) ? str.length() : static_cast<int>(pos);
}


/**************************************************************************************************
 * GetFirstTagLeveSpace                                                                           *
 **************************************************************************************************
 * gets first tag at leaves the indent of xml                                                     *
 **************************************************************************************************/
std::string QuickTileMap::GetFirstTagLeveSpace( std::string& stringTag) {
    size_t firstNonSpace = stringTag.find_first_not_of(' ');
    if (firstNonSpace == std::string::npos) {
        return stringTag; // Return the original string if there are only spaces
    }

    size_t end = stringTag.find(' ', firstNonSpace);
    if (end == std::string::npos) {
        return stringTag; // Return the original string if there's no space after the first word
    }
    return stringTag.substr(0, end);
}



/**************************************************************************************************
 * ConcatenateData                                                                                *
 **************************************************************************************************
 * converts a  string, text or layer data from         <text> aaaaaaaa   aaaa\r\n                 *
 *                                                            bb     cc\r\n                       *
 *                                                     </text>                                    *
 *                                                                                                *
 * formatted to property name="tag" value=" aaaaaaaa   aaaa\r\nbb     cc\r\n   cc\r\n"/           *
 * compiles to one string then reinserted back into the rawData stream before building SmartNode  *
 * getChiledByName("property")->getChiledByName("value");                                         *
 **************************************************************************************************/
std::vector<std::string> QuickTileMap::ConcatenateData(std::vector<std::string>& rawData) {
    std::string currentData; // Declare outside the loop
    size_t i = 0;
    std::vector<std::string> buffer;
    std::string dataString;
    std::string encodingType;
    bool  NoClean = true;

    for (; i < rawData.size(); ++i) {
        currentData = rawData[i]; // Modify within the loop
        std::string clean = CleanXmlSting(currentData);
        std::string firstTag = GetFirstTag(clean);
        std::string encodingType;

        /******************************
         * Start Text conversion      *
         ******************************/
        if ( firstTag == "text" ) {
            std::string tmp;
            for (; i < rawData.size(); ++i) {
                tmp+=rawData[i];
                size_t find = tmp.find_last_of('<');
                if( find > 0  && tmp[find+1] == '/' && tmp[find+2] == 't' ) {
                    break;
                }
            }   // We go all the data/

            size_t find1 = tmp.find_first_of('>');
            size_t find2 = tmp.find_last_of('<');

            currentData = tmp.substr(0, find1) + " value=\"" + tmp.substr(find1 + 1, find2 - 1 - find1) + "\"" + "/";
            tmp="";
           for( int i = 0; i < currentData.size()-1; i++) {
               tmp+=currentData[i];
                if(currentData[i] == '\r') {
                    tmp+='\n';
                }
            }

            int found = tmp.find_first_of('<');
            if( found > 0 ) {
                tmp.erase(found,1);
            }

            if( tmp.back() == '>') {
                tmp.pop_back();
            }

            if( tmp.back() != '/' ) {
                tmp+= '/';
            }

            buffer.push_back( tmp );
            NoClean = false;

            dataString.clear();
            firstTag.clear();
        } /****** End Text conversion ******/


        /******************************
        * Start Layer data conversion *
        *******************************/
        if ( firstTag == "data"  ) {
            auto dataEncoding  = StripToVector(rawData[ i ] );
            std::string encoding = "xml";
            std::string compression= "none";

            if ( dataEncoding[1] == "csv" ) {
                encoding = dataEncoding[1];
                compression = "none";
            }

            if( dataEncoding[1] == "base64" ) {
                encoding = "base64";
                compression = "none";
                if(dataEncoding[3] == "gzip" || dataEncoding[3] == "zlib" || dataEncoding[3] == "zstd") {
                    compression = dataEncoding[3];
                }
            }
            i++;
            for (; i < rawData.size(); ++i) {

                clean = CleanXmlSting(rawData[i]);
                firstTag = GetFirstTag(clean);

                if( firstTag == "/data" ) {
                    if( encoding == "xml" || dataString.back() == ',' ) {
                        dataString.pop_back();
                    }
                    break;
                }

                if( encoding == "xml" ) {
                    auto tmp = StripToVector(rawData[ i ] );
                    if( tmp.size() > 0 ) { dataString += tmp[1] + ","; } else { dataString +=  "0,"; }
                } else {
                    dataString += rawData[i];
                }
            }

            if( dataEncoding[1] == "csv"  ) {
                dataString.erase(std::remove(dataString.begin(), dataString.end(), '\r'), dataString.end());
                dataString.erase(std::remove(dataString.begin(), dataString.end(), '\n'), dataString.end());
            }

            if(  dataString.back() == '\r'  ) { dataString.pop_back(); }
            if(  dataString.back() == '\n'  ) { dataString.pop_back(); }

            dataString = TrimXmlSting(dataString);
            dataString = "data encoding=\""+encoding+"\" compression=\""+compression+"\" value=\"" + dataString  + "\"/";
            dataString = CleanXmlSting( dataString );

            buffer.push_back( dataString );
            dataString.clear();
            firstTag.clear();
            NoClean = false;
        } /****** End Layer conversion *****/


        /******************************
        * Start Sting data conversion *
        *******************************/
        if ( firstTag == "property" && clean.back() != '/' ) {
            auto v = StripToMap(clean);
            if ( v.count("type" ) == 0 ) {
                size_t find = currentData.find_last_of('>');
                if ( find != std::string::npos ) {
                    currentData.replace(find, 1, " value=\"" );
                }
                i++;
                for (; i < rawData.size(); ++i ) {
                    currentData += rawData[ i ]; // Modify within the loop
                    std::string clean = CleanXmlSting(currentData);
                    if( clean.back() == 'y' ) {
                        size_t find = currentData.find_last_of('<' );

                        if ( find != std::string::npos ) {
                            currentData.replace(find, currentData.size(), "\"/>" );
                        }
                        break;
                    }
                }
            }

           std::string tmp;
           for( int i = 0; i < currentData.size()-1; i++ ) {
               tmp+=currentData[i];
               if( currentData[i] == '\r' ) {
                   tmp+='\n';
               }
           }

            int found = tmp.find_first_of('<' );
            if( found > 0 ) {
                tmp.erase(found,1 );
            }

            if( tmp.back() == '>' ) {
                tmp.pop_back();
            }

            buffer.push_back( tmp );
            NoClean = false;
            dataString.clear();
            firstTag.clear();
        } /****** End String conversion ******/

        //Tag has No conversion feed it back
        if( NoClean == true ) {
            buffer.push_back(  clean );
        }
            NoClean = true;
    }
    rawData.clear(); // This clears the std::vector<std::string>& rawData input
                     // so we can do rawData = ConcatenateData(rawData); when called from function.
    return buffer;
}


/**************************************************************************************************
 * DecryptTileData                                                                                *
 **************************************************************************************************
 * Decompression routine for tile's. stored back into node in a std::vector<unsigned int> data;   *
 * as are node storage is stings only, supports xml, csv, zlib, gzip, base64 uncompressed         *
 * if the data is > 0 we don't we don't decrypt again unless you reload A map  to save time       *
 * if you just want to reset a map.                                                               *
 **************************************************************************************************/
void QuickTileMap::DecryptTileData( SmartNode* node )  {

    //If already decrypted don't do it again
    // as storage["value"] = "" from first decrypt &
    // already stored back in node->data;
    if( node->data.size() > 0 ) {
       // AXLOG("Noting to do allredy decrypted.!");
        return;
    }

    if ( !node ) {  return;  } // Quick ptr check
    auto data = node->getChildByName("data");

    if ( !data ) {
        AXLOG("Error Can't find any data on Name:%s ", node->getName().c_str() );
        return;
    }

    auto   encoding     =  data->getKeyAsString("encoding");
    auto   compression  =  data->getKeyAsString("compression");

    if( compression == "zstd" ) {
        AXLOG("ERROR Compression not supported, use zlib or gzip compression..!");
        return;
    }

    // XML and CSV convert Text to unsigned int
    if ( encoding == "xml" || encoding == "csv" ) {
        auto dataVector = StringToVector(data->getKeyAsString("value"),',');

        if (!dataVector.empty() && dataVector.back() == ",") {
            dataVector.pop_back();
        }

        data->deleteKeyFromStorage("value"); //free map["value"] data

        for ( int i = 0; i < dataVector.size(); i++ ) {
            node->data.push_back(std::atoll(dataVector[i].c_str() ) );
        }
        return;
    }

    // Base64 No compression
    if ( encoding == "base64" && compression == "none" ) {
        unsigned char* buffer;
        ax::utils::base64Decode( (unsigned char *) data->getKeyAsString("value").c_str(), (unsigned int) data->getKeyAsString("value").length(), &buffer );
        if ( !buffer ) {
            AXLOG("Error Decrypting Base64 No Compression..!");
            return;
        }
        auto out = reinterpret_cast<uint32_t *>( buffer );
        data->deleteKeyFromStorage("value");
        free ( buffer );
        buffer = nullptr;

        //Are Shortcut to Map we set already
        int tileCount = map->getKeyAsInt("width") * map->getKeyAsInt("height");

        for ( int i = 0; i < tileCount; i++ ) {
            node->data.push_back(out[i]);
        }
        return;
    }

        // gzip & zlib Decompress routine
    if ( compression == "gzip" || compression == "zlib" ) {
        unsigned char *buffer;
        auto len = ax::utils::base64Decode( (unsigned char *) data->getKeyAsString("value").c_str(), (unsigned int) data->getKeyAsString("value").length(), &buffer );

        if ( !buffer ) {
            AXLOG("axmol: TiledMap: decode data error" );
            return;
        }

        unsigned char *deflated = nullptr;
        int tileCount = map->getKeyAsInt("width") * map->getKeyAsInt("height");
        int sizeHint = tileCount * sizeof( uint32_t );
        ssize_t AX_UNUSED inflatedLen = ZipUtils::inflateMemoryWithHint(buffer, len, &deflated,sizeHint );
        AXASSERT(inflatedLen == sizeHint, "inflatedLen should be equal to sizeHint!");

        data->deleteKeyFromStorage("value");
        free( buffer );
        buffer = nullptr;

        if ( !deflated ) {
            AXLOG("axmol: TiledMap: inflate data error");
            return;
        }
        auto out = reinterpret_cast<uint32_t*>(deflated);
        for ( int i = 0; i < tileCount; i++ ) {
            node->data.push_back(out[i]);
        }
    }
}


/**************************************************************************************************
 * AddExtraDataToNodes                                                                            *
 **************************************************************************************************
 * Adds a rectangle/ keyword to the nodes so you don't have to scan for noting or dont exsit      *
 * it just seems to make more sense. when query a node type. allso adds shapeID ShapeName         *
 * for easy way to search for things                                                              *
 **************************************************************************************************/
void QuickTileMap::AddExtraDataToNodes( void )
{
//#define  ID_RECTANGLE     0
//#define  ID_POINT         1
//#define  ID_POLYGON       2
//#define  ID_POLYLINE      3
//#define  ID_ELLIPSE       4
//#define  ID_TEXT          5
//#define  ID_GID           6

    auto nodes = root->getChildByName("map")->getAllChildrenByName("object",1);
    for( auto fix : nodes ) {
        if( fix->keyExist("gid") ) { continue;  }
        auto obj = fix->getChildByName("ellipse/");
        if( obj ) { continue; }
        obj = fix->getChildByName("polygon");
        if( obj ) { continue; }
        obj = fix->getChildByName("polyline");
        if( obj ) { continue; }
        obj = fix->getChildByName("text");
        if( obj ) { continue; }
        obj = fix->getChildByName("point/");
        if( obj ) { continue; }

        fix->addChild("rectangle",-1);
    }

    nodes.clear();
    nodes = root->getChildByName("map")->getAllChildrenByName("object",1);
    for( auto obj : nodes ) {

        auto rectangle = obj->getChildByName("rectangle/");
        if(rectangle) {
            obj->addToStorage("shapeID", "0");
            obj->addToStorage("shapeName", "RECTANGLE");
            continue;
        }

        auto point= obj->getChildByName("point/");
        if(point) {
            obj->addToStorage("shapeID",   "1");
            obj->addToStorage("shapeName","POINT");
            point->setName("point");
            continue;
        }

        auto polygon = obj->getChildByName("polygon");
        if(polygon) {
            obj->addToStorage("shapeID",   "2");
            obj->addToStorage("shapeName","POLYGON");
            continue;
        }

        auto polyline = obj->getChildByName("polyline");
        if(polyline) {
            obj->addToStorage("shapeID",   "3");
            obj->addToStorage("shapeName","POLYLINE");
            continue;
        }

        auto ellipse = obj->getChildByName("ellipse/");
        if(ellipse) {
            obj->addToStorage("shapeID",   "4");
            obj->addToStorage("shapeName","ELLIPSE");
            ellipse->setName("ellipse");
            continue;
        }

        auto text = obj->getChildByName("text");
        if(text) {
            obj->addToStorage("shapeID",   "5");
            obj->addToStorage("shapeName","TEXT");
            continue;
        }

        if( obj->keyExist("gid") ) {
            obj->addToStorage("shapeID", "6");
            obj->addToStorage("shapeName", "GID");
        }
    }
}


/**************************************************************************************************
 * LoadMap                                                                                        *
 **************************************************************************************************
 * Load's a XML file and trims the \r\n                                                           *
 **************************************************************************************************/
SmartNode* QuickTileMap::LoadMap( std::string fileName ) {

     //Extra Speed no need to reload data or decrypt Tile compression alredy done
     //if map is the same

    if( FileUtils::getInstance()->fullPathForFilename(fileName) == mapFileName) {
         removeAllChildren();
         //Now we build and Display the TileMap Skip reloading
         delete root;
         root = SmartNode::create("root", -1);  // create rootNode
         BuildTileMap(map);
         return root;
    }  else  {
        root = SmartNode::create("root", -1);  // create rootNode
    }

    mapFileName = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());

    if ( FileUtils::getInstance()->isFileExist(mapFileName) == false ) {
         AXLOG("File Error Dose not Exsit: %s", fileName.c_str());
        return nullptr;
    }

    ssize_t DATASTREAM_SIZE = 0;
    auto fullpath = FileUtils::getInstance()->fullPathForFilename(mapFileName.c_str());
    std::string fileData;
    FileUtils::getInstance()->getContents(fullpath, &fileData);
    DATASTREAM_SIZE = fileData.size();

    if ( DATASTREAM_SIZE <= 0 ) {
        AXLOG("Error File empty");
        return 0;
    }

    // Process the FileData
    std::istringstream iss(fileData);
    std::string line;
    std::vector<std::string> xmlData;
    std::string currentTag;
    SmartNode *newChiled;
    SmartNode *lastNode = root;
    int layer = 0;
    while (std::getline(iss, line)) {
        xmlData.push_back(line);
    } // End While loop
    fileData.clear();

    xmlData = ConcatenateData(xmlData);

    /**
     * Build the SmartNode
     */
    for (auto xmlSting: xmlData) {
        std::string xmlTag = GetFirstTag(xmlSting);
        std::string spaces = GetFirstTagLeveSpace(xmlSting);
        int spacecount = GetXmlIndents(spaces);

        if (IsStrippable(xmlSting)) {
            newChiled = new SmartNode(xmlTag, -1);
            newChiled->storage = StripToMap(xmlSting);
        } else {
            newChiled = new SmartNode(xmlTag, -1);
        }

        if (newChiled->keyExist("id")) { //this is how to Access to storage
            newChiled->setTag(newChiled->getKeyAsInt("id")); // Set the node tag so can get by Tag
        }

        //Just adds storage["layer"] = layer number;
        // encase you want to know what layer it was on later
        // when adding another sprite behind or in front of layer
        if (xmlTag == "layer") {
            std::string number = std::to_string(layer);
            newChiled->addToStorage("layer", number);
            layer++;
        }

        //same as above comment
        if (xmlTag == "objectgroup" && spacecount < 2) {
            std::string number = std::to_string(layer);
            newChiled->addToStorage("layer", number);
            layer++;
        }

        //Insert into root of SmartNode
        if ( xmlTag == "map" || xmlTag == "xml" ) {
            lastNode = root->addChild(newChiled);
        }  else {
            //Insert into SmartNode
            if (xmlTag[0] == '/') {
                lastNode = lastNode->getParent();
                lastNode->addChild(newChiled);
            } else {
                if ( xmlSting[xmlSting.size() - 1] == '/') {
                    lastNode->addChild(newChiled);
                } else {
                    lastNode = lastNode->addChild(newChiled);
                }
            }
        }
    } // end for loop
    xmlData.clear();       // Everything in in SmartNode Clear the stack

    //Adds extra data like no rectangle
    // shapeID, ShapeName. For easy Identification
    AddExtraDataToNodes();

    root->cleanUpNodes();  // Remove all /properties, /property.  free's the memory

    //Creating Shortcut to map & tileset, you can create your owen as well.
    tileSet = root->getChildByName("tileset", 1);  // true = recuses find
    map = root->getChildByName("map", true);       // true = recuses find


    //Set Background colour
    auto colour = map->getKeyAsString("backgroundcolor");
    if (!colour.empty()) {
        auto colour4B = HTMLtoColour(colour);
        float r = MapTo(colour4B.r, 0.0,255.0 , 0.01 , 1.0 );
        float g = MapTo(colour4B.g, 0.0,255.0 , 0.01 , 1.0 );
        float b = MapTo(colour4B.b, 0.0,255.0 , 0.01 , 1.0 );
        Director::getInstance()->setClearColor( Color4F( r , g,  b, 1) );
    }


    //Now we build and Display the TileMap
      BuildTileMap(map);

    return root;
}


/**************************************************************************************************
 * CreateAnimation                                                                                *
 **************************************************************************************************
 * Creates and return's an animated sprite                                                        *
 * as a side note you lose the power to sprite->setContentSize() so use                           *
 * sprite->setScale( size.width / tileWidth , size.height / tileHeight );                         *
 * to scale after                                                                                 *
 **************************************************************************************************/
Sprite * QuickTileMap::CreateAnimation( SmartNode*  node )
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    //Error Checking
    if( !cache ) {
        AXLOG("Opps Cant Find SpriteFrameCache Did you load to SpriteSheet before Startup ?\r\n");
        AXLOG("//ZipUtils::setPvrEncryptionKey(0x5f1c402e, 0x625eaaf8, 0x55a4ee49, 0x22ffe0cf); //if Using Encryption add your number");
        AXLOG("SpriteFrameCache::getInstance()->addSpriteFramesWithFile(\"YourSpriteSheet.plist\");");
        return NULL;
    }
    char tileName[128];

    Animate* spriteActions;
    Vector<SpriteFrame*> animFrames;
    Sprite *sprite;

    auto frames = node->getVectorOfChildrenByName({"frame"} );
    if( !frames.empty() ) {
        sprintf(tileName, "%04d", frames[0]->getKeyAsInt("tileid") );
        sprite = Sprite::createWithSpriteFrameName(tileName);
        for (auto frame: frames) {
            sprintf(tileName, "%04d", frame->getKeyAsInt("tileid") );
            SpriteFrame* spriteFrame = cache->getSpriteFrameByName(  tileName );
            animFrames.pushBack(spriteFrame);
        }
        auto ani = Animation::createWithSpriteFrames(animFrames, frames[0]->getKeyAsFloat("duration"));
        ani->setDelayPerUnit(   frames[0]->getKeyAsFloat("duration") / 1000.0f  );
        ani->setRestoreOriginalFrame(false);
        spriteActions = Animate::create( ani );
        sprite->runAction( RepeatForever::create( spriteActions ) );
    }
    return sprite;
}



/**************************************************************************************************
 * GetAnimation                                                                                   *
 **************************************************************************************************
 * Creates and return's an animated sprite used for GID                                           *
 * this is to auto search the tileset if tile exsits it gets the ainmation frames from that tile  *
 * as a side note you lose the power to sprite->setContentSize() so use                           *
 * sprite->setScale( size.width / tileWidth , size.height / tileHeight );                         *
 * to scale after                                                                                 *
 **************************************************************************************************/
Sprite * QuickTileMap::GetAnimation( SmartNode*  node )
{
    Sprite*  sprite;

    uint32_t tileID  = node->getKeyAsInt("gid");;
    uint32_t ID =  tileID;
    ID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG |  FLIPPED_DIAGONALLY_FLAG);
    ID = (static_cast<int>((ID & kTMXFlippedMask)));

    auto test = node->getChildByName("animation",true);
            if ( test ) {
                return CreateAnimation( node );
            }

        if ( node->keyExist("gid") ) {

            ID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG |  FLIPPED_DIAGONALLY_FLAG);
            ID = (static_cast<int>((ID & kTMXFlippedMask)));

            auto tile = tileSet->getChildById( ID -1 ); // tile's in tileset start a 0

            if (tile) {          // Check if Tile Exists in tileSet
                auto animation = tile->getChildByName("animation");

                if (animation) {  // Check if there is animation

                    auto sprite =  CreateAnimation(animation);

                    if ( tileID & kTMXTileDiagonalFlag ) {
                        auto flag = tileID & (kTMXTileHorizontalFlag | kTMXTileVerticalFlag);
                        // handle the 4 diagonally flipped states.
                        if (flag == kTMXTileHorizontalFlag) {
                            sprite->setRotation(90.0f);
                        } else if (flag == kTMXTileVerticalFlag) {
                            sprite->setRotation(270.0f);
                        } else if (flag == (kTMXTileVerticalFlag | kTMXTileHorizontalFlag)) {
                            sprite->setRotation(90.0f);
                            sprite->setFlippedX(true);
                        } else {
                            sprite->setRotation(270.0f);
                            sprite->setFlippedX(true);
                        }
                    } else {
                        if (tileID & kTMXTileHorizontalFlag) {
                            sprite->setFlippedX(true);
                        }

                        if (tileID & kTMXTileVerticalFlag) {
                            sprite->setFlippedY(true);
                        }
                    }
                    return sprite;
                }
            }
        }

    char buffer[128];
    sprintf(buffer, "%04d", ID - 1 );  // tile's in tileset start a 0
    //See Header file on using .png or .jpeg
    #ifdef USE_EXTENSION
    sprintf(buffer, "%04d%s", ID , USE_EXTENSION );
    #else
    sprintf(buffer, "%04d", ID - 1);  // tile's in tileset start a 0
    #endif

    sprite = Sprite::createWithSpriteFrameName(buffer);

    if ( tileID & kTMXTileDiagonalFlag ) {
        auto flag = tileID & (kTMXTileHorizontalFlag | kTMXTileVerticalFlag);
        // handle the 4 diagonally flipped states.
        if (flag == kTMXTileHorizontalFlag) {
            sprite->setRotation(90.0f);
        } else if (flag == kTMXTileVerticalFlag) {
            sprite->setRotation(270.0f);
        } else if (flag == (kTMXTileVerticalFlag | kTMXTileHorizontalFlag)) {
            sprite->setRotation(90.0f);
            sprite->setFlippedX(true);
        } else {
            sprite->setRotation(270.0f);
            sprite->setFlippedX(true);
        }
    } else {
        if (tileID & kTMXTileHorizontalFlag) {
            sprite->setFlippedX(true);
        }

        if (tileID & kTMXTileVerticalFlag) {
            sprite->setFlippedY(true);
        }
    }

    return sprite;
}


/*************************************************************************************************
** addTextComponent                                                                             **
**************************************************************************************************
** @param addTextComponent( String )                                                             **
** @return The Label*                                                                           **
**************************************************************************************************
** Add's A Text Component From BMI  "SpriteSheet.png"                                           **
** Tip.  Create your font and add the font.png to you SpriteSheet with texture Packer.          **
** Edit your "font.fnt" file and goto the line -> file="../font.png" and change it to           **
**                                                          ^^^^                                **
**                                                file="../YourSpriteSheetName.png"             **
**************************************************************************************************/
Label* QuickTileMap::CreateTextLabel( std::string text ) {
    auto frame =  SpriteFrameCache::getInstance()->getSpriteFrameByName("Factory_0");
    auto label = Label::createWithBMFont("Factory.fnt", text, TextHAlignment::LEFT, 0, frame->getRectInPixels(), frame->isRotated());
    return label;
}

/*************************************************************************************************
** CreateTextLabel                                                                              **
**************************************************************************************************
** @param addTextComponent( String TextMsg, SpriteName , FontFileName);                         **
** @return The Label*                                                                           **
**************************************************************************************************
** Same as above except yse your different font                                                   **
**************************************************************************************************/

Label* QuickTileMap::CreateTextLabel( std::string text , std::string fontSpriteName , std::string fontFileName   ) {
    auto frame =  SpriteFrameCache::getInstance()->getSpriteFrameByName(fontSpriteName );
    auto label = Label::createWithBMFont(fontFileName, text, TextHAlignment::LEFT, 0, frame->getRectInPixels(), frame->isRotated());
    return label;
}

Color4B QuickTileMap::GetObjectColour( SmartNode* node ) {
    Color4B colour4B = Color4B::WHITE;
   // int objectOpacity = 255;
    if ( node->keyExist("color") ) {
        auto colour = node->getKeyAsString("color");
        if (!colour.empty()) {
            colour4B = HTMLtoColour(colour);
            colour4B.a = MapTo(colour4B.a, 255.0, 0.0, 0.0, 255.0);
            return colour4B;
        }
        //if (colour4B.a != 1)
            //objectOpacity = colour4B.a;
    }
    return Color4B::WHITE;
}

/**************************************************************************************************
 * GetPropertiesAsVector                                                                          *
 **************************************************************************************************
 * Return's a vector of property from properties                                                  *
 * to use you then just                                                                           *
 *           node->getKeyAsInt("tilewidth");                                                      *
 *           node->getKeyAsString("name");                                                        *
 *           node->getKeyAsFloat("value");                                                        *
 *           node->getKeyAsLong("value")                                                          *
 *           node->getKeyAsBool("value")                                                          *
 *           node->getKeyAsChar("tintcolor")                                                      *
 *          if( node->keyExist("name") ) {                                                        *
 *          }                                                                                     *
 *                                                                                                *
 *          Debug and help                                                                        *
 *          SmartNode::ShowDebugInfo(node);                                                       *
 *          node->ShowAllStorage();                                                               *
 **************************************************************************************************/
std::vector<SmartNode*>QuickTileMap::GetPropertiesAsVector( SmartNode * node ) {
    std::vector<SmartNode*>property;
    auto properties = node->getChildByName("properties");
    if ( properties ) {
        auto foundNode = properties->getVectorOfChildrenByName({"property"});
        for (auto found: foundNode) {
            property.push_back( found );
        }
    }
    return property;
}

/**************************************************************************************************
 * GetAllPropertiesAsVector                                                                       *
 **************************************************************************************************
 * Returns all found properties nodes in vector                                                   *
 *************************************************************************************************/
std::vector<SmartNode*>QuickTileMap::GetAllPropertiesAsVector( SmartNode * node ) {
      return node->getVectorOfChildrenByName( {"properties"} );
}


/**************************************************************************************************
 * GetAction                                                                                      *
 **************************************************************************************************
 * Create and return a finite Action that will be pushed onto a sequence buffer                   *
 * part of CreateActions().                                                                       *
 *************************************************************************************************/

FiniteTimeAction* QuickTileMap::GetAction( std::map<std::string,std::string> &action , Sprite* sprite )
{
    if ( action["DelayTime"].size() > 0  ) {
        float duration = std::atof( action["Duration"].c_str() );
        return DelayTime::create(duration );
    }

    if ( action["Blink"].size() > 0  ) {
        float duration = std::atof( action["Duration"].c_str() );
        int times = std::atoi( action["Times"].c_str() );
        return Blink::create(duration, times);
    }

    if ( action["MoveBy"].size() > 0  ) {
        float x = std::atof( action["X"].c_str() );
        float y = std::atof( action["Y"].c_str() );
        float duration = std::atof( action["Duration"].c_str() );
        return MoveBy::create( duration,Vec2( x, y) );
    }

    if ( action["MoveTo"].size() > 0  ) {
        float x = std::atof( action["X"].c_str() );
        float y = std::atof( action["Y"].c_str() );
        float duration = std::atof( action["Duration"].c_str() );
        return MoveTo::create( duration,Vec2( x, y) );
    }

    if ( action["ScaleBy"].size() > 0  ) {
        float x = std::atof( action["X"].c_str() );
        float y = std::atof( action["Y"].c_str() );
        float duration = std::atof( action["Duration"].c_str() );
        return ScaleBy::create( duration,1 * x, 1 * y );
    }

    if ( action["ScaleTo"].size() > 0  ) {
        float x = std::atof( action["X"].c_str() );
        float y = std::atof( action["Y"].c_str() );
        float duration = std::atof( action["Duration"].c_str() );
        return ScaleTo::create( duration, x / sprite->getContentSize().width , y / sprite->getContentSize().height );
      }

    if ( action["RotateTo"].size() > 0  ) {
        float x = std::atof( action["X"].c_str() );
        float y = std::atof( action["Y"].c_str() );
        float duration = std::atof( action["Duration"].c_str() );
        float angle = std::atof( action["Angle"].c_str() );
        if( x != 0 || y !=0 )
            sprite->setAnchorPoint(Vec2( x, y));
        else
            sprite->setAnchorPoint(Vec2( 0.5,0.5));
        return RotateTo::create( duration, angle );
    }

    if ( action["RotateBy"].size() > 0  ) {
        float x = std::atof( action["X"].c_str() );
        float y = std::atof( action["Y"].c_str() );
        float duration = std::atof( action["Duration"].c_str() );
        float angle = std::atof( action["Angle"].c_str() );

        if( x != 0 || y !=0 )
            sprite->setAnchorPoint(Vec2( x, y));
        else
            sprite->setAnchorPoint(Vec2( 0.5,0.5));
        return RotateBy::create( duration, angle );
        }


    if ( action["FadeOut"].size() > 0  ) {
        float duration = std::atof( action["Duration"].c_str() );
        return FadeOut::create( duration );
    }

    if ( action["FadeIn"].size() > 0  ) {
        float duration = std::atof( action["Duration"].c_str() );
        return FadeIn::create( duration );
    }

    if ( action["Remove Self"].size() > 0  ) {
        return RemoveSelf::create( true );
    }

    return nullptr;
}



/**************************************************************************************************
 * CreateActions                                                                                  *
 **************************************************************************************************
 * Creates and runs Actions from properties                                                       *
 *************************************************************************************************/
void QuickTileMap::CreateActions( SmartNode* properties , Sprite* sprite )
 {
    auto test = properties->getChildByName("properties");

    if ( !test ) {
       return;
    }

     bool  repeatForever = false;
     bool  repeat        = false;
     int   repeatAmount  = 0;
     ax::Vector<ax::FiniteTimeAction*>sequenceBuffer;

          for ( auto child : test->getChildren() ) {
              auto prototype = child->getKeyAsString("propertytype");

              /**
               * Get One Action
               ***/
              if ( prototype == "Action" ) {
                  std::map<std::string, std::string> data;
                  auto property = child->getAllChildrenByName("property", true);
                  for (auto p: property) {
                      if (p->getKeyAsString("name") == "ActionType") {
                          data[p->getKeyAsString("value")] = p->getKeyAsString("name");
                      } else {
                          data[p->getKeyAsString("name")] = p->getKeyAsString("value");
                      }
                  }

                  //Now get the Action
                  auto action = GetAction(data, sprite);
                  if (action)
                      sequenceBuffer.pushBack(action);

                  if ( data["Repeat"].size() > 0  ) {
                      repeat = true;
                      repeatAmount =  std::atoi( data["Times"].c_str() );
                  }

                  if ( data["Repeat Forever"].size() > 0  ) {
                      repeatForever = true;
                  }
              }

                /**
                 * Get Two Actions
                 ***/
              if( prototype == "ActionTwo" ) {
                  std::vector<FiniteTimeAction*> actions ;
                  // Get the ptr to the 2 actions
                  auto towActions = child->getNext()->getAllChildrenByName(  "property" );
                       for( auto node : towActions ) {
                           //Now get action1 and Action2
                            auto property = node->getNext()->getAllChildrenByName("property");
                            std::map<std::string, std::string> data;
                            //get the property value and name, X, Y, Duration, MoveBy, etc
                            for( auto p : property ) {
                              if ( p->getKeyAsString("name") == "ActionType") {
                                   data[ p->getKeyAsString("value" ) ] = p->getKeyAsString("name" );
                               } else {
                                   data[ p->getKeyAsString("name" ) ] = p->getKeyAsString("value" );
                               }
                            }

                            //Now get one Action and and push back
                            auto action = GetAction(data , sprite);
                            if( action ) {
                                actions.push_back( action );
                            }
                        }

               if ( actions[0] && actions[1]) {
                      auto  twoAction = Spawn::createWithTwoActions(actions[0],actions[1]);
                      sequenceBuffer.pushBack(twoAction);
                  }
              }
          } // End for Loop

     if ( sequenceBuffer.empty() ){ return; }
       Sequence* seq = Sequence::create( sequenceBuffer);

     if( repeatForever ||  repeat ) {
         if( repeatForever )
             sprite->runAction(RepeatForever::create(seq));
         else
             sprite->runAction(Repeat::create(seq, repeatAmount ) );
     } else {
             sprite->runAction(seq);
     }
 }


/**************************************************************************************************
* BuildTileMap()                                                                                  *
* *********************************************************************************************** *
* Starts building of the tile map                                                                 *
* *********************************************************************************************** *
*  Debug Functions                                                                                *
*   tile->showAllNode();                                                                          *
*   tile->showAllStorage();                                                                       *
*   tile->showAllChildren();                                                                      *
*   SmartNode::ShowTree(map); , root, node , tileSet , etc                                        *
*   SmartNode::ShowDebugInfo(tile);                                                               *
*   Remember you dealing with pointers some pointers maybe nullptr;                               *
*   so use if ( tile ) { Check, if Not NULL ptr                                                   *
*         //Then do something with tile, layer, etc                                               *
*    }                                                                                            *
**************************************************************************************************/

void QuickTileMap::BuildTileMap( SmartNode* rootNode )
{

#ifdef USE_Z_ORDER
    auto tileMapNodes = map->getVectorOfChildrenByName( { "objectgroup", "layer" } , false);  // false Not to reverse the order
#else
     auto tileMapNodes = rootNode->getVectorOfChildrenByName({ "objectgroup", "layer", "imagelayer", "group"},false);  // true to reverse the order
#endif

    for( auto node  : tileMapNodes) {

        if ( node->getName() == "group" ) {
            // Recursively process child nodes
            if(!node->keyExist("visible"))
              BuildTileMap(node);
         }


        /** Do something with an imagelayer **/
        if ( node->getName() == "imagelayer" ) {
            /**
            auto width = map->getKeyAsInt("width");
            auto height = map->getKeyAsInt("height");
            auto tileWidth = map->getKeyAsInt("tilewidth");
            auto tileHeight = map->getKeyAsInt("tileheight");
            AXLOG("%s", node->getNext()->getKeyAsString("source").c_str() );
            std::string image = node->getNext()->getKeyAsString("source").c_str();
            image.erase(0,3);
            auto imageLayer = Sprite::create(image);
            imageLayer->setPosition(node->getKeyAsFloat("offsetx")  , node->getKeyAsFloat("offsety")  );
            addChild(imageLayer , node->getKeyAsInt("level"));
             **/
             // I dont use them as they add layers and dont know where your dir for your images
             // This is if you want image layers my maps are in /Content/Maps/ so erase 3
             // from string for your ../Content/image.png directory remove the ../
        }


        //This Creates Tilemap Layer's
        /** Move this to your owen Function if you wish to unclutter
         *  Example: BuildLayer(SmartNode* layerNode); <- and just pass it the node
         ***/
        if ( node->getName() == "layer") { // <-- leave check here & put function here insted.
            //Setup Node
            Node *layer = Node::create();
            layer->setTag(node->getKeyAsInt("layer"));
            layer->setName(node->getKeyAsString("name"));

            auto width = map->getKeyAsInt("width");
            auto height = map->getKeyAsInt("height");
            auto tileWidth = map->getKeyAsInt("tilewidth");
            auto tileHeight = map->getKeyAsInt("tileheight");
            layer->setContentSize(Size(width * tileWidth, height * tileHeight));
            layer->setPosition(0, height * tileHeight);

            if (node->keyExist("visible")) {
                layer->setVisible(false);
            }

            //Decrypts tile values of the file Storage["value"] Once only.
            DecryptTileData(node);

            char tileName[128];
            uint32_t tilepos = 0;
            uint32_t tileID = 0;
            uint32_t ID = 0;
            Sprite *tileSprite;
            int opacity = 255;

            if (node->keyExist("opacity")) {
                opacity = node->getKeyAsFloat("opacity") * 255;
            }

            Color4B colour4B = Color4B::WHITE;
            Color3B colour3B = Color3B::WHITE;

            if (node->keyExist("tintcolor")) {
                auto colour = node->getKeyAsString("tintcolor");
                if (!colour.empty()) {
                    auto colour4B = HTMLtoColour(colour);
                    colour3B.r = colour4B.r;
                    colour3B.g = colour4B.g;
                    colour3B.b = colour4B.b;
                    opacity    = MapTo(colour4B.a , 255.0,0.0 , 0.0 , 255.0 );
                }
                if (colour4B.a != 1 )
                    opacity = colour4B.a;
            }

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    tilepos = (y * width) + x;
                    tileID = node->data[tilepos];
                    ID = tileID;

                    ID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
                    ID = (static_cast<int>((ID & kTMXFlippedMask)));

                    if (ID != 0) {
                        ID = ID - 1;

                        //See Header file on using .png or .jpeg
#ifdef USE_EXTENSION
                        sprintf(tileName, "%04d%s", ID , USE_EXTENSION );
                         AXLOG("%s",tileName);
#else
                        sprintf(tileName, "%04d", ID);
#endif


                        //Check for Animation
                        auto tile = tileSet->getChildById(ID );
                        if (tile) {          // Check if Tile Exists in tileSet
                            auto animation = tile->getChildByName("animation");
                            if (animation) { // Check if there is animation
                                tileSprite = CreateAnimation(animation);
                            } else {          // else no animation normal tile
                                tileSprite = Sprite::createWithSpriteFrameName(tileName);
                            }
                        } else {            // No Tile Exists in tileSet normal tile
                            tileSprite = Sprite::createWithSpriteFrameName(tileName);
                        }

#ifdef USE_Z_ORDER
                        tileSprite->setPosition(x * tileWidth + node->getKeyAsFloat("offsetx") + tileWidth / 2 ,  (y * -tileHeight + node->getKeyAsFloat("offsety") - tileHeight / 2) + ( height * tileHeight)  );
#else
                        tileSprite->setPosition(((x * tileWidth)) + tileWidth / 2,((y * -tileHeight)) - tileHeight / 2);
#endif

                        tileSprite->setColor(colour3B);
                        tileSprite->setOpacity(opacity);

                        tileSprite->setScale(1.00, 1.00);
                        tileSprite->setFlippedX(false);
                        tileSprite->setFlippedY(false);
                        tileSprite->setRotation(0.0f);
                        tileSprite->setAnchorPoint(Vec2(0.5, 0.5));

                        tileSprite->setTag(tilepos);

                        if (tileID & kTMXTileDiagonalFlag) {
                            auto flag = tileID & (kTMXTileHorizontalFlag | kTMXTileVerticalFlag);
                            // handle the 4 diagonally flipped states.
                            if (flag == kTMXTileHorizontalFlag) {
                                tileSprite->setRotation(90.0f);
                            } else if (flag == kTMXTileVerticalFlag) {
                                tileSprite->setRotation(270.0f);
                            } else if (flag == (kTMXTileVerticalFlag | kTMXTileHorizontalFlag)) {
                                tileSprite->setRotation(90.0f);
                                tileSprite->setFlippedX(true);
                            } else {
                                tileSprite->setRotation(270.0f);
                                tileSprite->setFlippedX(true);
                            }
                        } else {
                            if (tileID & kTMXTileHorizontalFlag) {
                                tileSprite->setFlippedX(true);
                            }

                            if (tileID & kTMXTileVerticalFlag) {
                                tileSprite->setFlippedY(true);
                            }
                        }
#ifdef USE_Z_ORDER
                        addChild(tileSprite, node->getKeyAsInt("layer") );
#else
                        layer->addChild(tileSprite);
#endif
                    }
                } // End For x
            } // End For y
#ifndef USE_Z_ORDER
            layer->setPosition(layer->getPositionX() + node->getKeyAsFloat("offsetx"),
                               layer->getPositionY() - node->getKeyAsFloat("offsety"));
            addChild(layer, node->getKeyAsInt("layer"));
#endif
        }  //End fo creating a layer


        /**
         * This Creates objectgroup's
         **/

        if ( node->getName() == "objectgroup" ) {
            auto width = map->getKeyAsInt("width");
            auto height = map->getKeyAsInt("height");
            auto tileWidth = map->getKeyAsInt("tilewidth");
            auto tileHeight = map->getKeyAsInt("tileheight");
            Vec2 mapSize = Vec2(width * tileWidth, height * tileHeight);


#ifndef USE_Z_ORDER
            Node *objectgroup = Node::create();
            objectgroup->setTag(node->getKeyAsInt("layer"));
            objectgroup->setName(node->getKeyAsString("name"));
            objectgroup->setContentSize(mapSize);
            objectgroup->setPosition(origin.x, origin.y);

            if (node->keyExist("visible")) {
                objectgroup->setVisible(false);
            }
            addChild(objectgroup, node->getKeyAsInt("layer"));
#endif

            int opacity = 255;
            if (node->keyExist("opacity")) {
                opacity = node->getKeyAsFloat("opacity") * 255;
            }


            Color4B colour4B = Color4B::WHITE;
            Color3B colour3B = Color3B::WHITE;
            if (node->keyExist("tintcolor")) {
                auto colour = node->getKeyAsString("tintcolor");
                if (!colour.empty()) {
                    colour4B = HTMLtoColour(colour);
                    colour3B.r = colour4B.r;
                    colour3B.g = colour4B.g;
                    colour3B.b = colour4B.b;
                    opacity = MapTo(colour4B.a, 255.0, 0.0, 0.0, 255.0);
                }
                if (colour4B.a != 1)
                    opacity = colour4B.a;
            }

            /**  Get gid Objects **/
            auto smartNodes = node->getVectorOfChildrenByName({"object"});

            for (auto smartNode: smartNodes) {

                //Start GID Sprite Animation, Physics and all that good stuff
                if (smartNode->keyExist("gid")) {

                    Sprite *sprite = GetAnimation(smartNode);

                    if (smartNode->keyExist("visible")) {
                        sprite->setVisible(false);
                    }

                    auto size = Vec2(smartNode->getKeyAsFloat("width"),
                                     smartNode->getKeyAsFloat("height"));

                    if (smartNode->keyExist("rotation")) {
                        sprite->setAnchorPoint(Vec2(0.0, 0.0));
                        sprite->setRotation(smartNode->getKeyAsFloat("rotation"));
                        sprite->setScale(size.x / tileWidth, size.y / tileHeight);
                        sprite->setPosition(smartNode->getKeyAsFloat("x"),
                                            -smartNode->getKeyAsFloat("y") + mapSize.height);
                    } else {
                        sprite->setAnchorPoint(Vec2(0.5, 0.5));
                        sprite->setScale(size.x / tileWidth, size.y / tileHeight);
                        sprite->setPosition(smartNode->getKeyAsFloat("x") + size.x / 2,
                                            -smartNode->getKeyAsFloat("y") + size.y / 2 +
                                            mapSize.height);
                    }

                    sprite->setColor(colour3B);
                    sprite->setOpacity(opacity);

                    //Actions from Properties. MoveTo, RotateBy, etc
                    CreateActions(smartNode, sprite);

                    //Get Physics from Tiled tileSet
                    auto physics = GetPhysics(smartNode);

                    if (physics) { //Remember Not all tile have physics so must check
                        //Loop out and build to one B2body if box2d you now have complex part
                        AXLOG("%zu", physics->getChildrenSize());
                        for (auto physicsPart: physics->getChildren()) {
                            AXLOG("ID:%d X:%f Y:%f Type:%s", physicsPart->getKeyAsInt("id"),
                                  physicsPart->getKeyAsFloat("x"), physicsPart->getKeyAsFloat("y"),
                                  physicsPart->getNext()->getName().c_str());
                        }
                    }
#ifdef USE_Z_ORDER
                    addChild(sprite,node->getKeyAsInt("layer"));
#else
                    objectgroup->addChild(sprite);
#endif
                } else {

                    /**
                     * This Creates Physics object's only, no gid number
                     **/

                    //EZ first method speed
                    switch (smartNode->getKeyAsInt("shapeID")) {
                        case ID_TEXT:
                            // AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                            break;
                        case ID_RECTANGLE:
                            // AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                            break;
                        case ID_ELLIPSE:
                            // AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                            break;
                        case ID_POINT:
                            // AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                            break;
                        case ID_POLYGON:
                            // AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                            break;
                        case ID_POLYLINE:
                            //  AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                            break;
                    }

                    //Else Manule get Physics
                    /**  Getting Text Move this to your owen Function if you wish to declutter **/
                    SmartNode *object = smartNode->getChildByName("text");
                    if (object) { // if text
                        //This is the object part
                        float x = smartNode->getKeyAsFloat("x");
                        float y = smartNode->getKeyAsFloat("y");
                        float width = smartNode->getKeyAsFloat("width"); //My font size
                        float height = smartNode->getKeyAsFloat("height");
                        float pixalSize = object->getKeyAsFloat("pixelsize");

                        //if you have added property's
                        auto property = GetPropertiesAsVector(smartNode);
                        //Loop through them and do someting with them

                        //Now extract your wrap , font name , etc
                        if (object->keyExist("wrap")) {
                            // do wrap
                        }

                        std::string yourText = object->getKeyAsString(
                                "value"); //value is always data it was converted in ConcatenateData() because of \r\n
                        //AXLOG("yourString >> %s", yourString.c_str());
                        Label *bitmapText = CreateTextLabel(yourText);
                        bitmapText->setContentSize(Vec2(width, height));
                        bitmapText->setBMFontSize(pixalSize);
                        bitmapText->setAnchorPoint(Vec2(0, 0));
                        bitmapText->setPosition(x,
                                                -y + mapSize.height - height); // Should make macro
                        bitmapText->setRotation(smartNode->getKeyAsFloat("rotation"));
                        if (object->keyExist("color")) {
                            auto colour = GetObjectColour(object);
                            bitmapText->setColor(Color3B(colour.r, colour.g, colour.b));
                            bitmapText->setOpacity(colour.a);
                        }
#ifdef USE_Z_ORDER
                        addChild(bitmapText,node->getKeyAsInt("layer"));
#else
                        objectgroup->addChild(bitmapText);
#endif
                    }  // End Getting Text


                    object = smartNode->getChildByName("point");
                    if (object) { //Get Physics
                        //AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                    }

                    object = smartNode->getChildByName("ellipse");
                    if (object) { //Get Physics
                        //AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                    }

                    object = smartNode->getChildByName("polygon");
                    if (object) { //Get Physics
                        // AXLOG("ID:%d X:%f Y:%f Type:%s\npoints:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y") , smartNode->getNext()->getName().c_str(),smartNode->getNext()->getKeyAsChar("points"));
                        // AXLOG("%s",object->getKeyAsChar("points"));
                        // AXLOG("%s",smartNode->getNext()->getKeyAsChar("points"));
                        // auto p = smartNode->getChildByName("polygon");
                        // AXLOG("%s",p->getKeyAsChar("points"));
                        // AXLOG("%s", object->storage["points"].c_str() );
                    }

                    object = smartNode->getChildByName("polyline");
                    if (object) {  //Get Physics
                        // AXLOG("ID:%d X:%f Y:%f Type:%s\npoints:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y") , smartNode->getNext()->getName().c_str(),smartNode->getNext()->getKeyAsChar("points"));
                        // AXLOG("%s",object->getKeyAsChar("points"));
                        // AXLOG("%s",smartNode->getNext()->getKeyAsChar("points"));
                        // auto p = smartNode->getChildByName("polyline");
                        // AXLOG("%s",p->getKeyAsChar("points"));
                        // AXLOG("%s", object->storage["points"].c_str() );
                    }


                    object = smartNode->getChildByName("rectangle");
                    if (object) {
                        // AXLOG("ID:%d X:%f Y:%f Width:%f Height:%f Type:%s",smartNode->getKeyAsInt("id"),smartNode->getKeyAsFloat("x"),smartNode->getKeyAsFloat("y"),smartNode->getKeyAsFloat("width"),smartNode->getKeyAsFloat("height") , smartNode->getNext()->getName().c_str());
                    }
                }
            } // End for Loop
        }
    }
} // End BuildTileMap();



