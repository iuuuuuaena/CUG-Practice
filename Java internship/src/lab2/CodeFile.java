package lab2;

import java.io.File;
import java.io.FileInputStream;
import java.util.*;
import java.lang.Math;

public class CodeFile {
    private String url;
    private Set<String> wordSet;
    private Map<String,Integer> map1;
    public CodeFile(String url){
        this.url=url;
        wordSet=new HashSet<>();
        map1=new HashMap<>();
        try {
            Scanner scanner=new Scanner(new File(url));
            String str;
            while (scanner.hasNext()){
                str=scanner.next();
//                System.out.println(str);
                wordSet.add(str);
                if (!map1.containsKey(str)){
                    map1.put(str,1);
                }else {
                    map1.put(str,map1.get(str).intValue()+1);
                }
            }
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public double similarity(String url2){
        Map<String,Integer> map2=new HashMap<>();
        Set<String> tempSet=new HashSet<>(wordSet);
        try {
            Scanner scanner=new Scanner(new File(url2));
            String str;
            while (scanner.hasNext()){
                str=scanner.next();
//                System.out.println(str);
                tempSet.add(str);
                if (!map2.containsKey(str)){
                    map2.put(str,1);
                }else {
                    map2.put(str,map2.get(str).intValue()+1);
                }
            }
        }catch (Exception e){
            System.out.println(e.toString());
        }
        int[] A=new int[tempSet.size()];
        int[] B=new int[tempSet.size()];
        int i=0;
        for (String str: tempSet) {
            A[i]=map1.get(str)!=null?map1.get(str).intValue():0;
            B[i]=map2.get(str)!=null?map2.get(str).intValue():0;
            ++i;
        }
        double res,a=0,b=0,c=0;
        for (i=0;i<tempSet.size();++i){
            c+=A[i]*B[i];
            a+=Math.pow(A[i],2);
            b+=Math.pow(B[i],2);
        }
        res=c/(Math.sqrt(a*b));
        tempSet.clear();
        return res;
    }
    public CodeFile(List<String> urls,boolean removeComments){
        wordSet=new HashSet<>();
        map1=new HashMap<>();
        try {
            for (String path:urls){
                if (removeComments){
                    boolean flag=true;
                    Scanner scanner=new Scanner(new File(path));
                    String str;
                    while (scanner.hasNext()){
                        str=scanner.next();
                        if (flag){
                            if (str.length()>=2&&str.charAt(0)=='/'&&str.charAt(1)=='*'){
                                flag=false;
                            }else if (str.length()>=2&&str.charAt(0)=='/'&&str.charAt(1)=='/'){
                                continue;
                            }else {
                                wordSet.add(str);
                                if (!map1.containsKey(str)){
                                    map1.put(str,1);
                                }else {
                                    map1.put(str,map1.get(str).intValue()+1);
                                }
                            }
                        }else {
                            if (str.length()>=2&&str.charAt(str.length()-2)=='*'&&str.charAt(str.length()-1)=='/'){
                                flag=true;
                            }
                        }
                    }
//                    File f=new File(path);
//                    byte[] content=new byte[Long.valueOf(f.length()).intValue()];
//                    FileInputStream in=new FileInputStream(f);
//                    in.read(content);
//                    String s=new String(content,"utf-8");
//                    String[] strs=s.split("(/\\*{1,2}(.|\\s)*\\*/)|(//( |\t|.)+\n)|(\\s+)");//"[([\\s\n]+)(/\\*\\*.*\\*/)(//.*\n)]"
//                    for (String str:strs){
//                        wordSet.add(str);
//                        if (!map1.containsKey(str)){
//                            map1.put(str,1);
//                        }else {
//                            map1.put(str,map1.get(str).intValue()+1);
//                        }
//                    }
                }else {
                    Scanner scanner=new Scanner(new File(path));
                    String str;
                    while (scanner.hasNext()){
                        str=scanner.next();
                        wordSet.add(str);
                        if (!map1.containsKey(str)){
                            map1.put(str,1);
                        }else {
                            map1.put(str,map1.get(str).intValue()+1);
                        }
                    }
                }
            }
        }catch (Exception e){
            System.out.println(e.toString());
        }
    }
    public double similarity(List<String> urls2,boolean removeComments){
        Map<String,Integer> map2=new HashMap<>();
        Set<String> tempSet=new HashSet<>(wordSet);
        try {
            for (String url2:urls2){
                if (removeComments){
                    boolean flag=true;
                    Scanner scanner=new Scanner(new File(url2));
                    String str;
                    while (scanner.hasNext()){
                        str=scanner.next();
                        if (flag){
                            if (str.length()>=2&&str.charAt(0)=='/'&&str.charAt(1)=='*'){
                                flag=false;
                            }else if (str.length()>=2&&str.charAt(0)=='/'&&str.charAt(1)=='/'){
                                continue;
                            }else {
                                tempSet.add(str);
                                if (!map2.containsKey(str)){
                                    map2.put(str,1);
                                }else {
                                    map2.put(str,map2.get(str).intValue()+1);
                                }
                            }
                        }else {
                            if (str.length()>=2&&str.charAt(str.length()-2)=='*'&&str.charAt(str.length()-1)=='/'){
                                flag=true;
                            }
                        }
                    }
//                    File f=new File(url2);
//                    byte[] content=new byte[Long.valueOf(f.length()).intValue()];
//                    FileInputStream in=new FileInputStream(f);
//                    in.read(content);
//                    String s=new String(content,"utf-8");
//                    String[] strs=s.split("(/\\*{1,2}(.|\\s)*\\*/)|(//( |\t|.)+\n)|(\\s+)");
//                    for (String str:strs){
//                        wordSet.add(str);
//                        if (!map2.containsKey(str)){
//                            map2.put(str,1);
//                        }else {
//                            map2.put(str,map2.get(str).intValue()+1);
//                        }
//                    }
                }else {
                    Scanner scanner=new Scanner(new File(url2));
                    String str;
                    while (scanner.hasNext()){
                        str=scanner.next();
//                System.out.println(str);
                        tempSet.add(str);
                        if (!map2.containsKey(str)){
                            map2.put(str,1);
                        }else {
                            map2.put(str,map2.get(str).intValue()+1);
                        }
                    }
                }

            }
        }catch (Exception e){
            System.out.println(e.toString());
        }
        int[] A=new int[tempSet.size()];
        int[] B=new int[tempSet.size()];
        int i=0;
        for (String str: tempSet) {
            A[i]=map1.get(str)!=null?map1.get(str).intValue():0;
            B[i]=map2.get(str)!=null?map2.get(str).intValue():0;
            ++i;
        }
        double res,a=0,b=0,c=0;
        for (i=0;i<tempSet.size();++i){
            c+=A[i]*B[i];
            a+=Math.pow(A[i],2);
            b+=Math.pow(B[i],2);
        }
        res=c/(Math.sqrt(a*b));
        tempSet.clear();
        return res;
    }
    @Override
    public String toString() {
        return url;
    }

    public static void main(String[] args) {
        String url1="./res/sample1.code";
        String url2="./res/sample2.code";
		
        CodeFile c=new CodeFile(url1);
        System.out.println(c.similarity(url2));
    }
}
