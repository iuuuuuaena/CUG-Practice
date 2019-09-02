package javax.servlet.process;

import javax.servlet.HttpServer;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * 创建jsp所对应的Servlet
 */
public class JspProcess {
    private String className;
    private String jsp_path = "";
    private File jsp = null;
    private String content = "";
    private BufferedWriter out = null;
    private String method = "Get";

    JspProcess() {

    }

    /**
     * 处理请求为jsp的文件
     * @param request 链接的HttpServletRequest对象
     * @param response 链接的HttpServletResponse对象
     */
    public void process(HttpServletRequest request, HttpServletResponse response) {
        jsp_path = HttpServer.Web_Root + request.getUrl();
        String jsp_class = System.getProperty("user.dir") + "\\src\\jsp" + "\\" + request.getUrl().substring(1, request.getUrl().length() - 4) + "_jsp.java";
        jsp = new File(jsp_class);
        if (jsp.exists()) {
            //
//            System.out.println("jsp已存在,更新mapping");
            TomcatUI.addLog("jsp已存在,更新mapping");
            File jspFile = new File(jsp_path);
            className = jsp.getName().substring(0, jsp.getName().length() - 5);
            updateInfo();
            //
            return;
        }
        try {
            boolean b = jsp.createNewFile();
            out = new BufferedWriter(new FileWriter(jsp));
            File jspFile = new File(jsp_path);
            className = jsp.getName().substring(0, jsp.getName().length() - 5);
            setMethod(request.getMethod());
//            className =jspFile.getName().substring(0,jspFile.getName().length()-4);
//            byte[] bytes=new byte[(int)jspFile.length()];
//            FileInputStream stream=new FileInputStream(jspFile);
//            stream.read(bytes);
//            content=new String(bytes);
//            stream.close();
            readFile(jspFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
        updateInfo();
        head();
        parser();
        end();
    }

    /**
     * 读jsp文件
     * @param jspFile jsp文件
     */
    private void readFile(File jspFile) {
        StringBuilder result = new StringBuilder();
        try {
            String encoding = "utf-8";
            if (jspFile.isFile() && jspFile.exists()) { //判断文件是否存在
                InputStreamReader read = new InputStreamReader(new FileInputStream(jspFile), encoding);//考虑到编码格式
                BufferedReader bufferedReader = new BufferedReader(read);
                String lineTxt = null;
                while ((lineTxt = bufferedReader.readLine()) != null) {
                    result.append(lineTxt);
                }
                read.close();
            } else {
                System.out.println("找不到指定的文件");
            }
        } catch (Exception e) {
            System.out.println("读取文件内容出错");
            e.printStackTrace();
        }
        content = result.toString();
    }

    /**
     * 解析jsp文件
     */
    private void parser() {
        removePage();
        String regex = "<%(.*?)%>";
        List<String> list = new ArrayList<>();
        Pattern pattern = Pattern.compile(regex);
        Matcher m = pattern.matcher(content);
        while (m.find()) {
            int i = 1;
//            if (!m.group(i).contains("@ page")){
            list.add(m.group(i));
//            }
            ++i;
        }
        String[] strings = content.split(regex);
        int i = 0;
        try {
            while (i < list.size() && i < strings.length) {
//                System.out.println(strings[i]);
                writeStatic(strings[i]);
                String s = list.get(i);
                writeJsp(s);
                ++i;
            }
            if (i < strings.length) {
                writeStatic(strings[i]);
                ++i;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 写入动态内容
     * @param s 内容
     * @throws Exception
     */
    private void writeJsp(String s) throws Exception {
        //=:out.write("out.println("+s.substring(1,s.length())+");\n");
        s = s.replaceAll("request", "req");
        s = s.replaceAll("response", "resp");
        if (s.charAt(0) == '=') {
            s = s.substring(1, s.length());
            out.write("out.println(" + s + ");\n");
        } else {
            out.write(s + '\n');
        }
    }

    /**
     * 写静态html内容
     * @param s 内容
     * @throws Exception
     */
    private void writeStatic(String s) throws Exception {
//        String[] strings=s.split("\n");
////        System.out.println(strings.length);
//        for (String s1:strings){
        s=s.replaceAll("\"","\\\\\"");
        String wr = "out.println(\"" + s + "\");\n";
//            System.out.println(wr);
        out.write(wr);
//        }
    }

    /**
     * 处理头部
     */
    private void head() {
        try {
            out.write("package jsp;\n");
            out.write("import javax.servlet.*; \n" +
                    "import javax.servlet.http.*; \n" +
                    "import java.io.*; \n" +
                    "import java.text.*; \n" +
                    "import java.util.*; \n" +
                    "\n" +
                    "public class ");
            out.write(className);
            out.write(" extends HttpServlet { \n");
            out.write("public void do" + method + "(HttpServletRequest req, \n" +
                    "                       HttpServletResponse resp ) \n" +
                    "        throws ServletException, IOException {\n");
            out.write("resp.setContentType(\"text/html\"); \n" +
                    "\n" +
                    "        PrintWriter out = resp.getWriter(); \n");
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    /**
     * 修改相关属性
     */
    private void updateInfo() {
        HttpServer.servletMapping.put("/" + className.substring(0, className.length() - 4), className);
        HttpServer.servletMap.put(className, "jsp." + className);
        //TODO update web.xml
    }

    /**
     * 处理尾部
     */
    private void end() {
        try {
            out.write("out.close();");
            out.write("\n}\n}");
            out.flush();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 设置方法
     * @param s 方法名称
     */
    public void setMethod(String s) {
        String m = "Get";
        if (s.equals("POST")) m = "Post";
        this.method = m;
    }

    /**
     * 移除page
     */
    private void removePage() {
        if (content.indexOf("<%@") == 0) {
            content = content.substring(content.indexOf("%>") + 2, content.length());
        }
    }

    public static void main(String[] args) throws Exception {
        String jsp_path = HttpServer.Web_Root + "\\test2.jsp";
        File jspFile = new File(jsp_path);
//        System.out.println(jspFile.getName());
        byte[] bytes = new byte[(int) jspFile.length()];
        FileInputStream stream = new FileInputStream(jspFile);
        stream.read(bytes);
        String content = new String(bytes);
//        System.out.println(content);
        String regex = "<%(.*?)%>";
        List<String> list = new ArrayList<>();
        Pattern pattern = Pattern.compile(regex);
        Matcher m = pattern.matcher(content);
        while (m.find()) {
            int i = 1;
            list.add(m.group(i));
            ++i;
        }
//        System.out.println(list);
        String[] strings = content.split(regex);
        for (String s : strings) {
//            System.out.println(s);
            String[] stringss = s.split("\n");
//        System.out.println(strings.length);
//        System.out.println(strings[0]);
            for (String s1 : stringss) {
//            String wr="out.print(\""+s1+"\");\n";
//            System.out.println("out.print(\""+s1+"\");\n");
//            System.out.println("out.print(\"");
                System.out.println(s1);
                System.out.print(s1);
//            System.out.println("\");\n");
            }

        }
    }
}
