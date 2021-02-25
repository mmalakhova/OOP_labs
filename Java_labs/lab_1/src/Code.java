import java.io.*;

class Code implements Handler{
    public void secret(InputStreamReader file, MorseABC abc) {
        StatisticGen stat = new StatisticGen();
        int ch;
        Writer ou = null;

        try {
             ou = new OutputStreamWriter(new FileOutputStream("morse_coded.txt"));
            while((ch = file.read()) != -1){
                ch = Character.toUpperCase(ch);
                stat.makeNote((char)ch);
                //if (ch == 0) continue;
                if(ch == ' '){
                    ou.write("      ", 0, 6);
                }
                else if(ch == '\n'){
                    String str = System.lineSeparator() + " ";
                    ou.write(str, 0, str.length());
                }
                else{
                    String str = abc.code((char)ch) + " ";
                    ou.write(str, 0, str.length());
                }
            }
            stat.printToFile();
        }
        catch (IOException e){
               System.err.println("Error while writing file: " + e.getLocalizedMessage());
        }
        finally {
            if (null != ou) {
                try {
                    ou.close();
                }
                catch (IOException e) {
                    e.printStackTrace(System.err);
                }
            }
        }

    }
}
