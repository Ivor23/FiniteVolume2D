#include "MeshBuilder.h"

#include "NodeManager.h"
#include "FaceManager.h"
#include "Node.h"
#include "Face.h"
#include "EntityCreatorManager.h"
#include "Util.h"

#include <boost/foreach.hpp>
#include <boost/format.hpp>

#include <iostream>


MeshBuilder::MeshBuilder(EntityCreatorManager::Ptr & entity_mgr) : entity_mgr_(entity_mgr), mesh_(Mesh::create()) {}

bool
MeshBuilder::buildNode(IGeometricEntity::Id_t mesh_id, IGeometricEntity::Entity_t entity_type, double x, double y)
{
    NodeManager::Ptr & node_mgr = entity_mgr_->getNodeManager();
    Node::Ptr v = node_mgr->createNode(mesh_id, entity_type, x, y);
    if (v == NULL)
        return false;
    mesh_->addNode(v);
    return true;
}

bool
MeshBuilder::buildFace(IGeometricEntity::Id_t mesh_id, IGeometricEntity::Entity_t entity_type, std::vector<IGeometricEntity::Id_t> const & node_ids)
{
    if (node_ids.size() != 2) {
        boost::format format = boost::format("MeshBuilder::buildFace: Face %1% must have 2 vertices!\n") % mesh_id;
        Util::error(format.str());
        return false;
    }

    NodeManager::Ptr & node_mgr = entity_mgr_->getNodeManager();

    EntityCollection<Node> nodes;

    BOOST_FOREACH (IGeometricEntity::Id_t node_id, node_ids) {
        Node::Ptr & v = node_mgr->getEntity(node_id);
        nodes.insert(v);
    }

    FaceManager::Ptr & face_mgr = entity_mgr_->getFaceManager();
    Face::Ptr f = face_mgr->createFace(mesh_id, entity_type, nodes);
    if (f == NULL)
        return false;
    mesh_->addFace(f);
    return true;
}

bool
MeshBuilder::buildCell(IGeometricEntity::Id_t mesh_id, std::vector<IGeometricEntity::Id_t> const & face_ids) {
    FaceManager::Ptr & face_mgr = entity_mgr_->getFaceManager();

    EntityCollection<Face> faces;

    BOOST_FOREACH (IGeometricEntity::Id_t face_id, face_ids) {
        Face::Ptr & f = face_mgr->getEntity(face_id);
        faces.insert(f);
    }

    CellManager::Ptr & cell_mgr = entity_mgr_->getCellManager();
    Cell::Ptr c = cell_mgr->createCell(mesh_id, faces);
    if (c == NULL)
        return false;
    mesh_->addCell(c);
    return true;
}

void
MeshBuilder::outputReport(std::ostream & target) const {
    Mesh::CPtr cmesh(mesh_);

    auto nboundary_nodes = cmesh->getNodeThread(IGeometricEntity::BOUNDARY).size();
    auto ninterior_nodes = cmesh->getNodeThread(IGeometricEntity::INTERIOR).size();

    auto nboundary_faces = cmesh->getFaceThread(IGeometricEntity::BOUNDARY).size();
    auto ninterior_faces = cmesh->getFaceThread(IGeometricEntity::INTERIOR).size();

    auto ncells = cmesh->getCellThread().size();


    target << nboundary_nodes << " boundary nodes" << std::endl;
    target << ninterior_nodes << " interior nodes" << std::endl;
    target << nboundary_faces << " boundary faces" << std::endl;
    target << ninterior_faces << " interior faces" << std::endl;
    target << ncells << " cells read." << std::endl;
}

boost::optional<Mesh::Ptr>
MeshBuilder::getMesh() const {
    return mesh_;
}
