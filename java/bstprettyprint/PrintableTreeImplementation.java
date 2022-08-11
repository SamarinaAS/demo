package com.epam.rd.autocode.bstprettyprint;

public class PrintableTreeImplementation implements PrintableTree {
    private Node root;
    private String printableTree;
    private int endOfLineCounter;
    private int previousLineStart;
    private int currentLineStart;


    private class Node {
        private int value;
        private Node left;
        private Node right;

        public Node(int value) {
            this.value = value;
        }

        public Node() {
        }
    }

    private Node add(Node node, int i) {
        if (node == null) {
            return new Node(i);
        }
        if (i < node.value) {
            node.left = add(node.left, i);
        } else if (i > node.value) {
            node.right = add(node.right, i);
        }
        return node;
    }


    @Override
    public void add(int i) {
        root = add(root, i);
    }

    @Override
    public String prettyPrint() {
        printableTree = null;
        print(root, 0, 0);
        printableTree += "\n";
        return printableTree;
    }

    private void print(Node root, int space, int leftOrRight) {

        if (root == null)
            return;

        space += Integer.toString(root.value).length() + 1;

        print(root.left, space, 1);

        previousLineStart = currentLineStart;
        if (printableTree == null) {
            printableTree = "";
            currentLineStart = 0;
        } else {
            printableTree += "\n";
            endOfLineCounter++;
            currentLineStart = printableTree.length();
        }

        for (int i = Integer.toString(root.value).length(); i < space - 1; i++) {
            if (i != space - 2) {
                boolean isSpace = true;
                if (endOfLineCounter != 0) {
                    int index = printableTree.length() - currentLineStart;
                    int previousLineIndex = previousLineStart + index;
                    if (previousLineIndex < currentLineStart) {
                        char upper = printableTree.charAt(previousLineIndex);
                        if (upper == '│' || upper == '┌' || upper == '┐' || upper == '┤') {
                            isSpace = false;
                        }
                    }
                }
                printableTree += isSpace ? " " : "│";
            } else {
                if (leftOrRight == 1) {
                    printableTree += "┌";
                } else if (leftOrRight == -1) {
                    printableTree += "└";
                }

            }
        }
        printableTree += Integer.toString(root.value);
        if (root.right != null && root.left != null) {
            printableTree += "┤";
        } else if (root.right != null) {
            printableTree += "┐";
        } else if (root.left != null) {
            printableTree += "┘";
        }

        print(root.right, space, -1);
    }
}
