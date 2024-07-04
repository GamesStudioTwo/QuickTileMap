//
// Created by Admin on 19/06/2024.
//

#include "SmartNode.h"

/**************************************************************************************************
 * getChild()                                                                                     *
 **************************************************************************************************
 * Returns first child of node                                                                    *
  *************************************************************************************************
 * @return SmartNode                                                                              *
 *************************************************************************************************/
SmartNode* SmartNode::getChild( void ) {
    if ( children.size() > 0  ) {
        return children[0];
    }
    return nullptr; // Out of bounds
}


/**************************************************************************************************
 * getChildAtIndex()                                                                              *
 **************************************************************************************************
 * Returns a child selected child in the index of children                                        *
  *************************************************************************************************
 * @return SmartNode                                                                              *
 *************************************************************************************************/
SmartNode* SmartNode::getChildAtIndex(size_t index) {
    if (index < children.size()) {
        return children[index];
    }
    return nullptr; // Out of bounds
}


/**************************************************************************************************
 * getChildByName()                                                                               *
 **************************************************************************************************
 * Returns a child node use getChildByName("name",false);  the node your on                       *
 *                           getChildByName("name",true);  for recursion search.                  *
 **************************************************************************************************
 * @return SmartNode                                                                              *
 *************************************************************************************************/
SmartNode* SmartNode::getChildByName( const std::string& nodeName, bool searchNodes  ) {

    if(searchNodes == 0 ) {
        for (SmartNode *child: children) {
            if (child->name == nodeName) {
                return child;
            }
        }
       // AXLOG("Not found getChildByName(\"Name\",1) for recursion search.");
    } else {
        if (this->name == nodeName) {
            return this; // Found the node with the specified name
        }

        for (SmartNode* child : children) {
            SmartNode* foundChild = child->getChildByName(nodeName,1);
            if (foundChild) {
                return foundChild; // Recurse into child nodes
            }
        }
    }
    return nullptr; // Not found
}


/**************************************************************************************************
 * getChildByTag()                                                                                *
 **************************************************************************************************
 * Returns a child node use getChildByName(1,false);  the node your on                            *
 *                           getChildByName(1,true);  for recursion search.                       *
 **************************************************************************************************
 * @return SmartNode                                                                              *
 *************************************************************************************************/
SmartNode* SmartNode::getChildById(int tag, bool searchNodes) {
    if( searchNodes == 0 ) {
        for (SmartNode *child: children) {
            if (child->tag == tag) {
                return child;
            }
        }
    } else {

        if ( this->tag == tag ) {
            return this; // Found the node with the specified name
        }

        for ( SmartNode* child : children ) {
            SmartNode* foundChild = child->getChildById( tag , true );
            if (foundChild) {
                return foundChild; // Recurse into child nodes
            }
        }
    }
    return nullptr; // Not found
}


/**************************************************************************************************
 * addChild()                                                                                     *
 **************************************************************************************************
 * adds a chiled to a node, Manual memory managed node                                            *
 * SmartNode* = new SmartNode("Hello");                                                           *
 **************************************************************************************************
 * @return SmartNode                                                                              *
 *************************************************************************************************/
SmartNode* SmartNode::addChild( SmartNode* child ) {
    children.push_back(child); // Add the child to the vector
    child->parentNode = this; // Set the parent node
    return child;
}


/**************************************************************************************************
 * addChild()                                                                                     *
 **************************************************************************************************
 * adds a chiled to a node, auto Create                                                           *
 * yourNode -> addChild("Hello",1);                                                               *
 **************************************************************************************************
 * @return SmartNode                                                                              *
 *************************************************************************************************/
SmartNode* SmartNode::addChild(const std::string& childName, int childTag) {
    SmartNode* child = new SmartNode(childTag, childName);
    children.push_back(child); // Add the child to the vector
    child->parentNode = this; // Set the parent node
    return child; // Return the newly created child
}


/**************************************************************************************************
 * removeChildByName()                                                                            *
 **************************************************************************************************
 * removes a chiled from a node, auto free memory                                                 *
 * yourNode -> removeChildByName("Hello");                                                        *
 **************************************************************************************************
 * @return void                                                                                   *
 *************************************************************************************************/
void SmartNode::removeChildByName(const std::string& childName) {
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i]->name == childName) {
            delete children[i]; // Delete the child node
            children.erase(children.begin() + i); // Remove it from the vector
            break; // Exit the loop once we find the child
        }
    }
}


/**************************************************************************************************
 * removeChild()                                                                                  *
 **************************************************************************************************
 * removes a chiled node, auto free memory                                                        *
 * yourNode -> removeChild(yourNode);                                                             *
 **************************************************************************************************
 * @return bool                                                                                   *
 *************************************************************************************************/
bool SmartNode::removeChild( SmartNode* child ) {
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        children.erase(it);   // Remove the child
        child->parentNode = nullptr; // Update the child's parent reference
        return true;
    }
    return false;
}


/**************************************************************************************************
 * removeFromParent()                                                                             *
 **************************************************************************************************
 * removes a chiled node from parent, auto free memory                                            *
 * yourNode -> removeFromParent(yourNode);                                                        *
 **************************************************************************************************
 * @return bool                                                                                   *
 *************************************************************************************************/
bool SmartNode::removeFromParent(void) {
    if (parentNode) {
        parentNode->removeChild(this); // Assuming you have a removeChild function
        parentNode = nullptr;               // Clear the parent reference
        return true;
    }
    return false;
}


/**************************************************************************************************
 * removeAllChildren()                                                                            *
 **************************************************************************************************
 * removes all chiled nodes, auto free memory                                                     *
 * yourNode -> removeAllChild(yourNode);                                                          *
 **************************************************************************************************
 * @return bool                                                                                   *
 *************************************************************************************************/
void SmartNode::removeAllChildren( void ) {
    for (SmartNode* child : children) {
        delete child; // Clean up memory
    }
    children.clear();
}

/*************************************************************************************************
* removeAllChildByName()                                                                         *
* ************************************************************************************************
* removes all child by Name                                                                      *
* @return void                                                                                   *
**************************************************************************************************/
void SmartNode::removeAllChildrenByName(const std::string& name) {
    for (auto it = children.begin(); it != children.end(); ) {
        if ((*it)->getName() == name) {
            (*it)->removeAllChildren(); // Recursively remove all descendants
            delete *it; // Delete the child itself
            it = children.erase(it); // Remove the child from the vector and get the new iterator
        } else {
            ++it;
        }
    }
}

/*************************************************************************************************
* getAllChildrenByTag()                                                                           *
* ************************************************************************************************
* gets all child by same name node Non Recursive                                                 *
* @return std::vector<SmartNode*>                                                              *
**************************************************************************************************/
std::vector<SmartNode*>SmartNode::getAllChildrenByTag( int id ) {
    std::vector<SmartNode*> matchingChildren;
    for (auto& child : children) {
        if (child->tag == id) {
            matchingChildren.push_back(child);
        }
    }
    return matchingChildren;
}

/*************************************************************************************************
* removeAllChildByNode()                                                                         *
* ************************************************************************************************
* removes all child by Node                                                                      *
* @return void                                                                                   *
**************************************************************************************************/
void SmartNode::removeAllChildrenByNode(SmartNode* node) {
    children.erase(std::remove(children.begin(), children.end(), node), children.end());
    node->removeAllChildren(); // Recursively remove all descendants
    delete node; // Delete the node itself
}


/*************************************************************************************************
* getPathToNode()                                                                                *
* ************************************************************************************************
* get the path to a node                                                                         *
* @return std::vector<std::string>                                                               *
**************************************************************************************************/
/**
std::vector<std::string> SmartNode::getPathToNode(SmartNode* node) {
    std::vector<std::string> path;
    SmartNode* current = node;
    while (current != nullptr) {
        path.insert(path.begin(), current->getName()); // Insert at the beginning to reverse the order
        current = current->getParent(); // Move up to the parent
    }
    return path; // The path is from root to the given node
} **/


std::vector<std::string> SmartNode::getPathToNode(SmartNode* node) {
    std::vector<std::string> path;
    SmartNode* current = node;
    while (current != nullptr) {
        path.insert(path.begin(), current->getName()); // Insert at the beginning to reverse the order
        current = current->getParent(); // Move up to the parent
    }
    return path; // The path is from root to the given node
}


/*************************************************************************************************
* getPathToNodeAsString()                                                                        *
* ************************************************************************************************
* get the path to a node                                                                         *
* @return std::vector<std::string>                                                               *
**************************************************************************************************/
std::string SmartNode::getPathToNodeAsString(SmartNode* node) {
    std::string path;
    SmartNode* current = node;
    while (current != nullptr) {
        path = current->getName() + (path.empty() ? "" : "/" + path); // Prepend name with delimiter
        current = current->getParent(); // Move up to the parent
    }
    return path; // The path is from root to the given node as a string
}

/*************************************************************************************************
* getPathToNodeByName()                                                                          *
* ************************************************************************************************
* get the path to a node by name                                                                 *
* @return SmartNode* SmartNode                                                               *
**************************************************************************************************/
SmartNode* SmartNode::getPathToNodeByName(SmartNode* root, const std::string& name) {
    if (root == nullptr) return nullptr; // Base case: root is null
    if (root->getName() == name) return root; // Base case: name matches

    // Recursive case: search in children
    for (auto& child : root->children) {
        SmartNode* result = getPathToNodeByName(child, name );
        if (result != nullptr) {
            return result; // Found the node
        }
    }
    return nullptr; // Node not found
}


/*************************************************************************************************
* getPathToNodeByName()                                                                          *
* ************************************************************************************************
* get the path to a node by name                                                                 *
* @return SmartNode* SmartNode                                                                   *
**************************************************************************************************/
SmartNode* SmartNode::getPathToNodeByName( const std::string& name ) {

    SmartNode* root = getRootNode();

    if (root == nullptr) return nullptr; // Base case: root is null
    if (root->getName() == name) return root; // Base case: name matches

    // Recursive case: search in children
    for (auto& child : root->children) {
        SmartNode* result = getPathToNodeByName(child, name );
        if (result != nullptr) {
            return result; // Found the node
        }
    }
    return nullptr; // Node not found
}

/**************************************************************************************************
* getPathToNodeByName()                                                                          *
* ************************************************************************************************
* get the path to a node by name                                                                 *
* @return SmartNode* SmartNode                                                                   *
**************************************************************************************************/
std::vector<SmartNode*> SmartNode::getPathToNodeSearch(const std::string& nodeName) {
    std::vector<SmartNode*> found;
    SmartNode* path = getChildByName(nodeName, 1); // Assuming getChildByName exists

    while (path != nullptr) {
        found.insert(found.begin(), path); // Insert at the beginning to reverse the order
        path = path->getParent(); // Move up to the parent
    }

    return found;
}
/*************************************************************************************************
* searchByName()                                                                                 *
* ************************************************************************************************
* get the path to a node by name                                                                 *
* @return SmartNode* pointers to all nodes named “desiredName”.                                *
* auto results = rootNode->searchByName("desiredName");                                          *
**************************************************************************************************/
std::vector<SmartNode*> SmartNode::searchByName(const std::string& searchName) {
    std::vector<SmartNode*> results;
    std::function<void(SmartNode*)> searchRecursive = [&](SmartNode* node) {
        if (node->getName() == searchName) {
            results.push_back(node);
        }
        for (auto& child : node->children) {
            searchRecursive(child);
        }
    };
    searchRecursive(this); // Start the search from this node
    return results;
}


/*************************************************************************************************
* clone()                                                                                        *
**************************************************************************************************
*  Deep copy (clone) functionality                                                               *
*  @return SmartNode*                                                                          *
**************************************************************************************************/
SmartNode* SmartNode::clone() const {
    SmartNode* newNode = new SmartNode(*this); // Copy the current node
    newNode->children.clear(); // Clear the copied children vector

    for (auto& child : children) {
        SmartNode* childClone = child->clone(); // Clone the child
        childClone->parentNode = newNode; // Set the parent of the cloned child
        newNode->children.push_back(childClone); // Add the cloned child to the new node's children vector
    }

    return newNode;
}

/**************************************************************************************************
 * getChildren()                                                                                  *
 **************************************************************************************************
 * Returns a vector of SmartNode* to all children                                                 *
 **************************************************************************************************
 * @return vector<SmartNode*>                                                                     *
 *************************************************************************************************/
std::vector<SmartNode*> SmartNode::getChildren( void ) {
    std::vector<SmartNode*> result;
    for (SmartNode* child : children) {
            result.push_back(child);
    }
    return result;
}


/**************************************************************************************************
 * getAllChildrenByName()                                                                         *
 **************************************************************************************************
 * Returns a vector of SmartNode* Matching children names                                         *
 **************************************************************************************************
 * @return vector<SmartNode*>                                                                     *
 *************************************************************************************************/
std::vector<SmartNode*> SmartNode::getAllChildrenByName( const std::string& name ,bool searchNodes )
{
    std::vector<SmartNode*> result;
    if( !searchNodes ) {
        for (SmartNode* child : children) {
            if (child->name == name) {
                result.push_back(child);
            }
        }
        return result;
    }

    else {
        if (this->name == name) {
           result.push_back(this);
        }
       // Recursively search children
       for (SmartNode *child: children) {
         std::vector<SmartNode *> childResult = child->getAllChildrenByName(name, searchNodes);
          result.insert(result.end(), childResult.begin(), childResult.end());
          }
     }
    return result;
}


/*************************************************************************************************
* getVectorOfChildrenByName()                                                                    *
* ************************************************************************************************
* Gets more the one name                                                                         *
* Usage getVectorOfChildrenByName(  { "name1","Name2","Name3" }  );                              *
* Must have curly brace's or pass a std::vector                                                  *
* @return bool                                                                                   *
**************************************************************************************************/
std::vector<SmartNode*> SmartNode::getVectorOfChildrenByName(const std::vector<std::string>& names , bool reverseOrder ) {
    std::vector<SmartNode*> result;
    for (SmartNode* child : children) {
        for (const auto& name : names) {
            if (child->name == name) {
                result.push_back(child);
            }
        }
    }

    if( reverseOrder ) {
        std::reverse(result.begin(), result.end());
    }

    return result;
}



/**************************************************************************************************
 * getParent()                                                                                    *
 **************************************************************************************************
 * Returns a parent of the node                                                                   *
 **************************************************************************************************
 * @return SmartNode*                                                                             *
 *************************************************************************************************/
SmartNode* SmartNode::getParent( void ) {
    return parentNode;
}


/**************************************************************************************************
 * getNext()                                                                                      *
 **************************************************************************************************
 * Returns the next of the node                                                                   *
 **************************************************************************************************
 * @return SmartNode*                                                                             *
 *************************************************************************************************/
SmartNode* SmartNode::getNext( void ) {
    if ( children.empty() ) {
        return nullptr; // No children
    }
    return children[0];
}


/**************************************************************************************************
 * getChildrenSize()                                                                              *
 **************************************************************************************************
 * Returns the count children of the node                                                         *
 **************************************************************************************************
 * @return size_t                                                                                 *
 *************************************************************************************************/
size_t SmartNode::getChildrenSize( void ) const {
    return children.size();
}


/**************************************************************************************************
 * getRootNode()                                                                                  *
 **************************************************************************************************
 * Returns the root of node                                                                       *
 **************************************************************************************************
 * @return SmartNode*                                                                             *
 *************************************************************************************************/
SmartNode* SmartNode::getRootNode( void ) {
    SmartNode* currentNode = this;
    while ( currentNode->parentNode ) {
        currentNode = currentNode->parentNode;
    }
    return currentNode;
}




/**************************************************************************************************
 * getTag()                                                                                       *
 **************************************************************************************************
 * Returns the TAG number of node                                                                 *
 **************************************************************************************************
 * @return int                                                                                    *
 *************************************************************************************************/
int SmartNode::getTag(void) const
{
    return tag;
}


/**************************************************************************************************
 * setTag()                                                                                       *
 **************************************************************************************************
 * Sets the TAG number of node                                                                    *
 **************************************************************************************************
 * @return int                                                                                    *
 *************************************************************************************************/
void SmartNode::setTag(int tagNumber) {
    tag = tagNumber;
}


/**************************************************************************************************
 * setName()                                                                                      *
 **************************************************************************************************
 * Sets the Name of the node                                                                      *
 **************************************************************************************************
 * @return void                                                                                   *
 *************************************************************************************************/
void SmartNode::setName(const std::string& nodeName) {
    name = nodeName;
}


/**************************************************************************************************
 * getName()                                                                                      *
 **************************************************************************************************
 * Returns the Name of the node                                                                   *
 **************************************************************************************************
 * @return std::string                                                                            *
 *************************************************************************************************/
std::string SmartNode::getName( void ) const   {
    return name;
}



/**************************************************************************************************
 * ShowNodes()                                                                                    *
 **************************************************************************************************
 * prints to console                                                                              *
 **************************************************************************************************
 * @return void                                                                                   *
 *************************************************************************************************/
void SmartNode::ShowNodes() const {
    AXLOG("Tag: %d, Name: %s\n", tag, name.c_str());
}


/**************************************************************************************************
 * ShowAllNode()                                                                                  *
 **************************************************************************************************
 * Shows all the node                                                                             *
 **************************************************************************************************
 * @return void                                                                                   *
 *************************************************************************************************/
void SmartNode::ShowAllNode() const {
    ShowNodes(); // Display information about the current node
    for (SmartNode* child : children) {
        child->ShowAllNode(); // Recursively display child nodes
    }
}


/**************************************************************************************************
 * showChildren()                                                                                 *
 **************************************************************************************************
 * Shows all children node's                                                                      *
 **************************************************************************************************
 * @return void                                                                                   *
 *************************************************************************************************/
void SmartNode::ShowAllChildren() const {
    AXLOG("************** Node Children **************");
    for (SmartNode* child : children) {
        child->ShowNodes(); // Display information about each child
    }
}

/**************************************************************************************************
 * startsWithSlash()                                                                              *
 **************************************************************************************************
 * Helper function to check if a child's name starts with '/'                                     *
 **************************************************************************************************
 * @return bool                                                                                   *
 *************************************************************************************************/
bool SmartNode::startsWithSlash(SmartNode* child) {
    if( child->name[0] == '/' && child->name[1] == 'p' && child->name[0] == 'r' ) {
        delete child;
    }
    return child->name.front() == '/';
}


/**************************************************************************************************
 * cleanUpNodes()                                                                                 *
 **************************************************************************************************
 * Recursively remove children starting with '/'                                                  *
 * Removes all the nodes that start  </animation>, </tile>, </tileset>, </tile>, </tileset>, etc  *
 * to speeds up searching less data to find and saves memory                                      *
 **************************************************************************************************
 * @return void                                                                                   *
 *************************************************************************************************/
void  SmartNode::cleanUpNodes(void) {
    // Remove children at this level
    children.erase(std::remove_if(children.begin(), children.end(), startsWithSlash), children.end());
    // Recursively remove children from child nodes
    for (SmartNode* child : children) {
        child->cleanUpNodes(); // Recursive call
    }
}


/**************************************************************************************************/
/************************************* Storage Functions ******************************************/
/**************************************************************************************************/


/*************************************************************************************************
* KeyExist()                                                                                     *
* ************************************************************************************************
*  checks the storage if key exsit                                                               *
*  @return bool                                                                                  *
**************************************************************************************************/
bool SmartNode::keyExist( const std::string& key )
{
    if( storage.count(key ) > 0 ) {
        return true;
    }
    return false;
}

/*************************************************************************************************
* addToStorage()                                                                                 *
* ************************************************************************************************
* Adds Data to the map Storage                                                                   *
* @return bool                                                                                   *
**************************************************************************************************/
bool SmartNode::addToStorage( const std::string& key, const std::string& value ) {

    if( key.empty() ) {
        return 0;
    }

    if( keyExist( key ) ) {
        return 0;
    }

    storage[key] = value;
    return 1;
}

/*************************************************************************************************
* setStorageData()                                                                               *
* ************************************************************************************************
* same ad addToStorage but overwrites data no checking                                           *
* @return int                                                                                    *
**************************************************************************************************/
int SmartNode::setStorageData( const std::string& key , const std::string& value )
{
    storage[ key ] =  value;
    return storage.size();
}



/*************************************************************************************************
* removeFromStorage()                                                                            *
* ************************************************************************************************
* removes Data to the map Storage function                                                       *
* @return void                                                                                   *
**************************************************************************************************/
void SmartNode::removeFromStorage(const std::string& key) {
    if ( keyExist( key ) ) {
        storage.erase(key);
        }
}

/*************************************************************************************************
* getFromStorage()                                                                               *
* ************************************************************************************************
* gets the Data to the Storage map                                                               *
* @return string                                                                                 *
**************************************************************************************************/

std::string SmartNode::getFromStorage(const std::string& key) const {
    auto it = storage.find(key);
    if (it != storage.end()) {
        return it->second;
    }
    return ""; // or throw an exception
}

/*************************************************************************************************
* showStorageData()                                                                              *
* ************************************************************************************************
* Function to show all storage data  print to console                                            *
* @return void                                                                                   *
**************************************************************************************************/

void SmartNode::ShowAllStorage( void ) const {
    AXLOG("************ Node Storage Data ************");
    for (const auto& pair : storage) {
        AXLOG("Storage Data for Node: %s : %s", pair.first.c_str(), pair.second.c_str() );
    }
}

/*************************************************************************************************
* GetKeyAsString()                                                                               *
* ************************************************************************************************
* returns data as string                                                                         *
* @return sting                                                                                  *
**************************************************************************************************/
std::string SmartNode::getKeyAsString( const std::string& key )
{
    if ( storage.count(key ) > 0 ) {
        return storage[key];
    }
    return "";
}


/*************************************************************************************************
* getKeyAsChar()                                                                                 *
* ************************************************************************************************
* returns data as raw char *                                                                     *
* @return char*                                                                                  *
**************************************************************************************************/
char * SmartNode::getKeyAsChar( const std::string& key )
{
    if ( storage.count(key ) > 0 ) {
        return (char*)storage[key].c_str();
    }
    return NULL;
}


/*************************************************************************************************
* getKeyAsFloat()                                                                                *
* ************************************************************************************************
* returns data as float                                                                          *
* @return float                                                                                  *
**************************************************************************************************/
float SmartNode::getKeyAsFloat( const std::string& key )
{
    if( storage.count(key ) > 0 ) {
        return std::atof(storage[key].c_str() );
    }
    return 0.0f;
}

/*************************************************************************************************
* getKeyAsInt()                                                                                  *
* ************************************************************************************************
* returns data as float                                                                          *
* @return int                                                                                    *
**************************************************************************************************/
int SmartNode::getKeyAsInt( const std::string& key )
{
    if( storage.count(key ) > 0 ) {
        return std::atoi(storage[ key ].c_str() );
    }
    return 0;
}

/*************************************************************************************************
* getKeyAsLong()                                                                                 *
* ************************************************************************************************
* returns data as long                                                                           *
* @return long                                                                                   *
**************************************************************************************************/
long SmartNode::getKeyAsLong( const std::string& key )
{
    if( storage.count(key ) > 0 ) {
        return std::atol(storage[ key ].c_str() );
    }
    return 0.0f;
}


bool SmartNode::getKeyAsBool( const std::string& key ) {
    if( storage.count(key ) > 0 ) {
        return std::atoi(storage[ key ].c_str() );
    }
    return false;
}

/*************************************************************************************************
* findKeyFromStorage()                                                                           *
* ************************************************************************************************
* finds if the key Exist in the storage                                                          *
* @return bool                                                                                   *
**************************************************************************************************/
bool SmartNode::findKeyFromStorage( const std::string& key )
{
    if( storage.find(key ) != storage.end() ) {
        return 1;
    }
    return 0;
}


/*************************************************************************************************
* deleteKeyFromStorage()                                                                         *
* ************************************************************************************************
* Deletes a key in the storage                                                                   *
* @return bool                                                                                   *
**************************************************************************************************/
bool SmartNode::deleteKeyFromStorage( const std::string& key ) {
    bool exist = storage.erase(key);
    return exist;
}





