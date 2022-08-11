package com.efimchick.tasks.figures;

//TODO
class Triangle extends Figure {
    private Point vertexA;
    private Point vertexB;
    private Point vertexC;

    public Triangle(Point vertexA, Point vertexB, Point vertexC) {
        this.vertexA = vertexA;
        this.vertexB = vertexB;
        this.vertexC = vertexC;
        if (this.area() == 0) {
            throw new RuntimeException("Figure with such vertices is degenerative");
        }
    }

    double calculateDeterminant() {
        return (vertexA.getX() - vertexC.getX()) * (vertexB.getY() - vertexC.getY()) -
                (vertexA.getY() - vertexC.getY()) * (vertexB.getX() - vertexC.getX());
    }

    @Override
    public double area() {
        return Math.abs(calculateDeterminant()) / 2;
    }

    @Override
    public Point centroid() {
        return new Point((vertexA.getX() + vertexB.getX() + vertexC.getX()) / 3, (vertexA.getY() + vertexB.getY() + vertexC.getY()) / 3);
    }

    private boolean isVertexContained(Point vertex) {
        return (vertex.isTheSame(vertexA) || vertex.isTheSame(vertexB)
                || vertex.isTheSame(vertexC));
    }

    @Override
    public boolean isTheSame(Figure figure) {
        return figure instanceof Triangle && ((Triangle) figure).isVertexContained(vertexA)
                && ((Triangle) figure).isVertexContained(vertexB) && ((Triangle) figure).isVertexContained(vertexC);
    }

    @Override
    public String toString() {
        return "Triangle[(" + vertexA.getX() + "," + vertexA.getY() + ")(" + vertexB.getX() + "," + vertexB.getY() + ")("
                + vertexC.getX() + "," + vertexC.getY() + ")]";
    }

    @Override
    double getXOfLeftMostVertex() {
        return Math.min(Math.min(vertexA.getX(), vertexB.getX()), vertexC.getX());
    }


}
