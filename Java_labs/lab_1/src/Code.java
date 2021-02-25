import java.io.*;

class Code implements Handler{
    Code(){}
    public void secret(InputStreamReader file, MorseABC abc) {
        Statistic stat = new Statistic();
        int ch;
        try
                (
                        Writer ou = new OutputStreamWriter(new FileOutputStream("init.decode"))
                )
        {
            while((ch = file.read()) != -1){
                ch = Character.toUpperCase(ch);
                stat.makeNote((char)ch);
                if(ch == ' '){
                    ou.write("      ", 0, 6);
                }
                else if(ch == '\n'){
                    String str = abc.getCode('$') + " ";
                    ou.write(str, 0, str.length());
                }
                else{
                    String str = abc.getCode((char)ch) + " ";
                    ou.write(str, 0, str.length());
                }
            }
            stat.printToFile();
        }
        catch (IOException e){
            System.err.println("Error while writing file: " + e.getLocalizedMessage());
        }

    }
}
