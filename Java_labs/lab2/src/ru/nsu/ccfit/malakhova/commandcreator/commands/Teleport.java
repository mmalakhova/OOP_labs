package ru.nsu.ccfit.malakhova.commandcreator.commands;

import ru.nsu.ccfit.malakhova.area.Field;
import ru.nsu.ccfit.malakhova.area.Position;

import java.util.logging.Logger;

public class Teleport {
    private static final Logger logger = Logger.getLogger(Teleport.class.getName());

    public void execute(String[] args, Field field) throws IllegalArgumentException{
        if (!field.isExist()) throw new IllegalStateException("Oops, there is no field...");
        if (args.length != 2) throw new IllegalArgumentException("Bad input");
        Position newPosition = new Position();

        newPosition.setX(Integer.parseInt(args[0]));
        newPosition.setY(Integer.parseInt(args[1]));

        field.setPlayerPosition(newPosition);
        logger.info("AE TELEPORT to X: " + args[0] + " Y: " + args[1]);
    }
}
