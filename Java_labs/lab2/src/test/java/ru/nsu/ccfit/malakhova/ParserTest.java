package ru.nsu.ccfit.malakhova;

import org.junit.Test;

import static org.junit.Assert.*;

public class ParserTest {
    @Test
    public void parseGetSetTest(){
        String command = "MOVE U 10";
        Parser tr = new Parser(command);
        assertEquals(tr.getName(), "MOVE");
        assertEquals((tr.getArgs())[0], "U");
        assertEquals((tr.getArgs())[1], "10");
    }
}