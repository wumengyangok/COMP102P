package com.wumengyangok;

/**
 * Created by wumengyang on 31/01/2016.
 */
public class BinaryTreeNode {
    private BinaryTreeNode left;
    private BinaryTreeNode right;
    private BinaryTreeNode father;
    private int element;

    public BinaryTreeNode(BinaryTreeNode left, BinaryTreeNode right, BinaryTreeNode father, int element) {
        this.left = left;
        this.right = right;
        this.element = element;
        this.father = father;
    }

    public BinaryTreeNode getLeft() {
        return left;
    }

    public BinaryTreeNode getRight() {
        return right;
    }

    public int getElement() {
        return element;
    }

    public BinaryTreeNode getFather() {
        return father;
    }

    public void setLeft(BinaryTreeNode left) {
        this.left = left;
    }

    public void setElement(int element) {
        this.element = element;
    }

    public void setFather(BinaryTreeNode father) {
        this.father = father;
    }

    public void setRight(BinaryTreeNode right) {
        this.right = right;
    }
}
