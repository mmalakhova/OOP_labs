package ru.nsu.ccfit.malakhova.commandcreator.commands;

import org.junit.Test;
import ru.nsu.ccfit.malakhova.area.Position;
import ru.nsu.ccfit.malakhova.area.Field;

import static org.junit.Assert.*;

public class InitTest {
    @Test(expected= IllegalArgumentException.class)
    public void initTest(){
        Field field = new Field();
        Init init = new Init();
        String[] args = {"f", "f", "f", "f"};
        init.execute(args, field);
    }
    @Test(expected = IllegalStateException.class)
    public void initTest2(){
        Field field = new Field();
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        Init init = new Init();
        String[] args = {"2", "2", "0", "0"};
        init.execute(args, field);
    }
}