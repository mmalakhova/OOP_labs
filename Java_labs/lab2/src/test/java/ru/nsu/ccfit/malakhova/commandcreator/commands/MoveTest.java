package ru.nsu.ccfit.malakhova.commandcreator.commands;

import org.junit.Test;
import ru.nsu.ccfit.malakhova.area.*;

import static org.junit.Assert.*;

public class MoveTest {
    @Test(expected = IllegalStateException.class)
    public void stateExceptTest(){
        Move mv = new Move();
        Field field = new Field();
        String[] args = {"D", "10"};
        mv.execute(args, field);
    }

    @Test(expected = IllegalArgumentException.class)
    public void argsExceptTest(){
        Move mv = new Move();
        Field field = new Field();
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        String[] args = {"10"};
        mv.execute(args, field);
    }

    @Test
    public void moveTest(){
        Move mv = new Move();
        Field field = new Field();
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(10);
        size.setY(10);
        field.createField(pos, size);
        String[] args = {"D", "3"};
        mv.execute(args, field);
        assertEquals( 7,field.getPlayerPosition().getX());
    }
}