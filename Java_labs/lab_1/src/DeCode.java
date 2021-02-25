import java.io.*;

class DeCode implements Handler{
    DeCode(){}
    public void secret(InputStreamReader file, MorseABC abc) throws java.io.IOException {
        Statistic stat = new Statistic();
        int ch;
        int count = 0;
        StringBuilder strb = new StringBuilder();
        try
                (
                        Writer ou = new OutputStreamWriter(new FileOutputStream("decoded.code"))
                )
        {
            while((ch = file.read()) != -1){
                if(ch == ' '){
                    if(count == 0 && strb.length() != 0){
                        char c = abc.getDeCode(strb.toString());
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
            if(strb.length() - 1 > 0){
                strb.deleteCharAt(strb.length() - 1);
                char c = abc.getDeCode(strb.toString());
                if(c == '$') ou.write("\n", 0, 1);
                else ou.write(Character.toString(c), 0, 1);
                //strb = new StringBuilder();
            }
            stat.printToFile();
        }
        catch (IOException e){
            System.err.println("Error while writing file: " + e.getLocalizedMessage());
        }
    }
}