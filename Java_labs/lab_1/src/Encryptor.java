import java.io.*;
import java.util.*;


class Encryptor{
    public static void main(String[] args){
        Map<String, Handler> make = new HashMap<>();
        make.put("code", new Code());
        make.put("decode", new DeCode());
        Scanner scan = new Scanner(System.in);
        MorseABC abc = new MorseABC();
        try
                (
                        BufferedReader readABC = new BufferedReader(new InputStreamReader(new FileInputStream("morse.abc")))
                )
        {
            String line;
            String[] splited;
            while((line = readABC.readLine()) != null){
                splited = line.split(" ");
                abc.makeNote(splited[0].charAt(0), splited[1]);
            }
        }
        catch (IOException e){
            System.err.println("Error while reading file: " + e.getLocalizedMessage());
        }
        while(true){
            String[] comm;
            while(true){
                System.out.print("> ");
                String command = scan.nextLine();
                if(command.equals("exit")) return;
//                else if(command.equals("help")){
//                    System.out.println("\n=============================\n\t  COMMANDS:\n=============================\n  code FILE - encrypt file.\n decode FILE - decrypt file.\n    exit - stop program.\n=============================\n");
//                }
                else{
                    comm = command.split(" ");
                    if((comm[0].equals("code") || comm[0].equals("decode")) && comm.length == 2){
                        break;
                    }
                    else{
                        System.out.println("!Bad command format. Type 'help' for instructions.");
                    }
                }
            }
            try
                    (
                            InputStreamReader file = new InputStreamReader(new FileInputStream(comm[1]))
                    )
            {
                make.get(comm[0]).secret(file, abc);
            }
            catch (IOException e){
                System.err.println("Error while reading file: " + e.getLocalizedMessage());
            }
        }
    }
}