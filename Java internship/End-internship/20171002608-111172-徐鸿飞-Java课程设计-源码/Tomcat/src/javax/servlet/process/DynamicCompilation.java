package javax.servlet.process;

import java.io.File;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;
public class DynamicCompilation{
    public static String JAVA_PATH=System.getProperty("user.dir")+"/src/jsp";
    public static String CLASS_PATH=System.getProperty("user.dir")+"/out/production/Tomcat/jsp";
    private String className;

    /**
     * 动态编译指定的文件,若已经便宜,则不再编译
     * @param path
     */
    public DynamicCompilation(String path){
        className=path.substring(0,path.length()-5);
        String java_path=JAVA_PATH+"/"+path;
        File f=new File(JAVA_PATH+"/"+path.substring(0,path.length()-5)+".class");
        if (f.exists()){
//            System.out.println("已编译");
            TomcatUI.addLog("已编译");
            return;
        }
//        System.out.println("动态编译jsp_servlet");
        TomcatUI.addLog("动态编译jsp_servlet");
        JavaCompiler compiler=ToolProvider.getSystemJavaCompiler();
        int result=compiler.run(null,null,null,java_path);
        TomcatUI.stringSet.add(f.getPath());
        System.out.println(result==0?"成功":"失败");
    }

    /**
     * ClassLoader反射动态编译的类
     * @param request
     * @param response
     */
    public void process(HttpServletRequest request, HttpServletResponse response){
        try{//
//            System.out.println("DynamicCompilation类:process");
            TomcatUI.addLog("DynamicCompilation类:process");
            URL[] urls=new URL[]{new URL("file:"+System.getProperty("user.dir")+"/src/")};
            URLClassLoader loader=new URLClassLoader(urls);
            Class<?> c=loader.loadClass("jsp."+className);
            HttpServlet servlet=(HttpServlet) c.getConstructor().newInstance();
            Method m=c.getMethod("service",HttpServletRequest.class,HttpServletResponse.class);
            m.invoke(servlet,request,response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}