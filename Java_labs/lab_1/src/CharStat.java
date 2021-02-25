
class CharStat{
    private final char ch;
    private int stat;

    CharStat(char ch){
        this.ch = ch;
        this.stat = 1;
    }
    char getCh(){
        return ch;
    }

    int getStat(){
        return stat;
    }

    void incCh(){
        ++(stat);
    }

    public boolean equals(Object stat){
        if(stat == this) return true;
        if(stat == null || this.getClass() != stat.getClass()) return false;
        CharStat st = (CharStat)stat;
        return this.ch == st.ch;
    }

    public int hashCode(){
        return this.ch;
    }
}