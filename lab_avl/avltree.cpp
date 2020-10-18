/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    //std::cout << "reached line " << __LINE__ << std::endl;
    Node* child = t -> right;
    t -> right = child -> left;
    child -> left = t;
    t = child;
    t -> left -> height = 1 + std::max(heightOrNeg1(t -> left -> left), heightOrNeg1(t -> left -> right));
    t -> height = 1 + std::max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* child = t -> left;
    t -> left = child -> right;
    child -> right = t;
    t = child;
    t -> right -> height = 1 + std::max(heightOrNeg1(t -> right -> left), heightOrNeg1(t -> right -> right));
    t -> height = 1 + std::max(heightOrNeg1(t -> left), heightOrNeg1(t -> right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //std::cout << "reached line " << __LINE__ << std::endl;
    if (subtree == NULL) {
        return;
    }

    int balance = (heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left));

    if (balance == 2) {
        int rightBalance = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);

        if (rightBalance == 1) {
            rotateLeft(subtree);
        } else if (rightBalance == -1) {
            rotateRightLeft(subtree);
        }
    }

    if (balance == -2) {
        int leftBalance = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);

        if (leftBalance == -1) {
            rotateRight(subtree);
        } else if (leftBalance == 1) {
            rotateLeftRight(subtree);
        }
    }

    subtree -> height = 1 + std::max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        Node* toInsert = new Node(key, value);
        if (root == NULL) {
            root = toInsert;
        }
        subtree = toInsert;
        return;
    }
    
    if (subtree -> key > key) {
        insert(subtree -> left, key, value);

        int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
        int leftBalance = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left -> left);

        if (balance == -2) {
            if (leftBalance == -1) {
                rotateRight(subtree);
            } else {
                rotateLeftRight(subtree);
            }
        }        
    } else if (subtree -> key <= key) {
        insert(subtree -> right, key, value);

        int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
        int leftBalance = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right -> left);

        if (balance == 2) {
            if (leftBalance == 1) {
                rotateLeft(subtree);
            } else {
                rotateRightLeft(subtree);
            }
        }
    }

    subtree -> height = std::max(heightOrNeg1(subtree -> left), heightOrNeg1(subtree -> right));
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* IOP = subtree -> left;
            while (IOP -> right != NULL) {
                IOP = IOP -> right;
            }

            swap(subtree, IOP);
            remove (subtree -> left, key);

            /*
            if (subtree -> left -> right) {
                std::cout << "reached line " << __LINE__ << std::endl;
                //Node* temp = subtree -> left;
                Node * largestNode = subtree -> left -> right;
                while (largestNode -> right != NULL) {
                    //temp = temp -> right;
                    largestNode = largestNode -> right;
                }
                //temp -> right = largestNode -> left;
                swap(subtree, largestNode);
                remove(subtree -> left, key);
            } else {
                std::cout << "reached line " << __LINE__ << std::endl;
                swap(subtree, subtree -> left);
                remove(subtree -> left, key);
            } */
        } else {
            /* one-child remove */
            // your code here
            std::cout << "reached line " << __LINE__ << std::endl;
            if (subtree -> left) {
                swap(subtree, subtree -> left);
                remove(subtree -> left, key);
            } else if (subtree -> right) {
                swap(subtree, subtree -> right);
                remove(subtree -> right, key);
            }
        }
        // your code here
        std::cout << "reached line " << __LINE__ << std::endl;
    }
    if (subtree != NULL) {
        rebalance(subtree);
    }
}
