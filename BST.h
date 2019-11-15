//José Elías Garza Vázquez - A00824494
//las librerías que uso son:
//stack
//queue
//vector
#include "NodeT.h"

class BST {
  public:
    BST();
    BST(const BST &copy);
    ~BST();

    void add(int data);
    bool search(int data);
    void remove(int data);

    void print(int x);

    int count() const;
    int height() const;
    int whatLevelamI(int data);

    std::vector<int> ancestors(int data);

    int nearestRelative(int n1, int n2);
    bool operator==(const BST& tree);
    std::queue<int> toQueue();
    int maxWidth();


  private:
    NodeT* root;
    int howManyChildren(NodeT* r);
    int pred(NodeT* r);
    int succ(NodeT* r);

    void preOrder(NodeT* r);
    void inOrder(NodeT* r);
    void postOrder(NodeT* r);
    void nivelXNivel(NodeT* r);

    void libera(NodeT* r);
    void printLeaves(NodeT* r);
    int cuenta(NodeT* r) const;
    int heightHelper(NodeT* r) const;
    void copyConstructorHelper(NodeT* r);
    bool isEqualToHelper(NodeT* r1, NodeT* r2, bool b);

    void toQueueHelper(NodeT* r);
    std::stack<int> treeStack;
};

BST::BST() {
  root = NULL;
}

BST::~BST() {
  libera(root);
}

void BST::libera(NodeT* r) {
  if ( r != NULL ) {
    libera(r->getLeft());
    libera(r->getRight());
    delete r;
  }
}

bool BST::search(int data) {
  NodeT* curr = root;
  while( curr != NULL ) {
    if ( curr->getData() == data ) {
      return true;
    }
    curr = ( curr->getData() > data ) ?
        curr->getLeft() : curr->getRight();
    // if ( curr->getData() > data ) {
    //   curr = curr->getLeft();
    // } else {
    //   curr = curr->getRight();
    // }
  }
  return false;
}


void BST::add(int data) {
  NodeT* curr = root;
  NodeT* father = NULL;

  while( curr != NULL ) {
    father = curr;
    curr = ( curr->getData() > data ) ?
        curr->getLeft() : curr->getRight();
  }

  if ( father == NULL ) {
    root = new NodeT(data);
  } else {
    if ( father->getData() > data ) {
      father->setLeft(new NodeT(data));
    } else {
      father->setRight(new NodeT(data));
    }

    // ((father->getData() > data) ? 
    //   father->setLeft(new NodeT(data)) :
    //   father->setRight(new NodeT(data)))
  }
}


void BST::remove(int data) {
  NodeT* curr = root;
  NodeT* father = NULL;

  while( curr != NULL && curr->getData() != data ) {
    father = curr;
    curr = ( curr->getData() > data ) ?
        curr->getLeft() : curr->getRight();
  }
  if ( curr == NULL ) {
    return;
  }
  int c = howManyChildren(curr);
  switch(c) {
    case 0:
      if ( father == NULL ) {
        root = NULL;
      } else {
        if ( father->getData() > data ) {
          father->setLeft(NULL);
        } else {
          father->setRight(NULL);
        }
      }
      delete curr;
      break;
    case 1:
      if ( father == NULL ) {
        if( curr->getLeft() != NULL ) {
          root = curr->getLeft();
        } else {
          root = curr->getRight();
        }
      } else {
        if ( father->getData() > data ) {
          if ( curr->getLeft() != NULL ) {
            father->setLeft(curr->getLeft());
          } else {
            father->setLeft(curr->getRight());
          }
        } else {
          if ( curr->getLeft() != NULL ) {
            father->setRight(curr->getLeft());
          } else {
            father->setRight(curr->getRight());
          }
        }
      }
      delete curr;
      break;
    case 2:
      int x = succ(curr);
      remove(x);
      curr->setData(x);
      break;
  }
}


int BST::howManyChildren(NodeT* r) {
  int cont = 0;
  if ( r->getLeft() != NULL ) {
    cont++;
  }
  if ( r->getRight() != NULL) {
    cont++;
  }
  return cont;
}


int BST::pred(NodeT* r) {
  NodeT* curr = r->getLeft();
  while( curr->getRight() != NULL ) {
    curr = curr->getRight();
  }
  return curr->getData();
}

int BST::succ(NodeT* r) {
  NodeT* curr = r->getRight();
  while( curr->getLeft() != NULL ) {
    curr = curr->getLeft();
  }
  return curr->getData();
}


int BST::count() const {
  return cuenta(root);
}

int BST::cuenta(NodeT* r) const {
  if ( r != NULL ) {
    return 1 + cuenta(r->getLeft()) + cuenta(r->getRight());
  } else {
    return 0;
  }
}


void BST::preOrder(NodeT* r) {
  if ( r != NULL ) {
    std::cout << r->getData() << " ";
    preOrder(r->getLeft());
    preOrder(r->getRight());
  }
}


void BST::inOrder(NodeT* r) {
  if ( r != NULL ) {
    inOrder(r->getLeft());
    std::cout << r->getData() << " ";
    inOrder(r->getRight());
  }
}


void BST::postOrder(NodeT* r) {
  if ( r != NULL ) {
    postOrder(r->getLeft());
    postOrder(r->getRight());
    std::cout << r->getData() << " ";
  } 
}

void BST::printLeaves(NodeT* r) {
  if ( r != NULL ) {
    if ( r->getLeft() == NULL && r->getRight() == NULL ) {
      std::cout << r->getData() << " ";
    } else {
      printLeaves(r->getLeft());
      printLeaves(r->getRight());
    }
  }
}

void BST::print(int x) {
  switch(x) {
    case 1: preOrder(root);
      break;
    case 2: inOrder(root);
      break;
    case 3: postOrder(root);
      break;
    case 4: printLeaves(root);
      break;
    case 5: nivelXNivel(root);
      break;
  }
  std::cout << '\n';
}

int BST::height() const {
  return heightHelper(root);
}

int BST::heightHelper(NodeT* r) const {
  if(r != NULL) {
    
    int leftHeight = heightHelper(r->getLeft());
    int rightHeight = heightHelper(r->getRight());

    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
  }
  return 0;
}

std::vector<int> BST::ancestors(int data) {
  std::vector<int> ancestorsVector;
  std::stack<int> ancestorsStack;

  NodeT* curr = root;

  while(curr->getData() != data) {
    ancestorsStack.push(curr->getData());
    curr = ( curr->getData() > data ) ?
        curr->getLeft() : curr->getRight();
  }
  while(!ancestorsStack.empty()) {
    ancestorsVector.push_back(ancestorsStack.top());
    ancestorsStack.pop();
  }

  return ancestorsVector;
}

int BST::whatLevelamI(int data) {
  NodeT* curr = root;
  int level = 1;

  while(curr != NULL) {
    if(curr->getData() == data) {
      return level;
    }
    level++;
    curr = ( curr->getData() > data ) ?
      curr->getLeft() : curr->getRight();
  }
  return -1;
}

void BST::nivelXNivel(NodeT* r) {
  std::queue<NodeT*> NodeQ;

  NodeQ.push(r);

  while(!NodeQ.empty()) {
    NodeT* curr = NodeQ.front();
    std::cout << curr->getData() << ' ';
    NodeQ.pop();

    if(curr->getLeft() != NULL) {
      NodeQ.push(curr->getLeft());
    }
    if(curr->getRight() != NULL) {
      NodeQ.push(curr->getRight());
    }
  }

}

int BST::maxWidth() {
  if(root == NULL){ return 0; }
  std::queue<NodeT*> NodeQ;
  int levelWidth;
  int maxWidth = 0;
  NodeQ.push(root);

  while(!NodeQ.empty()) {
    levelWidth = NodeQ.size();
    if(levelWidth > maxWidth){ maxWidth = levelWidth; }
    
    for(int i = 0; i < levelWidth; i++){
      
      NodeT* curr = NodeQ.front();
      NodeQ.pop();

      if(curr->getLeft() != NULL) {
        NodeQ.push(curr->getLeft());
      }
      if(curr->getRight() != NULL) {
        NodeQ.push(curr->getRight());
      }

    }
  }

  return maxWidth;
}

int BST::nearestRelative(int n1, int n2){
  if(n1 == root->getData() || n2 == root->getData() || !search(n1) || !search(n2)){ return -1; }
  std::vector<int> ancestorsVector1 = ancestors(n1);
  std::vector<int> ancestorsVector2 = ancestors(n2);

  for(int i = 0; i < ancestorsVector1.size(); i++){
    for(int j = 0; j < ancestorsVector2.size(); j++){
      if(ancestorsVector1[i] == ancestorsVector2[j]){
        return ancestorsVector2[j];
      }
    }
  }
  return 0;
}

BST::BST(const BST& copy){
  root = NULL;
  copyConstructorHelper(copy.root);
}

void BST::copyConstructorHelper(NodeT* r){
  if( r != NULL ) {
    add(r->getData());
    copyConstructorHelper(r->getLeft());
    copyConstructorHelper(r->getRight());
  }
}

bool BST::operator==(const BST& tree){
  if(root->getData() != tree.root->getData()){ return false; }
  if( this->count() != tree.count() ){ return false; }
  if( this->height() != tree.height() ){ return false; }
  else{
    bool isEqualTo = true;
    return isEqualToHelper(tree.root, root, isEqualTo);
  }
}

bool BST::isEqualToHelper(NodeT* r1, NodeT* r2, bool b){
  if(r1 != NULL && r2 != NULL){
    b = (r1->getData() != r2->getData())? false : true;
    b = (b && isEqualToHelper(r1->getLeft(), r2->getLeft(), b)) && isEqualToHelper(r1->getRight(), r2->getRight(), b);
  }
  return b;
}

std::queue<int> BST::toQueue(){
  toQueueHelper(root);
  std::queue<int> treeQueue;
  while(!treeStack.empty()){
    treeQueue.push(treeStack.top());
    treeStack.pop();
  }
  return treeQueue;
}

void BST::toQueueHelper(NodeT* r){
  if ( r != NULL ) {
    toQueueHelper(r->getLeft());
    treeStack.push(r->getData());
    toQueueHelper(r->getRight());
  }
}