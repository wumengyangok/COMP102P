package com.wumengyangok;

import java.util.LinkedList;

/**
 * Created by wumengyang on 26/02/2016.
 */
public class BTree {

    private int n;
    private int volume;
    BTree(int n) {
        this.n = n;
        this.volume = 0;
    }

    private class Page {
        private LinkedList<Integer> leaves;
        private Page father;
        private LinkedList<Page> children;
        private int minimumLeafNumber;
        private int maximumLeafNumber;

        Page(Page father, int min, int max) {
            this.father = father;
            this.minimumLeafNumber = min;
            this.maximumLeafNumber = max;
            leaves = new LinkedList<Integer>();
            children = new LinkedList<Page>();
        }

        public LinkedList<Integer> getLeaves() {
            return leaves;
        }

        public LinkedList<Page> getChildren() {
            return children;
        }

        public int addValue(int value) {
            int index = 0;
            while (index < leaves.size() && leaves.get(index) < value)
                index++;
            leaves.add(index, value);
            return index + 1;
        }

        public void addChildren(Page child, int index) {
            children.add(index, child);
            if (child != null)
                child.setFather(this);
        }

        public boolean ifOverflew() {
            return leaves.size() > maximumLeafNumber;
        }

        public Page getFather() {
            return father;
        }

        public void setFather(Page father) {
            this.father = father;
        }
    }

    private Page root;

    private void split(Page page) {

        Page father = page.getFather();
        LinkedList<Integer> leaves = page.getLeaves();
        LinkedList<Page> children = page.getChildren();
        if (father == null) {
            root = new Page(null, 0, 2 * n);
            father = root;
        }
        int index = father.addValue(page.getLeaves().get(n));
        Page left = new Page(father, n, 2 * n);
        for (int i = 0; i < n; i++) {
            left.addChildren(children.get(i), left.addValue(leaves.get(i)) - 1);
        }
        left.addChildren(children.get(n), n);
        Page right = new Page(father, n, 2 * n);
        for (int i = n + 1; i < 2 * n + 1; i++) {
            right.addChildren(children.get(i), right.addValue(leaves.get(i)) - 1);
        }
        right.addChildren(children.get(2 * n + 1), n);
        father.addChildren(left, index - 1);
        father.addChildren(right, index);

        if (father.ifOverflew())
            split(father);
    }

    public boolean search(int key) {
        Page search = root;
        while (search != null) {
            LinkedList<Integer> leaves = search.getLeaves();
            int index = 0;
            while (key < leaves.get(index)) {
                index++;
            }

            if (key == leaves.get(index))
                return true;
            else
                search = search.getChildren().get(index);
        }
        return false;
    }

    public void add(int key) {

        if (volume == 0) {
            root = new Page(null, 0, 2 * n);
            root.addValue(key);
            root.addChildren(null, 0);
            root.addChildren(null, 1);
            volume++;
        } else {
            if (search(key))
                return;
            volume++;
            Page search = root;
            while (search.children.get(0) != null) {
                LinkedList<Integer> leaves = search.getLeaves();
                int index = 0;
                while (index < leaves.size() && key > leaves.get(index))
                    index++;
                search = search.getChildren().get(index);
            }
            search.addChildren(null, search.addValue(key));
            if (search.ifOverflew())
                split(search);
        }
    }


}
