package ru.nsu.ccfit.malakhova.area;

import org.junit.Test;

import static org.junit.Assert.*;

public class FieldTest {
    @Test
    public void isExistTest(){
        Field field = new Field();
        assertTrue(!field.isExist());
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        assertTrue(field.isExist());
    }

    @Test
    public void isDrawTest(){
        Field field = new Field();
        assertTrue(!field.getDrawState());
        field.setDraw(true);
        assertTrue(field.getDrawState());
        field.setDraw(false);
        assertTrue(!field.getDrawState());
    }

    @Test(expected = IllegalArgumentException.class)
    public void setGetPlayerPosCreateTest(){
        Field field = new Field();
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        assertEquals(field.getFieldSize().getX(), size.getX());
        assertEquals(field.getFieldSize().getY(), size.getY());
        pos.setX(0);
        pos.setY(0);
        field.setPlayerPosition(pos);
        assertEquals(field.getPlayerPosition().getX(), pos.getX());
        assertEquals(field.getPlayerPosition().getY(), pos.getY());
        pos.setY(-10);
        field.setPlayerPosition(pos);
    }

    @Test
    public void positionMarkTest(){
        Field field = new Field();
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        Position pos2 = new Position();
        pos2.setX(2);
        pos2.setY(3);
        field.setPositionMark(pos2, true);
    }

    @Test
    public void compareTest(){
        Field field1 = new Field();
        Position pos1 = new Position();
        pos1.setX(0);
        pos1.setY(0);
        Position size1 = new Position();
        size1.setX(10);
        size1.setY(10);
        field1.createField(pos1, size1);

        Field field2 = new Field();
        Position pos2 = new Position();
        pos2.setX(0);
        pos2.setY(0);
        Position size2 = new Position();
        size2.setX(5);
        size2.setY(3);
        field2.createField(pos2, size2);

        Field field3 = new Field();
        Position pos3 = new Position();
        pos2.setX(0);
        pos2.setY(0);
        Position size3 = new Position();
        size3.setX(3);
        size3.setY(5);
        field3.createField(pos3, size3);

        assertEquals(field1.compareTo(field2), 1);
        assertEquals(field2.compareTo(field3), 0);
        assertEquals(field3.compareTo(field1),-1);
    }
}