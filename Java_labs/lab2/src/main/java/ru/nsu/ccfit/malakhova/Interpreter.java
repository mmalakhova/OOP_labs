package ru.nsu.ccfit.malakhova;

import ru.nsu.ccfit.malakhova.area.Field;
import ru.nsu.ccfit.malakhova.commandcreator.CommandFactory;
import ru.nsu.ccfit.malakhova.commandcreator.CommandInterface;

import java.lang.reflect.InvocationTargetException;
import java.util.logging.*;
import java.io.*;
import java.util.*;

public class Interpreter {
    private static final Logger logger = Logger.getLogger(Interpreter.class.getName());

    public static  void main(String[] argv){
        logger.info("Start execution...");
        Field field = new Field();
        CommandFactory factory = new CommandFactory();
        Scanner scan = new Scanner(System.in);

        while(true){
            try{
                logger.info("Receiving command");
                Parser parser = new Parser(scan.nextLine());
                logger.info("Parsing command");
                if(parser.getName().equals("END")){
                    logger.info("Execution finished");
                    return;
                }
                logger.info("Creating command object");
                CommandInterface command = factory.create(parser.getName());
                logger.info("Command created");
                logger.info("Run command!");
                command.execute(parser.getArgs(), field);
                logger.info("Command finished!");
                logger.info("Start printing field!");
                field.printField();
                logger.info("Printing completed!");
            }
            catch(IllegalArgumentException e){
                logger.warning(e.getMessage());
                System.out.println(e.getMessage());
            }
            catch (IOException exception) {
                exception.printStackTrace();
            }
            catch (ClassNotFoundException e) {
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                e.printStackTrace();
            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
            }
        }

    }

}
