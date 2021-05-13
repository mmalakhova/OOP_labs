package ru.nsu.ccfit.malakhova;

import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class ClassIdentifierTest {
    @Test(expected = NullPointerException.class)
    public void findTest() throws IOException {
        ClassIdentifier agent = new ClassIdentifier();
        String name = "INIT";
        String path = agent.find(name);
        assertEquals(path, "ru.nsu.ccfit.malakhova.commandcreator.commands.Init");
        name = "INit";
        agent.find(name);
    }
}