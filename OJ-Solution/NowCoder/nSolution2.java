package nowcoder;

public class nSolution2 {
    public String replaceSpace(StringBuffer str) {
        int len=str.length();
        int amount=0;
        for(int i=0;i<len;i++){
            if (str.charAt(i)==' ')amount+=1;
        }
        int new_len=len+2*amount;
        str.setLength(new_len);
        int i=new_len-1;
        while (i>=0){
            char ch=str.charAt(len-1);
            if(ch==' '){str.replace(i-2,i+1,"%20");i-=3;len--;}
            else {str.setCharAt(i,ch);i--;len--;}
        }
        return str.toString();
    }
}

//用例:
//        "hello world"
//
//        对应输出应该为:
//
//        "hello%20world"
//
//        你的输出为:
//
//        "hell%20oworld"
