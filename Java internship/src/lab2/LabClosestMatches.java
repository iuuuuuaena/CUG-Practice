package lab2;
/**
 *
 */
import jdk.jshell.spi.ExecutionControl;

import java.io.File;
import java.util.*;
import java.util.regex.*;

/**
 * @author 20171001234 xxx
 *
 *假设在 codes/lab1/目录下存在以下结构的文件组织：
 *├─Java课内实习-201710001234-xxx-实习1
 *│  ├─Java课内实习-20171000123-xxx-实习1
 *│  │  └─lab1_code
 *│  │      ├─rules
 *│  │      └─turtle
 *│  └─lab1_code
 *│      ├─rules
 *│      └─turtle
 *├─Java课内实习-20171001235-xxx-实习一
 *│  └─lab1
 *│      └─lab1_code
 *│          └─lab1_code
 *│              ├─bin
 *│              │  ├─rules
 *│              │  └─turtle
 *│              ├─rules
 *│              └─turtle
 *├─Java课内实习-20171001236-xxxx-实习一
 *│  ├─rules
 *│  └─turtle
 *└─Java课内实习20171001237-xxxx-实习一
 *    └─Java课内实习20171001237-xxx-实习一
 *       └─Java课内实习20171001237-xxxx-实习一
 *            └─lab1_code
 *               ├─123
 *                ├─rules
 *                │  └─bin
 *               └─turtle
 *                    └─bin
 *
 */
public class LabClosestMatches {
    public List<List<String>> pathss=new ArrayList<>();
    public void findFile(File file,String fileNameMatches,int i){
        File[] fs=file.listFiles();
        for (File f:fs){
            if (f.isDirectory()){
                findFile(f,fileNameMatches,i);
            }
            if (f.isFile()){
                if (Pattern.matches(fileNameMatches,f.toString())){
                    pathss.get(i).add(f.toString());
//                    System.out.println(f.toString());
                }
            }
        }
    }
    /**
     * 用于评价各相关目录下，指定文件的相似性。
     * Similarity   子目录1                        子目录2
     * 100%        Java课内实习-201710001234-xxx-实习1     Java课内实习-201710001235-xxx-实习1
     * 89%         Java课内实习-201710001234-xxx-实习1     Java课内实习-201710001236-xxx-实习1
     * ....
     * @param path 作业文件所在的目录，比如这里是：codes/lab1
     * @param fileNameMatches：用来过滤进行比较的文件名的文件名或者正则表达式.
     * 如 "DrawableTurtle.java"，"*.java","turtle/*.java"
     * 如果一个子目录下有多个符合条件的文件，将多个文件合并成一个文件。
     *
     * @param topRate:取值范围从[0,100],输出控制的阈值
     * 	从高往低输出高于topRate%相似列表，如
     * @param removeComments:是否移除注释内容
     * 	 */
    public static void closestCodes(String path, String fileNameMatches,double topRate,boolean removeComments)
    {
        File file=new File(path);
        File[] fs=file.listFiles();
        int i=0;
        LabClosestMatches labClosestMatches=new LabClosestMatches();
        for (File f:fs){
            labClosestMatches.pathss.add(new ArrayList<>());
            labClosestMatches.findFile(f,fileNameMatches,i);
            ++i;
        }
        Set<List<String>> urlSet=new HashSet<>();
        Map<List<String>,File> ms=new HashMap<>();
        i=0;
        for (List<String> str:labClosestMatches.pathss){
            urlSet.add(str);
            ms.put(str,fs[i]);++i;
        }
        Map<Turl,Double> map=new HashMap<>();
        while (!urlSet.isEmpty()){
            List<String> tmp=urlSet.iterator().next();
            urlSet.remove(tmp);
            CodeFile c=new CodeFile(tmp,removeComments);
            for(List<String> str:urlSet){
                double res=c.similarity(str,removeComments);
                map.put(new Turl(ms.get(tmp).getName(),ms.get(str).getName()),res);
            }
        }
        List<Map.Entry<Turl,Double>> list=new ArrayList<>(map.entrySet());
        list.sort(new Comparator<Map.Entry<Turl, Double>>() {
            @Override
            public int compare(Map.Entry<Turl, Double> o1, Map.Entry<Turl, Double> o2) {
                return o2.getValue().compareTo(o1.getValue());
            }
        });
        System.out.format("%-10s %20s %40s\n","Similarity","子目录1","子目录2");
        for (i=0;i<list.size();++i){
            if (list.get(i).getValue()*100>topRate){
                System.out.format("%4.0f%-6s %-40s %-40s\n",list.get(i).getValue()*100,"%",list.get(i).getKey().url2,list.get(i).getKey().url1);
            }
        }
        // 计算文件间的相似性，输出
    }
    /**
     * @param args
     */
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        String path="./res/lab1-codes-fortest";
        String fileNameMatches=".*TurtleSoup.java";
        double topRate=80;
        LabClosestMatches.closestCodes(path,fileNameMatches,topRate,true);
    }

}

