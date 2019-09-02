package javax.servlet.process;

import javax.servlet.HttpServer;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.util.HashSet;
import java.util.Set;
import java.util.regex.Pattern;

/**
 * 提供界面支持
 */
public class TomcatUI extends JFrame{
    public static Set<String> stringSet=new HashSet<>();
    private int port;
    private JFileChooser fileChooser=new JFileChooser();
    private boolean run=true;
    private static JTextArea textArea=new JTextArea();
    private JButton runButton=new JButton("run");
    private JButton stopBtn=new JButton("stop");
    private HttpServer httpServer=null;
    private TomcatUI(int port){
        super("MyTomcat");
        this.port=port;
        setUpUI();
        setSize(480,640);
        setLocationRelativeTo(null);
        setResizable(false);
        this.setVisible(true);
    }
    private void setUpUI(){
        int offsetX=100;
        Container contentPane=getContentPane();
        JFrame.setDefaultLookAndFeelDecorated(true);
        contentPane.setLayout(null);
        JLabel portLabel=new JLabel("Fill in the port:");
        portLabel.setBounds(offsetX,20,180,25);
        contentPane.add(portLabel);
        JButton chooseButton=new JButton("choose path");
        fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        chooseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int option=fileChooser.showDialog(null,null);
                if (option==JFileChooser.APPROVE_OPTION){
//                    System.out.println("change main path"+fileChooser.getSelectedFile().getPath());
                    textArea.append("change main path"+fileChooser.getSelectedFile().getPath()+'\n');
                    HttpServer.setWeb_Root(fileChooser.getSelectedFile().getPath());
                }
            }
        });
        chooseButton.setBounds(offsetX,60,120,20);
        contentPane.add(chooseButton);
        JTextField portIn=new JTextField(20);
        portIn.setBounds(offsetX+130,20,100,25);
        contentPane.add(portIn);
        //run
        runButton.setBounds(offsetX+130,60,60,20);
        runButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (portIn.getText().isEmpty()){
                    port=80;
                }
                else if (Pattern.compile("^[-\\+]?[\\d]*$").matcher(portIn.getText()).matches()&&Integer.valueOf(portIn.getText())>0) {
                    port = Integer.valueOf(portIn.getText()).intValue();
                }else {
                        port=80;
                }
                HttpServer.setPort(port);
                try{
                    httpServer=new HttpServer();
                    new Thread(httpServer).start();
                    Thread.sleep(50);
                    startBrowser();
                }catch (Exception e1){
                    addLog(e1.toString());
                }
                runButton.setEnabled(false);
                stopBtn.setEnabled(true);
            }
        });
        contentPane.add(runButton);
        //stop
        stopBtn.setBounds(offsetX+200,60,60,20);
        stopBtn.setEnabled(false);
        stopBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                httpServer.close();
                runButton.setEnabled(true);
                stopBtn.setEnabled(false);
            }
        });
        contentPane.add(stopBtn);
        //textLog
        textArea.setFont(new Font("宋体",Font.PLAIN,16));
        textArea.setLineWrap(true);
        JScrollPane js=new JScrollPane(textArea,JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        textArea.setBounds(10,90,440,500);
        js.setBounds(10,90,440,500);
        contentPane.add(js,null);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                for (String s:stringSet){
                    File f=new File(s);
                    f.delete();
                }
                System.exit(-1);
            }
        });
    }
    public static void addLog(String s){
        textArea.append(s+'\n');
    }
    private void startBrowser(){
        if (Desktop.isDesktopSupported()){
            try{
                java.net.URI uri=java.net.URI.create("http://localhost:"+port);
                Desktop dp= Desktop.getDesktop();
                if (dp.isSupported(Desktop.Action.BROWSE)){
                    dp.browse(uri);
                }
            }catch (Exception e){
                addLog(e.toString());
            }
        }
    }
    public static void main(String[] args) {
        new TomcatUI(80);
    }
}
