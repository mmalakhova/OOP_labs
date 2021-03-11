import java.util.HashMap;
import java.util.Map;

public final class MorseABC{
    private final Map<Character, String> table_code = new HashMap<>() ;
   // private final Map<String, Character> table_decode = new HashMap<>();

    void makeNote(Character ch, String str){
        table_code.put(ch, str);
    }
//    void makeNote(String str, Character ch){
//        table_decode.put(str, ch);
//    }

    String code(Character ch){
        return table_code.get(ch);
    }

//    Character decode(String str) {
//        return table_decode.get(str);}
Character decode(String str){
    for(Character key : this.table_code.keySet()){
        if (this.table_code.get(key).equals(str)){
            return key;
        }
    }
    return 0;
}

}
