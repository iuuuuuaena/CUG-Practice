package LeetCode;

import java.util.Stack;
import java.lang.Integer;
public class leetcode150 {
    public int evalRPN(String[] tokens){
        Stack<Integer> s=new Stack<Integer>();
        int len=tokens.length;
        for(int i=0;i<len;i++){
            if (!isF(tokens[i])){
                s.push(Integer.valueOf(tokens[i]));
            }else {
                int b=s.pop().intValue();
                int a=s.pop().intValue();
                int res=0;
                if(tokens[i].equals("+")){res=a+b;}
                if(tokens[i].equals("-")){res=a-b;}
                if(tokens[i].equals("*")){res=a*b;}
                if(tokens[i].equals("/")){res=a/b;}
                s.push(res);
            }
        }
        return s.pop();
    }
    public boolean isF(String str){
        if(str.equals("+")||str.equals("-")||str.equals("*")||str.equals("/")){
            return true;
        }else return false;
    }
}
