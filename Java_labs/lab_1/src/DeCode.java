import java.io.*;

class DeCode implements Handler{
    public void secret(InputStreamReader file, MorseABC abc) throws java.io.IOException {
        StatisticGen stat = new StatisticGen();
        int ch;
        int count = 0;
        StringBuilder strb = new StringBuilder();
        Writer ou = null;
        try{
            ou = new OutputStreamWriter(new FileOutputStream("eng_decoded.txt"));
            while((ch = file.read()) != -1){
                if(ch == ' '){
                    if(count == 0 && strb.length() != 0){
                        char c = abc.decode(strb.toString());
                        if(c == '$') ou.write("\n", 0, 1);
                        else ou.write(Character.toString(c), 0, 1);
                        strb = new StringBuilder();
                    }
                    ++count;
                }
                else{
                    if(count > 1){
                        for(int i = 0; i < count/6; i++) ou.write(" ", 0, 1);
                    }
                    count = 0;
                    strb.append((char)ch);
                }
                stat.makeNote((char)ch);
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