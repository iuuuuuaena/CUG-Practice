package lab2;

import java.util.*;

public class ClosestCodeMatch implements CodeMatch{
    private String[] urls;
    public ClosestCodeMatch(String[] urls){
        this.urls=urls;
    }
    @Override
    public void codeMatch() {
        Set<String> urlSet=new HashSet<>(List.of(urls));
//        for (String str:urls){
//            urlSet.add(str);
//        }
//        urlSet.addAll(List.of(urls));
        Map<Turl,Double> map=new HashMap<>();
        while (!urlSet.isEmpty()){
            String tmp=urlSet.iterator().next();
            urlSet.remove(tmp);
            CodeFile c=new CodeFile(tmp);
            for(String str:urlSet){
                double res=c.similarity(str);
                map.put(new Turl(tmp,str),res);
            }
        }
        List<Map.Entry<Turl,Double>> list=new ArrayList<>(map.entrySet());
        list.sort(new Comparator<Map.Entry<Turl, Double>>() {
            @Override
            public int compare(Map.Entry<Turl, Double> o1, Map.Entry<Turl, Double> o2) {
                return o2.getValue().compareTo(o1.getValue());
            }
        });
        System.out.println(list.get(0).getKey().url1+" | "+list.get(0).getKey().url2+":"+list.get(0).getValue());
//        for (int i=0;i<list.size();++i){
//            System.out.println(list.get(i).getKey().url1+" | "+list.get(i).getKey().url2+":"+list.get(i).getValue());
//        }
    }

    public static void main(String[] args) {
        String[] strs=new String[4];
        strs[0]="./res/sample1.code";
        strs[1]="./res/sample2.code";
        strs[2]="./res/sample3.code";
        strs[3]="./res/sample4.code";
        ClosestCodeMatch closestCodeMatch=new ClosestCodeMatch(strs);
        closestCodeMatch.codeMatch();
    }
}
