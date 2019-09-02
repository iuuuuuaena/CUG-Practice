package lab2;

import static org.junit.Assert.*;
import org.junit.Test;

public class lab2Test {
    @Test
    public void testCodeFile(){
        String url1,url2;
        url1="./res/sample1.code";
        url2="./res/sample2.code";
        CodeFile c=new CodeFile(url1);
        assertEquals(0.939040909148062,c.similarity(url2),0.001);
        assertEquals(1.0,c.similarity(url1),0.001);
    }
}
