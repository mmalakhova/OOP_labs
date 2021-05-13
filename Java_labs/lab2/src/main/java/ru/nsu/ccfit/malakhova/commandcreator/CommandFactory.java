package ru.nsu.ccfit.malakhova.commandcreator;

import ru.nsu.ccfit.malakhova.ClassIdentifier;
import java.io.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.*;

public class CommandFactory {
    private final Map<String, Class<?>> commands = new HashMap<>();
    private final ClassIdentifier agent = new ClassIdentifier();

    public CommandInterface create(String name) throws IOException, ClassNotFoundException, InvocationTargetException,
            InstantiationException, IllegalAccessException, NoSuchMethodException {
        if(!commands.containsKey(name)){
            commands.put(name, Class.forName(agent.find(name)));
        }

        Class<?> object = commands.get(name);
        Constructor<?> constructor = object.getConstructor();
        return (CommandInterface)constructor.newInstance();
    }
}
