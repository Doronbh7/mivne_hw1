#ifndef AVLTREE_H
#define AVLTREE_H

template<class Key_Type, class Data_Type>
class AVLNode {
private:
    Key_Type key_val;
    Data_Type data_val;
    int height_val;
    AVLNode *right_node, *left_node, *parent_node;
    int balance_val;

public:
    //defining ctor
    AVLNode(Key_Type key_val, Data_Type data_val):key_val(key_val),data_val(data_val),height_val(0),right_node(
            nullptr),left_node(nullptr),parent_node(nullptr),balance_val(0) {}

    //defining a dtor
    ~AVLNode() {

    }

    //defining gets and sets
/**
 * The function set the node's  key
 */
    void setKey(Key_Type key_val) {
        this->key_val = key_val;
    }
/**
 * The function set the node's  data
  */
    void setData(Data_Type data_val) {
        this->data_val = data_val;
    }
/**
 * The function set the node's  left son
  */
    void setLeft(AVLNode<Key_Type, Data_Type>* node) {
        this->left_node = node;
        if (left_node != nullptr) {
            left_node->setParent(this);
        }
    }
/**
 * The function set  the node's  parent
 */
    void setParent(AVLNode<Key_Type, Data_Type>* node) {
        this->parent_node = node;
    }
/**
 * The function set the node's  height
 */
    void setHeight(int height_val) {
        this->height_val=height_val;
    }
/**
 * The function set the node's  balance
 */
    void setBalance(int balance_val) {
        this->balance_val=balance_val;
    }
    /**
 * The function set the node's  right son
 */
    void setRight(AVLNode<Key_Type, Data_Type>* node) {
        this->right_node = node;
        if (right_node != nullptr) {
            right_node->setParent(this);
        }
    }
/**
 * The function return the node's  key
 * @return
 */
    Key_Type getKey() {
        return key_val;
    }
/**
 * The function return the node's  data
 * @return
 */
    Data_Type getData() {
        return data_val;
    }
/**
 * The function return the node's  height
 * @return
 */
    int getHeight() {
        return height_val;
    }
/**
 * The function return the node's  balance
 * @return
 */
    int getBalance() {
        return balance_val;
    }

    /**
 * The function return the node's  right son
 * @return
 */
    AVLNode* getRight() {
        return right_node;
    }
/**
 * The function return the node's  lefts son
 * @return
 */
    AVLNode* getLeft() {
        return left_node;
    }
/**
 * The function return the node's  parent
 * @return
 */
    AVLNode* getParent() {
        return parent_node;
    }

};


template<class Key_Type, class Data_Type>
class AVLTree {
private:
    AVLNode<Key_Type,Data_Type>* root_node;
    AVLNode<Key_Type, Data_Type>* biggest_node; //biggest node according to key_val value
    AVLNode<Key_Type, Data_Type>* smallest_node; //smallest node according to key_val value
    int size_val; //number of nodes
public:
    //defining ctor
    AVLTree():
            root_node(nullptr), biggest_node(nullptr),smallest_node(nullptr), size_val(0) {
    }

    //defining dtor
    ~AVLTree() {
        deleteTree(root_node);
    }

    //help function in order to delete tree with post order search
    void deleteTree(AVLNode<Key_Type, Data_Type>* node) {
        //stop condition, if we reach dead end
        if (node == nullptr) {
            return;
        }
            //else, we perform post order search
        else {
            deleteTree(node->getLeft());
            deleteTree(node->getRight());
        }
        //checks if we need to remove value from root_node or biggest node
        if (node == biggest_node) {
            biggest_node = node->getParent();
        }
        if (node == smallest_node) {
            smallest_node = node->getParent();
        }

        //deletes current node after search, reduces size_val
        delete node;
        node= nullptr;
        size_val--;
    }

    /**
     *
     * @return the number of nodes in the tree
     */
    int getSize() {
        return size_val;
    }

    /**
     * insert a node to the tree
     * @param key_val
     * @param data_val
     * @return the pointer of the node
     */
    AVLNode<Key_Type, Data_Type>* insertNode(Key_Type key_val, Data_Type data_val) {
        AVLNode<Key_Type,Data_Type>* node=new AVLNode<Key_Type,Data_Type>(key_val,data_val);
        Key_Type curr_node_key=node->getKey();


        if (biggest_node == nullptr) {
            biggest_node = node;
        }else{
            Key_Type biggest_node_key=biggest_node->getKey();

            if (curr_node_key>biggest_node_key) {
                biggest_node = node;
            }
        }

        if (smallest_node == nullptr) {
            smallest_node = node;
        }else{
            Key_Type smallest_node_key=smallest_node->getKey();

            if (curr_node_key<smallest_node_key) {
                smallest_node = node;
            }
        }




        if (root_node == nullptr) {
            root_node = node;
            size_val++;
            root_node->setParent(nullptr);
            return node;
        }
        insertNodeHelp(node,root_node);

        size_val++;
        return node;

    }

    /**
     * help to insert the node to the tree. We use this function if the new node is isn't the root_node.
     * @param new_node the node we insert to the tree
     * @param current_node the current node
     * @return the current node
     */
    AVLNode<Key_Type, Data_Type>* insertNodeHelp(
            AVLNode<Key_Type, Data_Type> *new_node, AVLNode<Key_Type, Data_Type> *current_node) {
        if(current_node== nullptr){
            current_node= new_node;
            return new_node;
        }
        AVLNode<Key_Type,Data_Type>* right_node=current_node->getRight();
        AVLNode<Key_Type,Data_Type>* left_node=current_node->getLeft();

        Key_Type new_node_key=new_node->getKey();
        Key_Type current_node_key=current_node->getKey();


        if (new_node_key<current_node_key) {
            current_node->setLeft(insertNodeHelp(new_node,left_node));
        }
        else if (new_node_key >= current_node_key) {
            current_node->setRight(insertNodeHelp(new_node,right_node));
        }

        updateNodeHeight(current_node);

        int right_node_height;
        int left_node_height;
        if(right_node== nullptr){
            right_node_height=-1;
        }
        else{
            right_node_height=right_node->getHeight();
        }
        if(left_node== nullptr){
            left_node_height=-1;
        }
        else{
            left_node_height=left_node->getHeight();

        }


        int balance_val=left_node_height-right_node_height;

        current_node->setBalance(balance_val);
        if((current_node->getBalance()==2)||(current_node->getBalance()==-2)){
            return balanceTree(current_node);

        }

        return current_node;

    }

    /**
     * delete node in the tree by key_val
     * @param key_val
     */
    void deleteNodeByKey(Key_Type key_val) {
        if(size_val<=0){
            return;
        }
        if ( (root_node->getHeight()==0)&&(root_node->getKey()==key_val)){
            delete root_node;
            root_node= nullptr;
            size_val=0;
            biggest_node= nullptr;
            smallest_node= nullptr;
            return;
        }
        if (biggest_node->getKey()==key_val) {
            if(biggest_node->getLeft()!= nullptr){
                biggest_node = biggest_node->getLeft();
            }else{
                biggest_node = biggest_node->getParent();
            }
        }

        if (smallest_node->getKey()==key_val) {
            if(smallest_node->getRight()!= nullptr){
                smallest_node = smallest_node->getRight();
            }else{
                smallest_node = smallest_node->getParent();
            }
        }
        deleteNodeByKeyHelp(key_val, root_node);
        size_val=size_val-1;
        if(size_val==1){
            biggest_node = smallest_node;
        }
        if(size_val==0){
            biggest_node= nullptr;
            smallest_node= nullptr;
            root_node= nullptr;
        }



    }

    /**
     * Help to delete the node by key_val.We use this function if the key_val is isn't the root_node and the root_node height_val is isn't 0.
     * @param key_val The key_val of the node that we want to delete.
     * @param current_node The current node.
     * @return The current node
     */

    AVLNode<Key_Type,Data_Type>* deleteNodeByKeyHelp(Key_Type key_val,
                                           AVLNode<Key_Type, Data_Type> *current_node) {

        if (current_node== nullptr) {
            return nullptr;
        }

        if(current_node->getKey() > key_val) {
            current_node->setLeft(deleteNodeByKeyHelp(key_val,current_node->getLeft())) ;
        }
        if(current_node->getKey() == key_val) {
            bool first_condition= false;
            if(!(current_node->getLeft())){
                first_condition= true;
            }
            bool second_condition= false;
            if(!(current_node->getRight())){
                second_condition= true;
            }
            if (first_condition || second_condition) {
                AVLNode<Key_Type, Data_Type> *temp_node = current_node->getLeft();
                if (!temp_node) {
                    if (current_node->getRight()== nullptr) {
                        temp_node = current_node;
                        current_node = nullptr;
                    }
                    else {
                        temp_node = current_node->getRight();
                    }
                }
                if (current_node != nullptr) {
                    if(temp_node==smallest_node){
                        smallest_node=current_node;
                    }
                    if(temp_node==biggest_node){
                        biggest_node=current_node;
                    }
                    Data_Type current_node_data=current_node->getData();
                    current_node->setLeft(temp_node->getLeft());
                    current_node->setRight(temp_node->getRight());
                    current_node->setData(temp_node->getData());
                    temp_node->setData(current_node_data);
                    current_node->setKey(temp_node->getKey());

                }
                delete temp_node;
                temp_node= nullptr;
            }
            else {
                AVLNode<Key_Type, Data_Type> *temp_node = current_node->getRight();
                while (temp_node->getLeft()) {
                    temp_node = temp_node->getLeft();
                }
                if(temp_node==smallest_node){
                    smallest_node=current_node;
                }
                if(temp_node==biggest_node){
                    biggest_node=current_node;
                }

                Data_Type temp_data = current_node->getData();
                Key_Type temp_key = current_node->getKey();
                current_node->setData(temp_node->getData());
                current_node->setKey(temp_node->getKey());
                temp_node->setData(temp_data);
                temp_node->setKey(temp_key);

                current_node->setRight(deleteNodeByKeyHelp(key_val,current_node->getRight()));
            }
        }
        else {
            current_node->setRight(deleteNodeByKeyHelp(key_val,current_node->getRight())) ;
        }

        if (current_node== nullptr) {
            return current_node;
        }

        AVLNode<Key_Type,Data_Type>* right_node=current_node->getRight();
        AVLNode<Key_Type,Data_Type>* left_node=current_node->getLeft();

        updateNodeHeight(current_node);

        int right_node_height;
        int left_node_height;
        if(right_node== nullptr){
            right_node_height=-1;
        }
        else{
            right_node_height=right_node->getHeight();
        }
        if(left_node== nullptr){
            left_node_height=-1;
        }
        else{
            left_node_height=left_node->getHeight();

        }


        int balance_val=left_node_height-right_node_height;

        current_node->setBalance(balance_val);

        if((current_node->getBalance()==2)||(current_node->getBalance()==-2)){
            return balanceTree(current_node);

        }

        return current_node;

    }


    /**
	 * balance_val the tree
	 * @param node
	 * @return The updated node
	 */
    AVLNode<Key_Type, Data_Type>* balanceTree(AVLNode<Key_Type, Data_Type> *node) {

        int left_node_balance;
        int right_node_balance;

        if(node->getBalance()==2){
            AVLNode<Key_Type,Data_Type>* left_node=node->getLeft();
            int left_right_node_height;
            int left_left_node_height;
            AVLNode<Key_Type, Data_Type> *left_right_node = left_node->getRight();
            AVLNode<Key_Type, Data_Type> *left_left_node = left_node->getLeft();

            if (left_right_node == nullptr) {
                left_right_node_height = -1;
            } else {
                left_right_node_height = left_right_node->getHeight();
            }

            if (left_left_node == nullptr) {
                left_left_node_height = -1;
            } else {
                left_left_node_height = left_left_node->getHeight();

            }
            left_node_balance = left_left_node_height - left_right_node_height;

            if(left_node_balance>=0){ //LL

                Key_Type root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=left_node;
                    root_node->setParent(nullptr);
                }
                left_node->setRight(node);
                node->setLeft(left_right_node);
                updateNodeHeight(node);
                updateNodeHeight(left_node);
                return left_node;

            }

            if(left_node_balance==-1){ //LR
                AVLNode<Key_Type,Data_Type>* node_left_right=node->getLeft()->getRight();
                AVLNode<Key_Type,Data_Type>* node_left_right_left=node_left_right->getLeft();

                Key_Type root_key=root_node->getKey();

                AVLNode<Key_Type,Data_Type>* LeftNode=node->getLeft();


                Key_Type LeftNode_key=LeftNode->getKey();


                if(root_key == LeftNode_key){
                    root_node=node_left_right;
                    root_node->setParent(nullptr);
                }

                node_left_right->setLeft(node->getLeft());
                node->getLeft()->setRight(node_left_right_left);
                updateNodeHeight(node->getLeft());
                updateNodeHeight(node_left_right);
                node->setLeft(node_left_right);


                AVLNode<Key_Type,Data_Type>* node_left=node->getLeft();
                node_left_right=node->getLeft()->getRight();


                root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=node_left;
                    root_node->setParent(nullptr);
                }
                node_left->setRight(node);
                node->setLeft(node_left_right);
                updateNodeHeight(node);
                updateNodeHeight(node_left);
                return node_left ;
            }
            return node;
        }

        if(node->getBalance()==(-2)){
            AVLNode<Key_Type,Data_Type>* right_node=node->getRight();
            int right_right_node_height;
            int right_left_node_height;
            AVLNode<Key_Type, Data_Type> *right_right_node = right_node->getRight();
            AVLNode<Key_Type, Data_Type> *right_left_node = right_node->getLeft();

            if (right_right_node == nullptr) {
                right_right_node_height = -1;
            } else {
                right_right_node_height = right_right_node->getHeight();
            }

            if (right_left_node == nullptr) {
                right_left_node_height = -1;
            } else {
                right_left_node_height = right_left_node->getHeight();

            }
            right_node_balance =
                    right_left_node_height - right_right_node_height;
            if(right_node_balance<=0){ //RR

                Key_Type root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=right_node;
                    root_node->setParent(nullptr);
                }
                right_node->setLeft(node);
                node->setRight(right_left_node);
                updateNodeHeight(node);
                updateNodeHeight(right_node);
                return right_node;

            }

            if(right_node_balance==1){ //RL

                AVLNode<Key_Type,Data_Type>* node_right_left=node->getRight()->getLeft();
                AVLNode<Key_Type,Data_Type>* node_right_left_right=node_right_left->getRight();

                Key_Type root_key=root_node->getKey();
                Key_Type Right_node_key=node->getRight()->getKey();

                if(root_key == Right_node_key){
                    root_node=node_right_left;
                    root_node->setParent(nullptr);
                }

                node_right_left->setRight(node->getRight());
                node->getRight()->setLeft(node_right_left_right);
                updateNodeHeight(node->getRight());
                updateNodeHeight(node_right_left);
                node->setRight(node_right_left);


                AVLNode<Key_Type,Data_Type>* node_right=node->getRight();
                node_right_left=node->getRight()->getLeft();

                root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=node_right;
                    root_node->setParent(nullptr);
                }
                node_right->setLeft(node);
                node->setRight(node_right_left);
                updateNodeHeight(node);
                updateNodeHeight(node_right);
                return node_right ;

            }
            return node;

        }
        return node;

    }

    /**
     *
     * @param key_val
     * @return true-if the node is exist in the tree
     * false-if the node is not exist in the tree
     */
    bool isExist(Key_Type key_val) {
        if(this->root_node== nullptr){
            return false;
        }
        if(isExistHelp(key_val,root_node)== nullptr){
            return false;
        }
        return true;
    }

    /**
     * Help to find if the node is exist in the tree. We use this function if the root_node is not nullptr.
     * @param key_val The key_val of the node we search.
     * @param node The root_node of the tree.
     * @return
     * nullptr-The node is not exist
     * other- The node is exist
     */
    AVLNode<Key_Type,Data_Type>* isExistHelp(Key_Type key_val, AVLNode<Key_Type, Data_Type> *node) {
        if(node == nullptr) {
            return nullptr;
        }
        if(key_val < node->getKey()) {
            return isExistHelp(key_val, node->getLeft());
        }

        if(key_val > node->getKey()) {
            return isExistHelp(key_val, node->getRight());
        }else{
            if(key_val==node->getKey()) {
                return node;
            }
        }

        return nullptr;
    }

    /**
     *
     * @param key_val
     * @return the tree node by key_val
     */
    AVLNode<Key_Type,Data_Type>* getNodeByKey(Key_Type key_val) {
        return isExistHelp(key_val,root_node);
    }











/**
 * Update the node height_val
 * @param node The node that we update
 */
    void updateNodeHeight(AVLNode<Key_Type, Data_Type> *node) {


        int right_node_height;
        int left_node_height;
        if(node->getRight()== nullptr){
            right_node_height=-1;
        }
        else{
            AVLNode<Key_Type,Data_Type>* right_node=node->getRight();
            right_node_height=right_node->getHeight();
        }

        if(node->getLeft()== nullptr){
            left_node_height=-1;
        }
        else{
            AVLNode<Key_Type,Data_Type>* left_node=node->getLeft();
            left_node_height=left_node->getHeight();

        }


        if(left_node_height>right_node_height){
            node->setHeight(left_node_height+1);
        }
        else{
            node->setHeight(right_node_height+1);
        }
    }


    /**
     * insert to the array the k biggest nodes in the tree
     * @param array
     * @param K
     */
    void GetKLargestReversedInOrderArray(Data_Type* array,int K) {
        if(this->size_val==1){
            smallest_node=root_node;
            biggest_node=root_node;
        }
        AVLNode<Key_Type,Data_Type> *max_node_iterator=this->getBiggestNode();
        AVLNode <Key_Type, Data_Type>** KLargestReversedInOrderArray=new AVLNode <Key_Type, Data_Type>* [K];
        AVLNode <Key_Type, Data_Type> * current_node_iterator=max_node_iterator;
        for (int i = 0; i < K; i++) {
            KLargestReversedInOrderArray[i]=current_node_iterator;
            current_node_iterator=getPreviusNodeInOrderPredeccessor(current_node_iterator);
        }


        for (int i = 0; i < K; i++) {
            array[i]=KLargestReversedInOrderArray[i]->getData();
        }


        delete [] KLargestReversedInOrderArray;

        return ;
    }

    /**
     * insert to the array the k smallest nodes in the tree(inorder)
     * @param array
     * @param K
     */
    void GetKSmallestInOrderArray(Data_Type* array,int K) {
        if(this->size_val==1){
            smallest_node=root_node;
            biggest_node=root_node;
        }
        AVLNode<Key_Type,Data_Type> *min_node_iterator=this->getSmallestNode();
        AVLNode <Key_Type, Data_Type>** KSmallestInOrderArray=new AVLNode <Key_Type, Data_Type>* [K];
        AVLNode <Key_Type, Data_Type> * current_node_iterator=min_node_iterator;
        for (int i = 0; i < K; i++) {
            KSmallestInOrderArray[i]=current_node_iterator;
            current_node_iterator=getNextNodeInOrderSuccessor(current_node_iterator);
        }
        for (int i = 0; i < K; i++) {
            array[i]= KSmallestInOrderArray[i]->getData();
        }
        delete [] KSmallestInOrderArray;

        return ;
    }


/**
 * Successor implemention
 * @param curr_node
 * @return  the next node of curr_node  inorder
 */
    AVLNode<Key_Type, Data_Type>* getNextNodeInOrderSuccessor(AVLNode<Key_Type,Data_Type>* curr_node){
        if(curr_node== nullptr){
            return nullptr;
        }

        if (curr_node->getRight() != nullptr){
            return getLeftMostRightChild(curr_node);
        }

        else
            return getFirstRightParent(curr_node);

    }

/**
 * return the leftest (smaller) child in the right subtree.
 * @param node
 * @return
 */
    AVLNode<Key_Type,Data_Type>* getLeftMostRightChild(AVLNode<Key_Type,Data_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        node = node->getRight();
        if(node== nullptr){
            return nullptr;
        }
        while (node->getLeft() != nullptr){
            if(node== nullptr){
                return nullptr;
            }
            node = node->getLeft();
            if(node== nullptr){
                return nullptr;
            }
        }
        return node;
    }

/**
 * The function go up until the first parent that has left son.
 * @param node
 * @return
 */
    AVLNode<Key_Type,Data_Type>* getFirstRightParent(AVLNode<Key_Type,Data_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        AVLNode<Key_Type,Data_Type>* parent_node = node->getParent();
        if (parent_node == nullptr)
            return nullptr;

        while (parent_node != nullptr && parent_node->getLeft() != node){
            node = parent_node;
            if(node== nullptr){
                return nullptr;
            }
            parent_node = node->getParent();
        }
        return parent_node;
    }


/**
 * Predeccessor implemention
 * @param curr_node
 * @return  the previous node of curr_node  inorder
 */
    AVLNode<Key_Type, Data_Type>* getPreviusNodeInOrderPredeccessor(AVLNode<Key_Type,Data_Type>* curr_node){
        if(curr_node== nullptr){
            return nullptr;
        }
        if (curr_node->getLeft() != nullptr){
            return getRightMostLeftChild(curr_node);
        }

        else
            return getFirstLeftParent(curr_node);

    }

 /**
 * return the rightest (biggest) child in the left subtree.
 * @param node
 * @return
 */
    AVLNode<Key_Type,Data_Type>* getRightMostLeftChild(AVLNode<Key_Type,Data_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        node = node->getLeft();
        if(node== nullptr){
            return nullptr;
        }
        while (node->getRight() != nullptr){
            if(node== nullptr){
                return nullptr;
            }
            node = node->getRight();
            if(node== nullptr){
                return nullptr;
            }
        }
        return node;
    }

    /**
 * The function go up until the first parent that has right son.
 * @param node
 * @return
 */
    AVLNode<Key_Type,Data_Type>* getFirstLeftParent(AVLNode<Key_Type,Data_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        AVLNode<Key_Type,Data_Type>* parent_node = node->getParent();
        if (parent_node == nullptr)
            return nullptr;

        while (parent_node != nullptr && parent_node->getRight() != node){
            node = parent_node;
            if(node== nullptr){
                return nullptr;
            }
            parent_node = node->getParent();
        }
        return parent_node;
    }

/**
 * The function return the Biggest Node in the avl tree
 * @return
 */
    AVLNode<Key_Type,Data_Type>* getBiggestNode() {
        return this->biggest_node;
    }


    /**
 * The function return the Smallest Node in the avl tree
 * @return
 */
    AVLNode<Key_Type,Data_Type>* getSmallestNode() {
        return this->smallest_node;
    }


    /**
 * The function return the Biggest Data in the avl tree
 * @return
 */
    Data_Type getBiggestData() {
        return this->biggest_node->getData();
    }


    /**
 * The function return the Smallest Data in the avl tree
 * @return
 */
    Data_Type getSmallestData() {
        return this->smallest_node->setData();
    }



/*  */
/**
 *  Constructs AVL Tree from a sorted array
 * @param DataArr Array of the data
 * @param KeyArr Array of the Data keys
 * @param Size Size of the array
 */

    void sortedArrayToAVL(Data_Type DataArr[],Key_Type KeyArr[],int Size)
    {
        size_val=Size;
        sortedArrayToAVLHelp(DataArr,KeyArr,0, Size-1);

    }

/**
 * Help to construct AVL Tree from a sorted array with recursive
 * @param DataArr Array of the data
 * @param KeyArr Array of the Data keys
 * @param start Start of the array
 * @param end End of the array
 * @return The current node
 */
    AVLNode<Key_Type,Data_Type>* sortedArrayToAVLHelp(Data_Type DataArr[],Key_Type KeyArr[],
                            int start, int end)
    {
        /* Base Case */
        if (start > end)
            return nullptr;

        /* Get the middle element  */
        int mid = (start + end)/2;

        AVLNode<Key_Type,Data_Type>* node=new AVLNode<Key_Type,Data_Type>(KeyArr[mid],DataArr[mid]);
        Key_Type curr_node_key=node->getKey();


        if (biggest_node == nullptr) {
            biggest_node = node;
        }else{
            Key_Type biggest_node_key=biggest_node->getKey();

            if (curr_node_key>biggest_node_key) {
                biggest_node = node;
            }
        }

        if (smallest_node == nullptr) {
            smallest_node = node;
        }else{
            Key_Type smallest_node_key=smallest_node->getKey();

            if (curr_node_key<smallest_node_key) {
                smallest_node = node;
            }
        }




        if (root_node == nullptr) {
            root_node = node;

            root_node->setParent(nullptr);
        }



        /* Recursively construct the left subtree
        and make it left child of node */
        node->setLeft(sortedArrayToAVLHelp(DataArr,KeyArr, start,mid - 1));

        /* Recursively construct the right subtree
        and make it right child of node */
        node->setRight(sortedArrayToAVLHelp(DataArr,KeyArr, mid + 1,end));
        updateNodeHeight(node);
        return node;
    }

    /**
     * Delete the data in every node in the tree by inorder
     */
    void deleteAllDataInTree(){

        Data_Type* data_array=new Data_Type[this->size_val];

        GetKSmallestInOrderArray(data_array,this->size_val);

        for(int i=0;i<(this->size_val);i++){
            delete data_array[i];
        }
        delete[] data_array;
    }

};

#endif