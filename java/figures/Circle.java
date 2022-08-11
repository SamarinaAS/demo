package com.efimchick.tasks.figures;

class Circle extends Figure {
    private double radius;
    private Point center;

    public Circle(Point center, double radius) {
        if (radius <= 0 || center == null) {
            throw new RuntimeException("A circle with such vertices is degenerative");
        }
        this.radius = radius;
        this.center = center;

    }

    @Override
    public double area() {
        return Math.PI * radius * radius;
    }

    @Override
    public Point centroid() {
        return center;
    }

    @Override
    public boolean isTheSame(Figure figure) {

        return figure instanceof Circle && Math.abs(radius - ((Circle) figure).radius) < Point.DELTA
                && center.isTheSame(((Circle) figure).center);
    }

    @Override
    public String toString() {
        return "Circle[(" + center.getX() + "," + center.getY() + ")" + radius + "]";
    }

    @Override
    double getXOfLeftMostVertex() {
        return center.getX() - radius;
    }

}
