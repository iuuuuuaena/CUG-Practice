package lab2;

public interface CodeMatch {
    public void codeMatch();
}

class Turl {
    public Turl(String u1, String u2){
        url1=u1;
        url2=u2;
    }
    public String url1;
    public String url2;
}

class StrDou{
    public String url;
    public double sim;
    public StrDou(String u,double s){
        url=u;
        sim=s;
    }
}