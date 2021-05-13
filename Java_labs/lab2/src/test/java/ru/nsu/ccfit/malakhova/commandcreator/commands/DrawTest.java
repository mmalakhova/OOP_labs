package ru.nsu.ccfit.malakhova.commandcreator.commands;

import org.junit.Test;
import ru.nsu.ccfit.malakhova.area.*;
import static org.junit.Assert.*;

public class DrawTest {
    @Test
    public void isDrawTest(){
        String[] arr = new String[0];
        Draw dr = new Draw();
        Init init = new Init();
        Field field = new Field();
        String[] args = {"10","10", "1", "1"};
        init.execute(args, field);
        dr.execute(arr, field);
        Position pos = new Position();
        pos.setX(4);
        pos.setY(1);
        Position size = new Position();
        size.setX(7);
        size.setY(6);
        field.createField(pos, size);
        dr.execute(arr, field);
        assertTrue(field.getDrawState());
    }
}