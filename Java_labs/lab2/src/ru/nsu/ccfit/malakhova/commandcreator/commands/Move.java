package ru.nsu.ccfit.malakhova.commandcreator.commands;

import ru.nsu.ccfit.malakhova.area.Field;
import ru.nsu.ccfit.malakhova.area.Position;
import ru.nsu.ccfit.malakhova.commandcreator.CommandInterface;

import java.awt.*;
import java.util.logging.Logger;

public class Move implements CommandInterface {
    private static final Logger logger = Logger.getLogger(Move.class.getName());

    public void execute(String[] args, Field field) throws IllegalArgumentException{
        if (!field.isExist()) throw new IllegalStateException("Oh, no... there is no field...");
        if (args.length != 2) throw new IllegalArgumentException("Bad input");
        int stepCount = Integer.parseInt(args[1]);
        if (stepCount < 0) throw new IllegalArgumentException("Bad input");

        Position playerPos = field.getPlayerPosition();
        Position fieldSize = field.getFieldSize();
        boolean draw = field.getDrawState();

        switch (args[0]) {
            case "L":
                for (int i = 0; i < stepCount; i++) {
                    if (draw) field.setPositionMark(playerPos, true);

                    playerPos.setX((playerPos.getX()) - 1);
                    if (playerPos.getX() < 0) playerPos.setX((fieldSize.getX()) - 1);
                }
                break;
            case "R":
                for (int i = 0; i < stepCount; i++) {
                    if (draw) field.setPositionMark(playerPos, true);

                    playerPos.setX((playerPos.getX()) + 1);
                    if (playerPos.getX() == fieldSize.getX()) playerPos.setX(0);
                }
                break;
            case "U":
                for (int i = 0; i < stepCount; i++) {
                    if (draw) field.setPositionMark(playerPos, true);

                    playerPos.setY((playerPos.getY()) - 1);
                    if (playerPos.getY() < 0) playerPos.setY((fieldSize.getY()) - 1);
                }
                break;
            case "D":
                for (int i = 0; i < stepCount; i++) {
                    if (draw) field.setPositionMark(playerPos, true);

                    playerPos.setY((playerPos.getY()) + 1);
                    if (playerPos.getY() == fieldSize.getY()) playerPos.setY(0);
                }
                break;
            default:
                throw new IllegalArgumentException("Bad way arg!");
        }
        logger.info("AE MOVE TO " + args[0] + " by " + stepCount + " steps");
    }
}
