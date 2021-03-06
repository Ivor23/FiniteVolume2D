/*
 * Name  : NodeManager
 * Path  : 
 * Use   : Creates and holds all nodes
 * Author: Sven Schmidt
 * Date  : 03/10/2012
 */
#pragma once

#include "DeclSpec.h"

#include "EntityManager.hpp"
#include "Node.h"


#pragma warning(disable:4251)


class DECL_SYMBOLS_2DLIB NodeManager : public EntityManager<Node> {
public:
    typedef std::shared_ptr<NodeManager> Ptr;

public:
    Node::Ptr createNode(IGeometricEntity::Id_t mesh_id, IGeometricEntity::Entity_t entity_type, double x, double y);

    static Ptr create();

private:
    NodeManager();
};

#pragma warning(default:4251)
