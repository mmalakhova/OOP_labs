package ru.nsu.ccfit.malakhova.commandcreator;

import ru.nsu.ccfit.malakhova.ClassIdentifier;
import java.io.*;
import java.util.*;

public class CommandFactory {
    private Map<String, Class> commands = new HashMap<String, Class>();
    private ClassIdentifier agent = new ClassIdentifier();

    public CommandInterface create(String name) throws IOException, ClassNotFoundException {
        Object command;
        if(!commands.containsKey(name)){
            commands.put(name, Class.forName(agent.find(name)));
        }

        command = commands.get(name);
        return (CommandInterface)command;
    }

}
