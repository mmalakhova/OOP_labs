package ru.nsu.ccfit.malakhova.commandcreator.commands;

import ru.nsu.ccfit.malakhova.area.Field;
import ru.nsu.ccfit.malakhova.area.Position;
import ru.nsu.ccfit.malakhova.commandcreator.CommandInterface;

import java.util.logging.Logger;

public class Init implements CommandInterface {
    private static final Logger logger = Logger.getLogger(Init.class.getName());

    public void execute(String[] args, Field field) throws IllegalArgumentException{
        if(field.isExist()) throw new IllegalStateException("There is no need in another field :)");
        if(args.length != 4) throw new IllegalArgumentException("Bad input...");

        Position fieldSize = new Position();
        fieldSize.setX(Integer.parseInt(args[0]));
        fieldSize.setY(Integer.parseInt(args[1]));

        Position playerPos = new Position();
        playerPos.setX(Integer.parseInt(args[2]));
        playerPos.setY(Integer.parseInt(args[3]));

        field.createField(playerPos, fieldSize);
        logger.setUseParentHandlers(false);
        logger.info("Field created");
        logger.info("AE created");
    }
}
