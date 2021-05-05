package ru.nsu.ccfit.malakhova;

public class Parser {
    private String commandName;
    private String[] commandArgs;

    public String getName() {return this.commandName;}
    public String[] getArgs() {return this.commandArgs;}

    public Parser(String command){
        String[] strings = command.split(" ");
        this.commandName = strings[0];

        String[] newSt = new String[strings.length - 1];
        System.arraycopy(strings, 1, newSt, 0, strings.length - 1);
        this.commandArgs = newSt;
    }


}
