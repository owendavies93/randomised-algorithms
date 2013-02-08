#include "RBST.hpp"
#include <stdlib.h>
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

int RBST::add(const Key& key, bool verbose) {
    unsigned int oldSize = m_size;
    m_head = randomAdd(m_head, key);
    if (m_size > oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is added into the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is already in the tree."<<endl;
        }
        return 0;
    }
    if (verbose) cout<<endl;
};

int RBST::del(const Key& key, bool verbose) {
    unsigned oldSize= m_size;
    m_head = del(m_head, key);
    if (m_size < oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is deleted from the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    }
};

int RBST::find(const Key& key, bool verbose) {
    RBSTNode* ret = find(m_head, key);
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is in the tree."<<endl;
        }
        return 1;
    }
};

int RBST::dump(char sep) {
    int ret = dump(m_head, sep);
    cout<<"SIZE: " <<ret<<endl;
    return ret;
};

int RBST::dump(RBSTNode* target, char sep) {
    if (target == NULL) {
        return 0;
    }
    int ret = dump(target->left(), sep);
    cout<< *target<<sep;
    ret ++;
    ret += dump(target->right(), sep);
    return ret;
};



/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/


/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

RBSTNode*  RBST::rightRotate(RBSTNode* target) {
    RBSTNode* l = target->left();

    target->setLeft(l->right());
    l->setRight(target);

    return l;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
    RBSTNode* r = target->right();

    target->setRight(r->left());
    r->setLeft(target);

    return r;
};

RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
    countAdd++;

    if (target == NULL) {
        return new RBSTNode(key);
    }

    if (key < target->getKey()) {
        target->setLeft(addRoot(target->left(), key));
        return rightRotate(target);
    } else {
        target->setRight(addRoot(target->right(), key));
        return leftRotate(target);
    }
};


RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;

    if (target == NULL) {
        m_size++;
        return new RBSTNode(key);
    }

    int randomIndex = (rand() % m_size) + 1;

    if (randomIndex == 1) {
        m_size++;
        return addRoot(target, key);
    }

    if (key < target->getKey()) {
        target->setLeft(randomAdd(target->left(), key));
    } else {
        target->setRight(randomAdd(target->right(), key));
    }

    m_size++;

    return target;
};


/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
    countFind++;

    if (target == NULL) {
        return NULL;
    } else if (target->getKey() == key) {
        return target;
    } else if (key < target->getKey()) {
        return find(target->left(), key);
    } else {
        return find(target->right(), key);
    }
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
    countDelete++;

    if (target == NULL) {
        return NULL;
    }

    if (target->getKey() == key) {
        if (target->left() == NULL && target->right() == NULL) {
            return NULL;
        } else if (target->left() == NULL) {
            return target->right();
        } else if (target->right() == NULL) {
            return target->left();
        } else {
            RBSTNode* smallest = smallestChild(target->right());

            target->setKey(smallest->getKey());

            target->setRight(del(target->right(), smallest->getKey()));
        }
    }

    if (key < target->getKey()) {
        return target->setLeft(del(target->left(), key));
    } else {
        return target->setRight(del(target->right(), key));
    }
};

RBSTNode* RBST::smallestChild(RBSTNode* target) {
    if (target->left() == NULL) {
        return target;
    } else {
        return smallestChild(target->left());
    }
}
