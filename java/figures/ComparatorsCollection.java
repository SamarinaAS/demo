package com.efimchick.tasks.figures;

public class ComparatorsCollection {

    //TODO
    public static int compareByArea(Figure lhs, Figure rhs) {

        if (Math.abs(lhs.area() - rhs.area()) < Point.DELTA) {
            return 0;
        } else if ((lhs.area() - rhs.area()) < 0) {
            return -1;
        } else {
            return 1;
        }
    }

    //TODO
    public static int compareByHorizontalStartPosition(Figure lhs, Figure rhs) {
        if (Math.abs(lhs.getXOfLeftMostVertex() - rhs.getXOfLeftMostVertex()) < Point.DELTA) {
            return 0;
        } else if ((lhs.getXOfLeftMostVertex() - rhs.getXOfLeftMostVertex()) < 0) {
            return -1;
        } else {
            return 1;
        }
    }

    //TODO
    public static int compareByHorizontalCenterPosition(Figure lhs, Figure rhs) {
        if (Math.abs(lhs.centroid().getX() - rhs.centroid().getX()) < Point.DELTA) {
            return 0;
        } else if ((lhs.centroid().getX() - rhs.centroid().getX()) < 0) {
            return -1;
        } else {
            return 1;
        }
    }
}
