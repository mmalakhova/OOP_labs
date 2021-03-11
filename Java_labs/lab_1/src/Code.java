import java.io.*;


class Code implements Handler{
    public void secret(InputStreamReader file, MorseABC abc) {
        StatisticGen stat = new StatisticGen();
        int ch;
        Writer ou = null;

//TODO: ДОБАВИТЬ ПРОВЕРКУ НА ПОСЛДЕНИЙ СИМВОЛ В СТРОКЕ
//TODO: ЗАМЕРИТЬ ВРЕМЯ РАБОТЫ(HASHMAP)
        try {
             ou = new OutputStreamWriter(new FileOutputStream("morse_coded.txt"));
            while((ch = file.read()) != -1){
                ch = Character.toUpperCase(ch);
                //Integer c = ch;
                stat.makeNote((char)ch);

                if(ch == ' '){
                    ou.write("      ", 0, 6);
                }
                else if(ch == '\n'){
                    String str = abc.code('$') + System.lineSeparator();
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
