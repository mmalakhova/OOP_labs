package ru.nsu.ccfit.malakhova.commandcreator.commands;

import ru.nsu.ccfit.malakhova.area.Field;
import ru.nsu.ccfit.malakhova.commandcreator.CommandInterface;

import java.util.logging.Logger;

public class Ward implements CommandInterface {
    private static final Logger logger = Logger.getLogger(Ward.class.getName());

    public void execute(String[] args, Field field) throws IllegalArgumentException{
        if(!field.isExist()) throw new IllegalArgumentException("there is no field...");
        if( args.length > 0) throw new IllegalArgumentException("Too many arguments...");
        field.setDraw(false);
        logger.setUseParentHandlers(false);
        logger.info("Field draw is FALSE now...");
    }
}
