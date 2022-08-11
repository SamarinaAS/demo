package com.efimchick.tasks.figures;

class Point {
    private double x;
    private double y;
    static final double DELTA = 0.000000001;

    public Point(final double x, final double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public boolean isTheSame(Point point) {
        return Math.abs(point.x - this.x) < DELTA && Math.abs(point.y - this.y) < DELTA;
    }

}
