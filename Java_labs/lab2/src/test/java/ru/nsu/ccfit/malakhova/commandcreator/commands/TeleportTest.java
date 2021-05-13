package ru.nsu.ccfit.malakhova.commandcreator.commands;

import org.junit.Test;
import ru.nsu.ccfit.malakhova.area.*;

import static org.junit.Assert.*;

public class TeleportTest {
    @Test(expected = IllegalArgumentException.class)
    public void telepTest(){
        Field field = new Field();
        Teleport tele = new Teleport();
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        String[] args = {"f", "y"};
        tele.execute(args, field);
    }

    @Test(expected = IllegalStateException.class)
    public void telepTest2(){
        Field field = new Field();
        Teleport tele = new Teleport();
        String[] args = {"2", "2"};
        tele.execute(args, field);
    }
}