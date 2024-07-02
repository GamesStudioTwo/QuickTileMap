//
// Created by Admin on 16/05/2024.
//

#ifndef MAZEOFDEATH_DEBUGNODES_H
#define MAZEOFDEATH_DEBUGNODES_H

#include "axmol.h"
#include "box2d/box2d.h"
#include "extensions/axmol-ext.h"

using namespace ax;
using namespace ax::extension;

/** Part for the Tree View return Type of class**/
#define  CREATE_TYPE(typeName)  else if(dynamic_cast<typeName*>(node)) { return #typeName; }

class DebugNodes : public Node {

public:
    std::vector<std::string> DataTree;
    std::string              output;
    virtual bool init();
    static Node* createNode();
    CREATE_FUNC(DebugNodes);

    void BuildDebugTree( std::string &string , Node* node, int setPosition );
    void DebugNode( Node* node );
    std::string getNodePosition( Node* node, int setPosition );
    std::string getNodeProperty( Node *node );
    bool isLastChild( Node* node );
    std::string getNodeTypeByName(Node *node);

};


#endif //MAZEOFDEATH_DEBUGNODES_H
