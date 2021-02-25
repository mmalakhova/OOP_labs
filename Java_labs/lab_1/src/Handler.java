import java.io.InputStreamReader;

interface Handler{
    void secret(InputStreamReader file, MorseABC abc) throws java.io.IOException;
}