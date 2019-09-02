package javax.servlet.process;

import java.io.File;
import java.util.HashMap;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import javax.servlet.*;

public class XMLReader {

    private String path=HttpServer.Web_Root+"\\WEB-INF\\web.xml";
    private Map<String,String> servletMap =new HashMap<>();
    private Map<String,String> servletMapping=new HashMap<>();
    private Map<String,String> filterMap=new HashMap<>();
    private Map<String,String> filterMapping=new HashMap<>();
    public XMLReader(){
        readXMLFile(new File(path));
    }

    /**
     * 读XML文件进行解析
     * @param file xml文件
     */
    private void readXMLFile(File file){
        try {
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(file);
            NodeList servletList = doc.getElementsByTagName("servlet");
            for (int i = 0; i < servletList.getLength(); i++) {
                Node servletNode = servletList.item(i);
                if (servletNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) servletNode;
                    servletMap.put(element.getElementsByTagName("servlet-name").item(0).getTextContent(),element.getElementsByTagName("servlet-class").item(0).getTextContent());
                }
            }
            NodeList servletMappingList = doc.getElementsByTagName("servlet-mapping");
            for (int i = 0; i < servletMappingList.getLength(); i++) {
                Node servletMappingNode = servletMappingList.item(i);
                if (servletMappingNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) servletMappingNode;
                    servletMapping.put(element.getElementsByTagName("url-pattern").item(0).getTextContent(),element.getElementsByTagName("servlet-name").item(0).getTextContent());
                }
            }
            NodeList filterList = doc.getElementsByTagName("filter");
            for (int i = 0; i < filterList.getLength(); i++) {
                Node filterNode = filterList.item(i);
                if (filterNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) filterNode;
                    filterMap.put(element.getElementsByTagName("filter-name").item(0).getTextContent(),element.getElementsByTagName("filter-class").item(0).getTextContent());
                }
            }
            NodeList filterMappingList = doc.getElementsByTagName("filter-mapping");
//            System.out.println(servletMappingList.getLength());
            for (int i = 0; i < filterMappingList.getLength(); i++) {
                Node filterNode = filterMappingList.item(i);
                if (filterNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) filterNode;
                    filterMapping.put(element.getElementsByTagName("url-pattern").item(0).getTextContent(),element.getElementsByTagName("filter-name").item(0).getTextContent());
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 获取ServletMap
     * @return ServletMap
     */
    public Map<String, String> getServletMap() {
        return servletMap;
    }

    /**
     * 获取ServletMapping
     * @return ServletMapping
     */
    public Map<String, String> getServletMapping() {
        return servletMapping;
    }

    /**
     * 获取filterMap
     * @return filterMap
     */
    public Map<String, String> getFilterMap() {
        return filterMap;
    }

    /**
     * 获取filterMapping
     * @return filterMapping
     */
    public Map<String, String> getFilterMapping() {
        return filterMapping;
    }

    public static void main(String[] args) {
        XMLReader xmlReader=new XMLReader();
        xmlReader.readXMLFile(new File(xmlReader.path));
        System.out.println(xmlReader.servletMap);
        System.out.println(xmlReader.servletMapping);
    }
}
