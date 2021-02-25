import java.io.Writer;
import java.util.*;
import java.io.*;

class StatisticGen {
    private final Set<CharStat> stat;

    StatisticGen() {
        stat = new HashSet<>();
    }

    void makeNote(char ch) {
        if (stat.add(new CharStat(ch))) return;
        for (CharStat s : stat) {
            if (s.getCh() == ch) {
                s.incCh();
                break;
            }
        }
    }

    void printToFile() {
        Writer ou = null;
        try {
            ou = new OutputStreamWriter(new FileOutputStream("stat.txt"));

            for(CharStat s : this.stat) {
                    String str = s.getCh() + " " + s.getStat() + "\n";
                    ou.write(str, 0, str.length());
                }
            }
        catch(IOException e){
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