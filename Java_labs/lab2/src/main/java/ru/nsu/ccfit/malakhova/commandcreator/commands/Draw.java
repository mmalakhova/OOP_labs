package ru.nsu.ccfit.malakhova.commandcreator.commands;

import ru.nsu.ccfit.malakhova.area.Field;
import ru.nsu.ccfit.malakhova.commandcreator.CommandInterface;
import java.util.logging.Logger;

public class Draw implements CommandInterface {
    private static final Logger logger = Logger.getLogger(Draw.class.getName());

    public void execute(String[] args, Field field) throws IllegalArgumentException{
        if(!field.isExist()) throw new IllegalArgumentException("there is no field...");
        if( args.length > 0) throw new IllegalArgumentException("Too many arguments...");
        field.setDraw(true);
        logger.setUseParentHandlers(false);
        logger.info("Field draw is TRUE now");
    }
}
