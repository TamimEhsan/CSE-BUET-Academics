package com.tamimehsan;

public class BinarySearchTree {
    /**
     * a binary search tree (BST), also called an
     * ordered or sorted binary tree, is a rooted
     * binary tree whose internal nodes each store
     * a key greater than all the keys in the node's
     * left subtree and less than those in its right subtree.
     */
    private Node root;

    public BinarySearchTree() {
    }

    /**
     * Inserts item in the BST. If BST is empty then it is
     * inserted as node, else a recursive function @insertItem(Node,int) is called
     * @param item
     */
    public void insertItem(int item) {
        if( root == null ){
            root = new Node(item,null,null);
        }else insertItem(root, item);
    }

    /**
     * Recursive function to insert  item in BST
     * @param node Current standing position in BST which is compared
     *             with item
     * @param item The value to be added
     */
    private void insertItem(Node node, int item) {
        if( node.getValue() < item ){           // The item should be placed in the right of this node
           if( node.getRight() == null ){
               Node newNode = new Node(item,null,null);
               node.setRight(newNode);
           }else{
               insertItem(node.getRight(),item);
           }
        } else if( node.getValue() > item ){    // The item should be placed in the left of this node
            if( node.getLeft() == null ){
                Node newNode = new Node(item,null,null);
                node.setLeft(newNode);
            }else{
                insertItem(node.getLeft(),item);
            }
        }else{                                  // The item already exists in this tree
            return;
        }
    }

    /**
     * Decides what to output with respect to if
     * a item is present in BST
     * @param item
     */
    public void searchItem(int item) {
        if (searchItem(root, item) == null) System.out.println(item + " has not been found");
        else System.out.println(item + " has been found");
    }

    /**
     * A recursive function to find a item in BST
     * @param node Current comparing position in BST
     * @param item The value which is to be searched
     * @return true if found, false otherwise
     */
    private Node searchItem(Node node, int item) {
        if (node == null || node.getValue() == item) return node;
        else if (node.getValue() < item) return searchItem(node.getRight(), item);
        else return searchItem(node.getLeft(), item);
    }

    /**
     * Iterative function to find the in order successor
     * value of item
     * @param item
     * @return the immediate larger value than item
     */
    public int getInOrderSuccessor(int item) {
        Node node = searchItem(root, item);
        if (node == null) return -1;            // The given value doesn't exist in the BST
        if (node.getRight() != null)            // the successor is the smallest value in right subtree
            return getMinItem(node.getRight());
        Node curr = root;                       // We will start looking from the root of tree
        Node seccessor = null;
        while (curr != null) {
            if (curr.getValue() > node.getValue()) {
                seccessor = curr;
                curr = curr.getLeft();
            } else if (curr.getValue() < node.getValue()) {
                curr = curr.getRight();
            } else {
                break;
            }
        }
        if (seccessor == null) return -1;
        else return seccessor.getValue();
    }

    /**
     * Iterative function to find the In order predecessor
     * of item
     * @param item
     * @return the immediate smaller value than item
     */
    public int getInOrderPredecessor(int item) {
        Node node = searchItem(root, item);
        if (node == null) return -1;
        if (node.getLeft() != null)
            return getMaxItem(node.getLeft());      // Predecessor is the maximum value in left subtree
        Node curr = root;                           // We will start from root
        Node predecessor = null;
        while (curr != null) {
            if (curr.getValue() < node.getValue()) {
                predecessor = curr;
                curr = curr.getRight();
            } else if (curr.getValue() > node.getValue()) {
                curr = curr.getLeft();
            } else {
                break;
            }
        }
        if (predecessor == null) return -1;
        else return predecessor.getValue();
    }

    /**
     * Entry point for deleting a value
     * @param item value which is to be deleted
     */
    public void deleteItem(int item) {
        root = deleteItem(root, item);
    }

    /**
     * Recurive function to delete a value
     * @param node Current comparative position in BST
     * @param item The value which is to be deleted
     * @return the curremt position after some provbable change
     */
    private Node deleteItem(Node node, int item) {
        if (node == null) return node;
        if (node.getValue() < item) {
            node.setRight(deleteItem(node.getRight(), item));
        } else if (node.getValue() > item) {
            node.setLeft(deleteItem(node.getLeft(), item));
        } else {
            if (node.getLeft() == null) return node.getRight();
            if (node.getRight() == null) return node.getLeft();
            int min = getMinItem(node.getRight());
            node.setValue(min);
            node.setRight(deleteItem(node.getRight(), min));
        }
        return node;
    }

    /**
     * Finds the depth of a item
     * @param item
     * @return -1 if item not found ,
     *         else calls recursive function to find the depth
     */
    public int getItemDepth(int item) {
        if (searchItem(root, item) == null) return -1;
        return getItemDepth(root, item)-1;
    }

    /**
     * Recurive function to find the depth of an item present in BST
     * @param node Current position in BST
     * @param item
     * @return distance between root and item node
     */
    private int getItemDepth(Node node, int item) {
        if (node.getValue() == item) return 1;
        else if (node.getValue() < item) return getItemDepth(node.getRight(), item) + 1;
        else return getItemDepth(node.getLeft(), item) + 1;
    }

    /**
     * Finds the maximum value in BST
     * @return maximum in BST
     */
    public int getMaxItem() {
        return getMaxItem(root);
    }

    /**
     * Recursive function to find the maximum value
     * in BST
     * @param node Current position in BST
     * @return maximum in BST
     */
    private int getMaxItem(Node node) {
        if (node == null) return -1;
        while (node.getRight() != null) node = node.getRight();
        return node.getValue();
    }

    /**
     * Finds the minimum value in BST
     * @return minimum in BST
     */
    public int getMinItem() {
        return getMinItem(root);
    }

    /**
     * Recursive function to find the minimum value
     * in BST
     * @param node Current position in BST
     * @return minimum in BST
     */
    private int getMinItem(Node node) {
        if (node == null) return -1;
        while (node.getLeft() != null) node = node.getLeft();
        return node.getValue();
    }

    /**
     * calls recursive overloaded function
     * @return value obtained from overloaded function
     */
    public int getHeight() {
        return getHeight(root)-1;
    }

    /**
     * Recursive function to find the height of a tree
     * @param node Current position in BST
     * @return maximum of height of two child nodes +1
     */
    private int getHeight(Node node) {
        if (node == null) return 0;
        else return Math.max(getHeight(node.getLeft()), getHeight(node.getRight())) + 1;
    }

    /**
     * Calls recursive overloaded print function
     */
    public void printInOrder() {
        printInOrder(root);
    }

    /**
     * Recursive DFS implementation of In order tree traversal
     * @param node Current position in tree
     */
    private void printInOrder(Node node) {
        if (node == null) return;
        printInOrder(node.getLeft());
        System.out.print(node.getValue() + " ");
        printInOrder(node.getRight());
    }

    /**
     * Calls recursive overloaded print function
     */
    public void printPreOrder() {
        printPreOrder(root);
    }

    /**
     * Recursive DFS implementation of Pre order tree traversal
     * @param node Current position in tree
     */
    private void printPreOrder(Node node) {
        if (node == null) return;
        System.out.print(node.getValue() + " ");
        printPreOrder(node.getLeft());
        printPreOrder(node.getRight());
    }

    /**
     * Calls recursive overloaded print function
     */
    public void printPostOrder() {
        printPostOrder(root);
    }

    /**
     * Recursive DFS implementation of Post order tree traversal
     * @param node Current position in tree
     */
    private void printPostOrder(Node node) {
        if (node == null) return;
        printPostOrder(node.getLeft());
        printPostOrder(node.getRight());
        System.out.print(node.getValue() + " ");
    }

    /**
     * Calls recursive function for the size of tree
     * @return tree size
     */
    public int getSize() {
        return getSize(root);
    }

    /**
     * Recursive function to find the size of tree
     * @param node
     * @return size of subtree in child nodes +1
     */
    private int getSize(Node node) {
        if (node == null) return 0;
        else return getSize(node.getLeft()) + getSize(node.getRight()) + 1;
    }
}
