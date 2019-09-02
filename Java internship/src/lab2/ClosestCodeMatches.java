package lab2;

import java.util.*;

public class ClosestCodeMatches implements CodeMatch {
    private String[] urls;
    public ClosestCodeMatches(String[] urls){
        this.urls=urls;

    }
    @Override
    public void codeMatch() {
        Set<String> urlSet=new HashSet<>(List.of(urls));
//        for (String str:urls){
//            urlSet.add(str);
//        }
        Map<String,StrDou> map=new HashMap<>();
        while (!urlSet.isEmpty()){
            String tmp=urlSet.iterator().next();
            urlSet.remove(tmp);
            CodeFile c=new CodeFile(tmp);
            for(String str:urlSet){
                double res=c.similarity(str);
                if (!map.containsKey(tmp)){
                    map.put(tmp,new StrDou(str,res));
                }else if (res>map.get(tmp).sim){
                    map.put(tmp,new StrDou(str,res));
                }
                if (!map.containsKey(str)){
                    map.put(str,new StrDou(tmp,res));
                }else if (res>map.get(str).sim){
                    map.put(str,new StrDou(tmp,res));
                }
            }
        }
        for (String str:urls){
            System.out.println(str+" | "+map.get(str).url+":"+map.get(str).sim);
        }
//        for (Map.Entry<String,StrDou> e:map.entrySet()){
//            System.out.println(e.getKey()+" | "+e.getValue().url+":"+e.getValue().sim);
//        }
    }

    public static void main(String[] args) {
        String[] strs=new String[4];
        strs[0]="./res/sample1.code";
        strs[1]="./res/sample2.code";
        strs[2]="./res/sample3.code";
        strs[3]="./res/sample4.code";
        ClosestCodeMatches closestCodeMatches=new ClosestCodeMatches(strs);
        closestCodeMatches.codeMatch();
    }
}
