package ru.nsu.ccfit.malakhova.area;

public class Field implements Comparable<Field> {
    private boolean[][] field = null;
    private boolean draw = false;
    private boolean exist = false;
    private Position fieldSize = null;
    private Position playerPosition = null;

    public boolean isExist(){ return this.exist; }
    public boolean getDrawState(){ return this.draw; }
    public Position getPlayerPosition(){ return this.playerPosition; }
    public Position getFieldSize(){ return this.fieldSize; }

    public void setPlayerPosition(Position newPosition) throws IllegalArgumentException{
        if (newPosition.getX() < 0 || newPosition.getY() < 0 || newPosition.getX() > this.fieldSize.getX() - 1 || newPosition.getY() > this.fieldSize.getY() - 1) throw new IllegalArgumentException("Incorrect coordinates...");
        this.playerPosition = newPosition;
    }

    public void setPositionMark(Position position, boolean mark){
        this.field[position.getX()][position.getY()] = mark;
    }

    public void setDraw(boolean mark){
        this.draw = mark;
    }

    public void createField(Position playerPosition, Position fieldSize) throws IllegalArgumentException{
        this.playerPosition = playerPosition;
        this.fieldSize = fieldSize;
        if ( this.fieldSize.getX() <= 0 || this.fieldSize.getY() <= 0) throw new IllegalArgumentException("Incorrect field size...");
        if (this.playerPosition.getX() < 0 || this.playerPosition.getY() < 0 || this.playerPosition.getX() > this.fieldSize.getX() - 1 || this.playerPosition.getY() > this.fieldSize.getY() - 1) throw new IllegalArgumentException("Incorrect coordinates...");


        this.field = new boolean[this.fieldSize.getX()][this.fieldSize.getY()];
        this.exist = true;
    }

    public void printField(){
        for (int i = 0; i < this.fieldSize.getX(); i++){
            for ( int j = 0; j < this.fieldSize.getY(); j++){
                if (this.playerPosition.getX() == i && this.playerPosition.getY() == j){ System.out.print(" P");}
                else if (field[i][j]) System.out.print(" #");
                else System.out.print(" _");
            }
            System.out.print("\n\n");
        }
    }


    @Override
    public int compareTo(Field f){
        Position pos = f.getFieldSize();
        if (this.fieldSize.getX() * this.fieldSize.getY() > pos.getX() * pos.getY()) return 1;
        else if(this.fieldSize.getX() * this.fieldSize.getY() < pos.getX() * pos.getY()) return -1;
        else return 0;
    }
}
