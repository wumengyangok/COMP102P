package com.wumengyangok;

import com.sun.org.apache.regexp.internal.RE;

/**
 * Created by wumengyang on 31/01/2016.
 */
public class BinarySearchTree {
    private BinaryTreeNode root;

    public BinarySearchTree() {
        this.root = null;
    }

    public BinarySearchTree(BinaryTreeNode root) {
        this.root = root;
    }

    private BinaryTreeNode findMin(BinaryTreeNode search) {
        while (search.getLeft() != null) {
            search = search.getLeft();
        }
        return search;
    }

    private BinaryTreeNode findMax(BinaryTreeNode search) {
        while (search.getRight() != null) {
            search = search.getRight();
        }
        return search;
    }

    private BinaryTreeNode succ(BinaryTreeNode search) {
        if (search.getRight() != null)
            return findMin(search.getRight());
        else {
            while (search == search.getFather().getRight()) {
                search = search.getFather();
                if (search.getFather() == null)
                    return null;
            }
            return search.getFather();
        }
    }

    private BinaryTreeNode prev(BinaryTreeNode search) {
        if (search.getLeft() != null)
            return findMax(search.getLeft());
        else {
            while (search == search.getFather().getLeft()) {
                search = search.getFather();
                if (search.getFather() == null)
                    return null;
            }
            return search.getFather();
        }
    }

    private BinaryTreeNode search(int key) {
        BinaryTreeNode search = this.root;
        while (search != null) {
            if (search.getElement() == key)
                return search;
            else if (search.getElement() > key)
                search = search.getLeft();
            else
                search = search.getRight();
        }
        return null;
    }

    private void insert(int key, BinaryTreeNode search) {
        if (key < search.getElement()) {
            if (search.getLeft() == null) {
                search.setLeft(new BinaryTreeNode(null, null, search, key));
            } else {
                insert(key, search.getLeft());
            }
        } else {
            if (search.getRight() == null) {
                search.setRight(new BinaryTreeNode(null, null, search, key));
            } else {
                insert(key, search.getRight());
            }
        }
    }

    private void delete(int key, BinaryTreeNode search) {
        BinaryTreeNode temp;
        if ((search.getLeft() == null)||(search.getRight() == null)) {
            if (search.getLeft() != null)
                temp = search.getLeft();
            else
                temp = search.getRight();
            if (search.getFather().getLeft() == search)
                search.getFather().setLeft(temp);
            else
                search.getFather().setRight(temp);
            if (temp != null) {
                temp.setFather(search.getFather());
            }
        } else {
            temp = succ(search);
            search.setElement(temp.getElement());
            delete(temp.getElement(),temp);
        }
    }

    public boolean delete(int key) {
        if (contains(key)) {
            delete(key, search(key));
            return true;
        } else
            return false;
    }

    public void insert(int key) {
        if (this.root == null) {
            this.root = new BinaryTreeNode(null, null, null, key);
        } else {
            insert(key, this.root);
        }
    }

    public boolean contains(int key) {
        BinaryTreeNode search = this.root;
        while (search != null) {
            if (search.getElement() == key)
                return true;
            else if (search.getElement() > key)
                search = search.getLeft();
            else
                search = search.getRight();
        }
        return false;
    }


}
