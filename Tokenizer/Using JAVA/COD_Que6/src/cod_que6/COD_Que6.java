package cod_que6;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class COD_Que6 {

    static String keyword, id, punc, literal, operator;

    static String removeSingleLineComments(String code) {
        String regex = "//.*?\\n";
        Pattern p = Pattern.compile(regex, Pattern.DOTALL);
        Matcher m = p.matcher(code);
        return (m.replaceAll(""));
    }

    static String removeMultiLineComments(String code) {
        String regex = "/\\*.*?\\*/";
        Pattern p = Pattern.compile(regex, Pattern.DOTALL);
        Matcher m = p.matcher(code);
        return (m.replaceAll(""));

    }

    static String removeLines(String code) {
        String regex = "\\n\\s*\\n";
        Pattern p = Pattern.compile(regex, Pattern.DOTALL);
        Matcher m = p.matcher(code);
        return (m.replaceAll("\n"));

    }
    
    static class TriPair
    {
        String a;
        String b;
        int c;
        TriPair(String x, String y, int z)
        {
            a = x;
            b = y;
            c = z;
        }
    }
    
    private static class MyComp implements Comparator {

        @Override
        public int compare(Object o1, Object o2) {
            
            TriPair t1,t2;
            t1 = (TriPair)(o1);
            t2 = (TriPair)(o2);
            if(t1.c < t2.c) return -1;
            return 1;
            
        }
    
    }

    public static void main(String[] args) throws FileNotFoundException, IOException {
        FileReader fr = new FileReader("helloworld.c");
        BufferedReader br = new BufferedReader(fr);
        String code = "";
        String line;
        while ((line = br.readLine()) != null) {
            code = code + line + "\n";
        }
        code = removeSingleLineComments(code);
        code = removeMultiLineComments(code);
        code = removeLines(code);

        System.out.println(code);

        keyword = "\\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|return|register|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b";
        id = "\\b([_A-Za-z][_A-Za-z0-9]*)\\b";
        operator = "\\+|\\-|\\*|\\/";
        punc = "[.#!?\\\\{}\\(\\)\\>\\<;]";
        literal = "\\\"([^\\\\\\\"]|\\\\.)*\\\"";
        
        HashMap<String, Integer> hm =  new HashMap<String,Integer>();
        
        ArrayList<TriPair> tokens = new ArrayList<>();
        
        Pattern p = Pattern.compile(literal);
        Matcher m = p.matcher(code);
        while (m.find()) {
            //System.out.print(code.substring(m.start(), m.end()));
            //System.out.println("-> string");
            
//            System.out.println("String = "+code.substring(m.start(),m.end()));
            String temp = code.substring(m.start(),m.end());
            System.out.println(temp.length());
            System.out.println(temp);
           // tokens.add(new TriPair(temp,"string",m.start()));
            code = code.replaceAll(literal, "");
            System.out.println(code);
        }
        //System.out.println("***********************************");
        
        p = Pattern.compile(keyword);
        m = p.matcher(code);
        while (m.find()) {
            String temp = code.substring(m.start(), m.end());
            //System.out.print(temp);
            tokens.add(new TriPair(temp,"keyword",m.start()));
            //System.out.println("-> Keyword");
            hm.put(temp,1);
        }
        //System.out.println("***********************************");
        p = Pattern.compile(id);
        m = p.matcher(code);
        while (m.find()) {
            String temp = code.substring(m.start(), m.end());
            if (hm.containsKey(temp))
                continue;
            //System.out.print(code.substring(m.start(), m.end()));
            tokens.add(new TriPair(temp,"identifier",m.start()));
            //System.out.println("-> identifier");
        }
        //System.out.println("***********************************");
        p = Pattern.compile(operator);
        m = p.matcher(code);
        while (m.find()) {
            //System.out.print(code.substring(m.start(), m.end()));
            //System.out.println("-> operator");
            String temp = code.substring(m.start(), m.end());
            tokens.add(new TriPair(temp,"operator",m.start()));
        }
        //System.out.println("***********************************");
        p = Pattern.compile(punc);
        m = p.matcher(code);
        while (m.find()) {
            //System.out.print(code.substring(m.start(), m.end()));
            //System.out.println("-> punctuator");
            String temp = code.substring(m.start(), m.end());
            tokens.add(new TriPair(temp,"punctuator",m.start()));
        }
        
       
        
        Collections.sort(tokens,new MyComp());
        
         for (int i=0;i<tokens.size();i++) {
            System.out.println(tokens.get(i).a + " -> " + tokens.get(i).b);
        }
        //System.out.println("***********************************");
        
    }
}
