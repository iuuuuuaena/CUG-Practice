package LeetCode;

import java.util.Stack;
public class leetcode20 {
    public boolean isValid(String s) {
        Stack<Character> stack=new Stack<Character>();
        int len=s.length();
        for(int i=0;i<len;i++){
            if(stack.empty()){stack.push(s.charAt(i));}
            else if (s.charAt(i)==')'){
                if(stack.pop()!='(')return false;
            }
            else if (s.charAt(i)=='}'){
                if(stack.pop()!='{')return false;
            }
            else if (s.charAt(i)==']'){
                if(stack.pop()!='[')return false;
            }
            else stack.push(s.charAt(i));
        }
        if(stack.empty())return true;
        else return false;
    }
}
