package com.tamimehsan;

public class AVL {
    /**
     * a binary search tree (BST), also called an
     * ordered or sorted binary tree, is a rooted
     * binary tree whose internal nodes each store
     * a key greater than all the keys in the node's
     * left subtree and less than those in its right subtree.
     */
    private Node root;

    public AVL() {
    }

    /**
     * Inserts item in the AVL. If AVL is empty then it is
     * inserted as node, else a recursive function @insertItem(Node,int) is called
     *
     * @param item
     */
    public void insertItem(int item) {
        if (root == null) {
            root = new Node(item, null, null);
        } else root = insertItem(root, item);
    }

    /**
     * Recursive function to insert  item in AVL
     *
     * @param node Current standing position in AVL which is compared
     *             with item
     * @param item The value to be added
     */
    private Node insertItem(Node node, int item) {

        if (node == null) {
            return new Node(item);
        } else if (node.getValue() > item) {
            node.setLeft(insertItem(node.getLeft(), item));
        } else if (node.getValue() < item) {
            node.setRight(insertItem(node.getRight(), item));
        } else {
            return node;
        }

        return rebalance(node);
    }

    /**
     * Balances the subtree of nodex according to height variant
     *
     * @param nodex Node to be balanced
     * @return the balanced node
     */
    private Node rebalance(Node nodex) {
        updateHeight(nodex);

        if (getNodeHeight(nodex.getLeft()) - getNodeHeight(nodex.getRight()) > 1) {
            System.out.print("Height invariant violated.\n" +
                    "After rebalancing: ");
            Node nodey = nodex.getLeft();
            if (getNodeHeight(nodey.getLeft()) >= getNodeHeight(nodey.getRight())) {
                // first case
                nodex = rotateRight(nodex);
            } else {
                // second case

                nodex.setLeft(rotateLeft(nodex.getLeft()));
                nodex = rotateRight(nodex);
            }

        } else if (getNodeHeight(nodex.getLeft()) - getNodeHeight(nodex.getRight()) < -1) {
            System.out.print("Height invariant violated.\n" +
                    "After rebalancing: ");

            Node nodey = nodex.getRight();
            if (getNodeHeight(nodey.getRight()) >= getNodeHeight(nodey.getLeft())) {
                nodex = rotateLeft(nodex);
            } else {

                nodex.setRight(rotateRight(nodex.getRight()));
                nodex = rotateLeft(nodex);
            }
        }

        return nodex;
    }

    /**
     * Right rotation
     *
     * @param nodex root of the subtree to be rotated
     * @return changed root after rotation
     */
    private Node rotateRight(Node nodex) {
        Node nodey = nodex.getLeft();
        Node nodeB = nodey.getRight();

        nodex.setLeft(nodeB);
        nodex = updateHeight(nodex);

        nodey.setRight(nodex);
        nodey = updateHeight(nodey);


        return nodey;
    }

    /**
     * Left rotation
     *
     * @param nodey root of the subtree to be rotated
     * @return changed root after rotation
     */
    private Node rotateLeft(Node nodey) {
        Node nodex = nodey.getRight();
        Node nodeB = nodex.getLeft();

        nodey.setRight(nodeB);
        nodey = updateHeight(nodey);
        nodex.setLeft(nodey);
        nodex = updateHeight(nodex);
        return nodex;
    }


    /**
     * Decides what to output with respect to if
     * a item is present in AVL
     *
     * @param item
     */
    public void searchItem(int item) {
        if (searchItem(root, item) == null) System.out.println("False");
        else System.out.println("True");
    }

    /**
     * A recursive function to find a item in AVL
     *
     * @param node Current comparing position in AVL
     * @param item The value which is to be searched
     * @return true if found, false otherwise
     */
    private Node searchItem(Node node, int item) {
        if (node == null || node.getValue() == item) return node;
        else if (node.getValue() < item) return searchItem(node.getRight(), item);
        else return searchItem(node.getLeft(), item);
    }


    /**
     * Entry point for deleting a value
     *
     * @param item value which is to be deleted
     */
    public void deleteItem(int item) {
        root = deleteItem(root, item);
    }

    /**
     * Recurive function to delete a value
     *
     * @param node Current comparative position in AVL
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

        if (node != null) {
            node = rebalance(node);
        }

        return node;
    }


    /**
     * Finds the maximum value in AVL
     *
     * @return maximum in AVL
     */
    public int getMaxItem() {
        return getMaxItem(root);
    }

    /**
     * Recursive function to find the maximum value
     * in AVL
     *
     * @param node Current position in AVL
     * @return maximum in AVL
     */
    private int getMaxItem(Node node) {
        if (node == null) return -1;
        while (node.getRight() != null) node = node.getRight();
        return node.getValue();
    }

    /**
     * Finds the minimum value in AVL
     *
     * @return minimum in AVL
     */
    public int getMinItem() {
        return getMinItem(root);
    }

    /**
     * Recursive function to find the minimum value
     * in AVL
     *
     * @param node Current position in AVL
     * @return minimum in AVL
     */
    private int getMinItem(Node node) {
        if (node == null) return -1;
        while (node.getLeft() != null) node = node.getLeft();
        return node.getValue();
    }


    /**
     * Calls recursive overloaded print function
     */
    public void printPreOrder() {
        printPreOrder(root);
        System.out.println("");
    }

    /**
     * Recursive DFS implementation of Pre order tree traversal
     *
     * @param node Current position in tree
     */
    private void printPreOrder(Node node) {
        if (node == null) {
            return;
        }
        System.out.print(node.getValue());
        if (node.getLeft() == null && node.getRight() == null) return;
        System.out.print("(");
        printPreOrder(node.getLeft());
        System.out.print(")(");
        printPreOrder(node.getRight());
        System.out.print(")");
    }


    /**
     * Gets the height of a node , -1 if null
     *
     * @param node
     * @return the height
     */
    private int getNodeHeight(Node node) {
        if (node == null) return -1;
        else return node.getHeight();
    }

    /**
     * Updates the height of node according to children
     *
     * @param node
     * @return the node after updating the height
     */
    private Node updateHeight(Node node) {
        node.setHeight(1 + Math.max(getNodeHeight(node.getLeft()), getNodeHeight(node.getRight())));
        return node;
    }

}
