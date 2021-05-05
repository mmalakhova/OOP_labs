package ru.nsu.ccfit.malakhova;

import java.io.*;
import java.util.*;

public class ClassIdentifier {
    public String find(String name) throws IOException, NullPointerException{
        Properties prop = new Properties();
        String path = null;

//        try(InputStream stream = new FileInputStream("comm.config")) {
//            prop.load(stream);
//
//            for (String str : prop.stringPropertyNames()) {
//                if (str.equals(name)) {
//                    path = prop.getProperty(str);
//                    break;
//                }
//            }
//        }
        try(InputStream inp = ClassLoader.getSystemResourceAsStream("comm.config"))
        {
            if (inp == null) throw new IOException("Problems with config");
            prop.load(inp);
            for (String str : prop.stringPropertyNames()) {
                if (str.equals(name)) {
                    path = prop.getProperty(str);
                   break;
                }
            }
        }

        catch (IOException e){
            throw new IOException("Config error", e);
        }
        if (path == null) throw new NullPointerException("No such class!");

        return path;
    }

}
