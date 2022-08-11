package com.efimchick.tasks.figures;

//TODO
class Quadrilateral extends Figure {
    private Point vertexA;
    private Point vertexB;
    private Point vertexC;
    private Point vertexD;

    public Quadrilateral(Point vertexA, Point vertexB, Point vertexC, Point vertexD) {
        Triangle triangleABC = new Triangle(vertexA, vertexB, vertexC);
        Triangle triangleCDA = new Triangle(vertexC, vertexD, vertexA);
        Triangle triangleBCD = new Triangle(vertexB, vertexC, vertexD);
        Triangle triangleDAB = new Triangle(vertexD, vertexA, vertexB);
        if (triangleABC.calculateDeterminant() * triangleCDA.calculateDeterminant() < 0 ||
                triangleBCD.calculateDeterminant() * triangleDAB.calculateDeterminant() < 0) {
            throw new RuntimeException("Figure with such vertices is degenerative or non-convex");
        }
        this.vertexA = vertexA;
        this.vertexB = vertexB;
        this.vertexC = vertexC;
        this.vertexD = vertexD;
    }

    @Override
    public double area() {
        Triangle triangleABC = new Triangle(vertexA, vertexB, vertexC);
        Triangle triangleADC = new Triangle(vertexA, vertexD, vertexC);
        return triangleABC.area() + triangleADC.area();
    }

    @Override
    public Point centroid() {
        Triangle triangleABC = new Triangle(vertexA, vertexB, vertexC);
        Triangle triangleADC = new Triangle(vertexA, vertexD, vertexC);
        return new Point((triangleABC.centroid().getX() * triangleABC.area() +
                triangleADC.centroid().getX() * triangleADC.area()) / area(),
                (triangleABC.centroid().getY() * triangleABC.area() +
                        triangleADC.centroid().getY() * triangleADC.area()) / area());
    }

    private boolean isVertexContained(Point vertex) {
        return (vertex.isTheSame(vertexA) || vertex.isTheSame(vertexB)
                || vertex.isTheSame(vertexC) || vertex.isTheSame(vertexD));
    }

    @Override
    public boolean isTheSame(Figure figure) {
        return figure instanceof Quadrilateral && ((Quadrilateral) figure).isVertexContained(vertexA) &&
                ((Quadrilateral) figure).isVertexContained(vertexB) &&
                ((Quadrilateral) figure).isVertexContained(vertexC) &&
                ((Quadrilateral) figure).isVertexContained(vertexD);
    }

    @Override
    public String toString() {
        return "Quadrilateral[(" + vertexA.getX() + "," + vertexA.getY() + ")(" + vertexB.getX() + "," + vertexB.getY() + ")("
                + vertexC.getX() + "," + vertexC.getY() + ")(" + vertexD.getX() + "," + vertexD.getY() + ")]";
    }

    @Override
    double getXOfLeftMostVertex() {
        return Math.min(Math.min(vertexA.getX(), vertexB.getX()), Math.min(vertexC.getX(), vertexD.getX()));
    }

}
