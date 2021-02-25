import java.io.*;
import java.util.*;


class Encryptor{
    public static void main(String[] args){
        Map<String, Handler> make = new HashMap<>();
        make.put("code", new Code());
        make.put("decode", new DeCode());
        Scanner scan = new Scanner(System.in);
        MorseABC abc = new MorseABC();
        BufferedReader readABC = null;
        //чтение азбуки Морзе(алфавит)
        try{
            readABC = new BufferedReader(new InputStreamReader(new FileInputStream("morseABC.txt")));
            String line;
            String[] splited;
            while((line = readABC.readLine()) != null){
                splited = line.split(" ");
                abc.makeNote(splited[0].charAt(0), splited[1]);
                abc.makeNote(splited[1], splited[0].charAt(0));
            }
        }
        catch (IOException e){
            System.err.println("Error while reading file: " + e.getLocalizedMessage());
        }
        finally {
            if (null != readABC) {
                try {
                    readABC.close();
                }
                catch (IOException e) {
                    e.printStackTrace(System.err);
                }
            }
        }

        //чтение и выполнение команд
        while(true){
            String[] comm;
            while(true){
                String command = scan.nextLine();
                if(command.equals("exit")) return;
                else{
                    comm = command.split(" ");
                    if((comm[0].equals("code") || comm[0].equals("decode")) && comm.length == 2){
                        break;
                    }
                    else{
                        System.out.println("Bad command");
                    }
                }
            }

            //кодированиие/декодирование текста
            InputStreamReader file = null;
            try{
                file = new InputStreamReader(new FileInputStream(comm[1]));
                make.get(comm[0]).secret(file, abc);
            }
            catch (IOException e){
                System.err.println("Error while reading file: " + e.getLocalizedMessage());
            }
            finally {
                if (null != file)
                {
                    try
                    {
                        file.close();
                    }
                    catch (IOException e)
                    {
                        e.printStackTrace(System.err);
                    }
                }
            }
        }
    }
}