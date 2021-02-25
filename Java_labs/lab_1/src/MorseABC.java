import java.util.HashMap;
import java.util.Map;

public final class MorseABC{
    private final Map<Character, String> table;

    MorseABC(){
        table = new HashMap<>();
    }

    void makeNote(Character ch, String str){
        table.put(ch, str);
    }

    String getCode(Character ch){
        return table.get(ch);
    }

    Character getDeCode(String str){
        for(Character key : table.keySet()){
            if (table.get(key).equals(str)){
                return key;
            }
        }
        return null;
    }
}
