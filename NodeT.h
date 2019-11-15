class NodeT {
  public:
    NodeT(int data);
    void setData(int data);
    void setLeft(NodeT *left);
    void setRight(NodeT *right);
    int getData();
    NodeT* getLeft();
    NodeT* getRight();
  
  private:
    int data;
    NodeT *left;
    NodeT *right;
};

NodeT::NodeT(int data) {
  this->data = data;
  this->left = NULL;
  this->right = NULL;
}

void NodeT::setData(int data) {
  this->data = data;
}

void NodeT::setLeft(NodeT *left) {
  this->left = left;
}

void NodeT::setRight(NodeT *right) {
  this->right = right;
}

int NodeT::getData() {
  return data;
}

NodeT* NodeT::getLeft() {
  return this->left;
}

NodeT* NodeT::getRight() {
  return this->right;
}
