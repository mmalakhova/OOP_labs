package ru.nsu.ccfit.malakhova.commandcreator;

import ru.nsu.ccfit.malakhova.area.Field;

public interface CommandInterface {
    public void execute(String[] args, Field field) throws IllegalArgumentException;
}
