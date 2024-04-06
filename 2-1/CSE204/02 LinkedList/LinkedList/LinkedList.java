package com.tamimehsan;

public class LinkedList {
    private Node currentNode;
    private int nodeCount;
    private int direction = 0;

    public LinkedList(){
        currentNode = null;
        nodeCount = 0;
    }
    public LinkedList(int [] reflexes){
        Node firstNode = new Node(1,null,null,reflexes[0]);
        Node previousNode = firstNode;
        for(int i=1;i<reflexes.length;i++){
            Node node = new Node(i+1,previousNode,null,reflexes[i]);
            previousNode.setNext(node);
            previousNode = node;
        }
        previousNode.setNext(firstNode);
        firstNode.setPrevious(previousNode);
        currentNode = firstNode;
        nodeCount = reflexes.length;
    }
    public void deleteNode(Node node){
        if( node == currentNode ){
            next();
        }
        node.getPrevious().setNext(node.getNext());
        node.getNext().setPrevious(node.getPrevious());
        nodeCount--;
    }
    public void deleteCurrentNode(){
        currentNode.getPrevious().setNext(currentNode.getNext());
        currentNode.getNext().setPrevious(currentNode.getPrevious());
        currentNode.setRemainingTime(0);
        currentNode = currentNode.getNext(direction);
        currentNode.setRemainingTime(currentNode.getReflexTime()+1);
        nodeCount--;
    }
    private void addNode(Node node,int index,int reflex){
        Node newNode = new Node(index,node.getPrevious(),node,reflex);
        node.setPrevious(newNode);
        newNode.getPrevious().setNext(newNode);
        nodeCount++;
    }

    public void addNode(int index,int reflex){
        if(direction == 0) addNodeBeforeCurrent(index,reflex);
        else addNodeAfterCurrent(index,reflex);
    }
    private void addNodeBeforeCurrent(int index,int reflex){
        Node newNode = new Node(index,currentNode.getPrevious(),currentNode,reflex);
        currentNode.setPrevious(newNode);
        newNode.getPrevious().setNext(newNode);
        nodeCount++;
    }
    private void addNodeAfterCurrent(int index,int reflex){
        Node newNode = new Node(index,currentNode,currentNode.getNext(),reflex);
        currentNode.setNext(newNode);
        newNode.getNext().setPrevious(newNode);
        nodeCount++;
    }

    public void next(){
        currentNode.decrease();
      //  System.out.println(" currently at "+currentNode.getId()+" "+currentNode.getRemainingTime()+" "+currentNode.getReflexTime());
        if( currentNode.getRemainingTime() <= 0 ){
            currentNode = currentNode.getNext(direction);
            currentNode.reset();
        }

    }

    public Node getCurrentNode(){
        return currentNode;
    }

    public int getNodeCount(){
        return nodeCount;
    }
    public void changeDirection(){
        direction = 1-direction;
    }

    public void printSequence(){
        Node node = currentNode;
        for(int i=0;i<nodeCount;i++){
            System.out.print( node.getId()+", ");
            node = node.getNext(direction);

        }
        System.out.println("\b\b ");
    }

}
