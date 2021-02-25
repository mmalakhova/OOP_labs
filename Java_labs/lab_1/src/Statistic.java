import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.HashSet;
import java.util.Set;

class Statistic{
    private final Set<CharStat> stat;

    Statistic(){
        stat = new HashSet<>();
    }

    void makeNote(char ch){
        if(stat.add(new CharStat(ch))) return;
        for(CharStat s : stat){
            if(s.getCh() == ch) {
                s.incCh();
                break;
            }
        }
    }

    void printToFile(){
        try
                (
                        Writer ou = new OutputStreamWriter(new FileOutputStream("stat.st"))
                )
        {
            for(CharStat s : this.stat) {
                String str = s.getCh() + " " + s.getStat() + "\n";
                ou.write(str, 0, str.length());
            }
        }
        catch (IOException e){
            System.err.println("Error while writing file: " + e.getLocalizedMessage());
        }
    }
}



