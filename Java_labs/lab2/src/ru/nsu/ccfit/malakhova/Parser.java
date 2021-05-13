package ru.nsu.ccfit.malakhova;

public class Parser {
    private final String commandName;
    private final String[] commandArgs;

    public String getName() {return this.commandName;}
    public String[] getArgs() {return this.commandArgs;}

    public Parser(String command){
        String[] strings = command.split(" ");
        this.commandName = strings[0];

        String[] newSt = new String[strings.length - 1];

        for(int i = 0; i < strings.length - 1; i++){
            newSt[i] = strings[i + 1];
        }
        //System.arraycopy(strings, 1, newSt, 0, strings.length - 1);
        this.commandArgs = newSt;
    }


}
