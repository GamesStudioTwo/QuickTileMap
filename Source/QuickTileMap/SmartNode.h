//
// Created by Admin on 19/06/2024.
//

#ifndef SMARTNODE_H
#define SMARTNODE_H

//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>


#include "axmol.h"  // For Printing debug

class SmartNode {

private:
    int tag;
    std::string name;
    SmartNode*  parentNode;
    SmartNode*  currentNode;
    std::vector<SmartNode*> children;


    void ShowNodes() const;

public:
    std::map<std::string, std::string> storage;
    std::vector<unsigned int> data;

    SmartNode* getChild( void );
    SmartNode* getChildAtIndex(size_t index);
    SmartNode* getChildById(int tag, bool searchNodes = false);
    SmartNode* getChildByName( const std::string& nodeName, bool searchNodes = false );
    std::vector<SmartNode*> getAllChildrenByTag( int id );
    std::vector<SmartNode*> getAllChildrenByName( const std::string& name ,bool searchNodes =0);
    std::vector<SmartNode*> getVectorOfChildrenByName(const std::vector<std::string>& names, bool reverseOrder = 0);
    std::vector<SmartNode*> getChildren( void );
    size_t getChildrenSize() const;

    SmartNode(int tag, const std::string& name) : tag(tag), name(name), parentNode(nullptr), currentNode(nullptr) {}
    SmartNode(const std::string& name) : name(name), parentNode(nullptr), currentNode(nullptr) {}
    SmartNode(const std::string& nodeName, int nodeTag) : name(nodeName), tag(nodeTag), parentNode(nullptr) {}


    SmartNode* addChild(SmartNode* child);
    SmartNode* addChild(const std::string& childName, int childTag);
    void removeChildByName(const std::string& childName);
    bool removeChild( SmartNode* child );
    void removeAllChildren( void );

    void removeAllChildrenByName(const std::string& name);
    void removeAllChildrenByNode(SmartNode* node);
    static bool startsWithSlash(SmartNode* child);
    void cleanUpNodes(void);
    std::vector<std::string> getPathToNode(SmartNode* node);
    std::string getPathToNodeAsString(SmartNode* node);
    SmartNode*  getPathToNodeByName(SmartNode* root, const std::string& name);
    SmartNode*  getPathToNodeByName( const std::string& name );
    std::vector<SmartNode*> searchByName(const std::string& searchName);
    std::vector<SmartNode*> getPathToNodeSearch(const std::string& nodeName);
    SmartNode* clone() const;
    bool removeFromParent( void );
    SmartNode* getParent( void );
    SmartNode* getNext( void );
    SmartNode* getRootNode( void );
    int  getTag(void) const;
    void setTag(int tagNumber);
    std::string getName(void) const;
    void setName(const std::string& nodeName);

    //Debug Help
     void ShowAllNode() const;
     void ShowAllChildren() const;

    /**  Map-related functions **/
    bool keyExist( const std::string& key );
    bool addToStorage( const std::string& key, const std::string& value );
    int  setStorageData( const std::string& key , const std::string& value );
    std::string getFromStorage(const std::string& key) const;
    void removeFromStorage( const std::string& key );

    SmartNode* getNodeWithData( const std::string tag , const std::string key );
    SmartNode* getNextTag(  const std::string tag  );

    bool  findKeyFromStorage( const std::string& key );
    bool  deleteKeyFromStorage( const std::string& key );
    std::string getKeyAsString( const std::string& key );
    char * getKeyAsChar( const std::string& key );
    float  getKeyAsFloat( const std::string& key );
    int    getKeyAsInt( const std::string& key );
    long   getKeyAsLong( const std::string& key );
    bool   getKeyAsBool( const std::string& key );
    void   ShowAllStorage( void ) const;

    // Forward iterator for child nodes
    class Iterator {
    public:
        Iterator(std::vector<SmartNode*>::iterator it) : current(it) {}
        Iterator& operator++() {
            ++current;
            return *this;
        }
       bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
        SmartNode* operator*() const {
            return *current;
        }
    private:
        std::vector<SmartNode*>::iterator current;
    };
    Iterator begin() {
        return Iterator(children.begin());
    }
    Iterator end() {
        return Iterator(children.end());
    }


    static SmartNode* create( const std::string& name ,int tag ) {
        SmartNode* node = new SmartNode(tag, name);
         return node;
    }


    // Function to print the tree (for testing)
    static void ShowTree(SmartNode* node, int depth = 0) {
        if (!node) { return; }
        AXLOG("%*s%s (Children: %zu)\n", 2 * depth, "", node->name.c_str(), node->children.size());
        for (const auto& child : node->children) {
            ShowTree(child, depth + 1);
        }
    }

    // Function to print the tree (for testing)
    static void ShowDebugInfo(SmartNode* node, int depth = 0) {
        if (!node) { return; }
        if( node->keyExist("id") )
        AXLOG("********** Debug Object ID: %s ************\n",node->storage["id"].c_str());
        AXLOG("%*s%s (Children: %zu)\n", 2 * depth, "", node->name.c_str(), node->children.size());
       for (const auto& pair : node->storage) {
            AXLOG("%*s Storage Data: %s : %s",2 * depth, "", pair. first.c_str(), pair.second.c_str() );
        }
        AXLOG("********************************************");
        for (const auto& child : node->children) {
            ShowDebugInfo(child, depth + 1);
        }
    }



    // Destructor to free memory when the SmartNode is deleted
    ~SmartNode() {
       removeAllChildren();
    }
};



#endif //QUICKTILEMAP_SMARTNODE_H
