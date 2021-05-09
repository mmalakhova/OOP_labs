package ru.nsu.ccfit.malakhova.commandcreator;

import ru.nsu.ccfit.malakhova.*;
import java.io.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.*;

public class CommandFactory {
    private Map<String, Class> commands = new HashMap<String, Class>();
    private ClassIdentifier agent = new ClassIdentifier();

    public CommandInterface create(String name) throws IOException, ClassNotFoundException, InvocationTargetException,
            InstantiationException, IllegalAccessException, NoSuchMethodException {
        if(!commands.containsKey(name)){
            commands.put(name, Class.forName(agent.find(name)));
        }

        Class object = commands.get(name);
        Constructor constructor = (Constructor)object.getConstructor();
        return (CommandInterface)constructor.newInstance();
    }
}
