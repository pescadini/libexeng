/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include <cassert>
#include <vector>
#include <stdexcept>
#include <boost/checked_delete.hpp>

#include <exeng/scenegraph/SceneNode.hpp>

using namespace exeng;
using namespace exeng::math;
using namespace exeng::scenegraph;

namespace exeng { namespace scenegraph {

//! SceneNode private data
struct SceneNode::Private {
    std::string name;               //! Node name
    Matrix4f transform;             //! Node transformation
    SceneNode* parentPtr;           //! 
    SceneNodeVector childVector;    //! Node childs
    SceneNodeData *data;            //! Private data
            
    Private() {   
        this->data = nullptr;
        this->parentPtr = nullptr;
        this->transform.identity();
    }
            
    ~Private()  {
	}
            
    /**
        * @brief Busca el nodo hijo con el nombre indicado, y devuelve un iterador.
        * En caso de que no exista, se devuelve el fin de la secuencia
        * @param name
        * @return 
        */
    SceneNodeVectorIt getChild(const std::string &name) {
		/*
        SceneNode *child = nullptr; 
		*/

		auto &childs = this->childVector;
        
		return std::find_if(std::begin(childs), std::end(childs), [&name](SceneNode *node) {
			return node->impl->name == name;
		});

		/*
        for (auto it=std::begin(childs); it!=std::end(childs); ++it) {
            child = *it;
                    
            if ( child->impl->name == name ) {
                return it;
            }
        }
        
        // No encontrado
        return childs.end();
		*/
    }
};
}
}

namespace exeng {
namespace scenegraph {
SceneNode::SceneNode() {
    this->impl = new SceneNode::Private();
}


SceneNode::SceneNode(const std::string &name) {
    this->impl = new SceneNode::Private();

    // Pueden existir nodos hermanos que tengan, potencialmente, 
    // el mismo nombre, asi que es preferible llamar al metodo.
    this->setName(name);
}


SceneNode::~SceneNode() {
    this->orphan();
    boost::checked_delete(this->impl);
}


std::string SceneNode::toString() const {
    assert(this->impl != nullptr);

    if (this->hasParent() == false) {
        return "";
    } else {
        return this->getParentPtr()->toString() + "\\" + this->getName();
    }
}


Matrix4f SceneNode::getTransform() const {
    assert(this->impl != NULL);
    return this->impl->transform;
}


void SceneNode::setTransform(const math::Matrix4f& transform) {
    assert(this->impl != NULL);
    this->impl->transform = transform;
}


std::string SceneNode::getName() const {
    assert(this->impl != NULL);

    // Devuelve el nombre por valor 
    return this->impl->name;
}


void SceneNode::setName(const std::string &name) {
    assert(this->impl != NULL);

    if (this->hasParent() == true) {
        if (this->getParentPtr()->existChild(name) == true) {
            throw std::logic_error("Ya existe un nodo hermano con ese nombre.");
        }
    }
            
    this->impl->name = name;
}


int SceneNode::getChildCount() const {
    assert(this->impl != NULL);
    return static_cast<int>(this->impl->childVector.size());
}


SceneNode* SceneNode::getChildPtr(int index) const {
    assert(this->impl != NULL);
    return this->impl->childVector[index];
}


SceneNode* SceneNode::getChildPtr(const std::string& name) {
    assert(this->impl != NULL);

    SceneNode *childPtr = NULL;

    childPtr = *this->impl->getChild(name);

    // Como no existe el nodo hijo, instanciamos uno y devolvemos su referencia
    if (childPtr == nullptr) {
        childPtr = this->addChildPtr(name);
    }

    return childPtr;
}


SceneNode* SceneNode::getChildPtr(const std::string& name) const {
    assert(this->impl != NULL);

    SceneNode *childPtr = NULL;
            
    childPtr = *this->impl->getChild(name);

    if (childPtr == NULL) {
        // Lanzar una excpecion, ya que no podemos modificar al grafo de escena 
        // si este es constante
        std::string msg;

        msg += "El nodo con el nombre '";
        msg += name;
        msg += "' no fue encontrado.";

        throw std::logic_error(msg);
    }

    return childPtr;
}


SceneNode* SceneNode::getParentPtr() const {
    assert(this->impl != NULL);

    if (this->hasParent() == false) {
        std::string msg;

        msg += "El nodo " + this->toString();
        msg += " no posee nodo padre.";

        throw std::logic_error(msg);
    }

    return this->impl->parentPtr;
}


void SceneNode::setParentPtr(SceneNode* parent) {
    assert(this->impl != NULL);

    // Para cambiar el padre, es necesario primero desvincular al nodo 
    // de su padre previo (si lo tiene)
    if (this->hasParent() == true) {
        this->getParentPtr()->removeChildPtr(this);
    }

    // Ahora, agregamos el nuevo nodo al padre
    parent->addChildPtr(this);
}


bool SceneNode::hasParent() const {
    assert(this->impl != NULL);
    return this->impl->parentPtr != NULL;
}


bool SceneNode::existChild(const std::string &name) const {
    assert(this->impl != NULL);

    // Si el nodo hijo con el nombre indicado existe, entonces devolvemos true
    return *this->impl->getChild(name) != NULL;
}


SceneNode* SceneNode::addChildPtr(SceneNode *childPtr) {
    assert(this->impl != NULL);

    // Debemos considerar que este metodo debe modificar los padres directamente, 
    // ya que en la implementacion actual, otros metodos relacionados con la modificacion
    // de la jerarquia del grafo de escena son depedientes de este.
    if (childPtr->hasParent() == true) {
        // Desvincular al nodo padre 
        childPtr->getParentPtr()->removeChildPtr(childPtr);
    }
            
    childPtr->impl->parentPtr = this;
    this->impl->childVector.push_back(childPtr);

    return childPtr;
}


SceneNode* SceneNode::removeChildPtr(const std::string& name) {
    assert(this->impl != NULL);

    // Implementacion rapida y sucia
    SceneNodeVectorIt it = this->impl->getChild(name);
    SceneNode* child = *it;

    return this->removeChildPtr(child);
}


SceneNode* SceneNode::removeChildPtr(SceneNode* childPtr) {
    assert(this->impl != NULL);

    // Determinar si el padre de este nodo somos nosotros antes de continuar
    if (this->impl->parentPtr == this) {
        // Buscar el iterador correspondiente
        auto &childs = this->impl->childVector;
        auto it = childs.begin();

        for (it=childs.begin(); it!=childs.end(); ++it) {
            if (*it == childPtr) {
                break;
            }
        }

        // Indica en tiempo de ejecucion errores internos
        assert(it != childs.end());
                
        // Sacar el nodo de la lista de los hijos
        this->impl->childVector.erase(it);
        childPtr->impl->parentPtr = NULL;

        return childPtr;
    } else {
        std::string msg;

        msg += "El nodo '" + 
        msg += childPtr->toString();
        msg += "' no pertenece a la jerarquia de ";
        msg += this->toString();

        throw std::logic_error(msg);
    }	
}


SceneNode* SceneNode::addChildPtr(const std::string& name) {
    assert(this->impl != NULL);

    SceneNode* childPtr = new SceneNode(name);
    return this->addChildPtr(childPtr);
}


void SceneNode::orphan() {
    if (this->hasParent() == true) {
        this->getParentPtr()->removeChildPtr(this);
    }
}

        
void SceneNode::setDataPtr(SceneNodeData* data) {
    this->impl->data = data;
}


SceneNodeData* SceneNode::getDataPtr() const {
    return this->impl->data;
}
        
        
const SceneNodeVector& SceneNode::getChilds() const {
    return this->impl->childVector;
}

}}
