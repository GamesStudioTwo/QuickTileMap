//
// Created by Admin on 16/05/2024.
//

#include "DebugNodes.h"

Node* DebugNodes::createNode() {
    return DebugNodes::create();
}

// on "init" you need to initialize your instance
bool DebugNodes::init() {

    //////////////////////////////
    // 1. super init first
    if (!Node::init()) {
        return false;
    }

    return true;
}

/*************************************************************************************************
** BuildDebugTree                                                                               **
**************************************************************************************************
** @param BuildDebugTree(output, this , 1);                                                     **
** @return NULL takes &std::string                                                              **
**************************************************************************************************
** Builds a text tree and print it to string; Shows the node Order in engine for tracing        **
** Used For Debug of your nodes                                                                 **
*************************************************************************************************/
void DebugNodes::BuildDebugTree( std::string &string , Node* node, int setPosition ) {

    for ( auto obj : node->getChildren() ) {
        auto childNode = static_cast<Node*>( obj );
        string += getNodePosition( childNode , setPosition );
        string += getNodeProperty( childNode );
        string += '\n';
        BuildDebugTree( string , childNode , setPosition + 1 );
        DataTree.push_back(string);
        string.clear();
    }
} // End Print Tree for Debug

/**************************************************************************************************
 * getNodeTypeByName(Node *node) Part of BuildDebugTree
 **************************************************************************************************/
std::string DebugNodes::getNodeTypeByName(Node *node) {
    if( !node ) { return "UNKNOWN TYPE"; }
    CREATE_TYPE(ClippingNode)
    CREATE_TYPE(ClippingRectangleNode)
    CREATE_TYPE(Scene)
    CREATE_TYPE(Layer)
    CREATE_TYPE(Action)
    CREATE_TYPE(Sprite)
    CREATE_TYPE(Label)
    CREATE_TYPE(Menu)
    CREATE_TYPE(MenuItem)
    CREATE_TYPE(MenuItemFont)
    CREATE_TYPE(MenuItemAtlasFont)
    CREATE_TYPE(MenuItemSprite)
    CREATE_TYPE(MenuItemImage)
    CREATE_TYPE(MenuItemLabel)
    CREATE_TYPE(PhysicsBody)
    CREATE_TYPE(PhysicsWorld)
    CREATE_TYPE(PhysicsSpriteBox2D)
    //CREATE_TYPE(ui::Button)
    //CREATE_TYPE(ScrollView)
    //CREATE_TYPE(ListView)
    //CREATE_TYPE(ui::Widget)
    CREATE_TYPE(Image)
    CREATE_TYPE(Camera)
    CREATE_TYPE(ParticleSystem)
    CREATE_TYPE(Sequence)
    CREATE_TYPE(Timer)
    CREATE_TYPE(RepeatForever)
    CREATE_TYPE(Node)
    return "UNKNOWN TYPE";
}

/**************************************************************************************************
 * isLastChild(Node* node) Part of BuildDebugTree
 **************************************************************************************************/
bool DebugNodes::isLastChild( Node* node )
{
    Node * parent = node->getParent();
    return parent->getChildren().getIndex(node) == parent->getChildrenCount()-1;
}

/**************************************************************************************************
 * getNodeProperty(Node *node) Part of BuildDebugTree
 **************************************************************************************************/
std::string DebugNodes::getNodeProperty( Node *node )
{
    std::stringstream ss;
    std::string tag = StringUtils::format("%d" , node->getTag() );
    std::string nodeName =  node->getName().data();
    if(nodeName.empty()) {
        ss << "──═ " << getNodeTypeByName(node) << " Tag:" << tag << " Name:NULL";
        } else {
        ss << "──═ " << getNodeTypeByName(node) << " Tag:" << tag << " Name: " << nodeName;
    }
    Node* parent = node->getParent();
    Point position = parent?parent->convertToWorldSpace( node->getPosition() ):node->getPosition();
    ss << " Position( X:" << position.x << ",Y:" << position.y << " )  Visible( " << ( node->isVisible()?"True":"False" ) << " )  Size( W=" << node->getBoundingBox().size.width << " , H=" << node->getBoundingBox().size.height << " ) Scale( X:" << node->getScaleX() <<" Y:" << node->getScaleY() << ")" ;
    return ss.str();
}


/**************************************************************************************************
 * getNodePosition(Node* node, int setPosition) Part of BuildDebugTree
 **************************************************************************************************/
std::string DebugNodes::getNodePosition( Node* node, int setPosition )
{
    std::string string = "  ├";
    node = node->getParent();
    for ( int i=1; i < setPosition; i++ ) {
        string = std::string(isLastChild(node)?"  │":"  │")  + string;
        node = node->getParent();
    }
    return string;
}


/*************************************************************************************************
** DebugNode                                                                                    **
**************************************************************************************************
** @param DebugNode( Node* yourNode )                                                           **
**************************************************************************************************
** Builds a text tree and print it to string; Shows the node Order in engine for tracing        **
** Used For Debug of your nodes prints out to COCOS_CREATE_DEBUG_DIALOG()  Frame                **
*************************************************************************************************/
void DebugNodes::DebugNode( Node* node )
{

    std::string timeStamp;
    time_t now = time(0);
    std::string mytime = ctime(&now);
    timeStamp =  "\nLog Time: " + mytime +"\n";

    if(node->getName().empty()) {
        timeStamp += "  Root Node Name:NULL";
    } else {
        timeStamp += StringUtils::format( "  Root Node Name: %s " , node->getName().data() );
    }


    DataTree.push_back(timeStamp);

    BuildDebugTree( output, node , 1);

    for(auto &tree : DataTree) {
        AXLOG( "%s",tree.c_str());
    }

}
