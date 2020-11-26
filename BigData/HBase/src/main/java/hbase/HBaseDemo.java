package hbase;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.client.*;
import org.apache.hadoop.hbase.util.Bytes;

import java.io.IOException;
import java.util.Arrays;

public class HBaseDemo {
    public static Configuration conf = null;
    public static Connection conn = null;
    public static Admin admin = null;

    public static void init() {
        conf = HBaseConfiguration.create();
        conf.set("hbase.zookeeper.quorum", "hbase");
        conf.set("hbase.zookeeper.property.clientPort", "2181");
//        conf.set("hbase.master", "hbase:16000");
//        conf.setInt("hbase.regionserver.port", 16201);
        conf.setInt("hbase.rpc.timeout", 2000);
        conf.setInt("hbase.client.operation.timeout", 3000);
        conf.setInt("hbase.client.scanner.timeout.period", 6000);

        try {
            conn = ConnectionFactory.createConnection(conf);
            admin = conn.getAdmin();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void close() {
        try {
            if (admin != null) {
                admin.close();
            }
            if (null != conn) {
                conn.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /*创建表*/
    /**
     * @param myTableName 表名
     * @param colFamily 列族数组
     * @throws Exception
     */
    public static void createTable(String myTableName,String[] colFamily) throws IOException {
        System.out.println(Arrays.toString(admin.listTables()));
        TableName tableName = TableName.valueOf(myTableName);
        if(admin.tableExists(tableName)){
            System.out.println("table exists!");
        }else {
            HTableDescriptor hTableDescriptor = new HTableDescriptor(tableName);
            for(String str: colFamily){
                HColumnDescriptor hColumnDescriptor = new HColumnDescriptor(str);
                hTableDescriptor.addFamily(hColumnDescriptor);
            }
            admin.createTable(hTableDescriptor);
        }
    }

    /*添加数据*/
    /**
     * @param tableName 表名
     * @param rowKey 行键
     * @param colFamily 列族
     * @param col 列限定符
     * @param val 数据
     * @throws IOException 异常
     */
    public static void insertData(String tableName, String rowKey, String colFamily, String col,
                                  String val) throws IOException {
        Table table = conn.getTable(TableName.valueOf(tableName));
        Put put = new Put(Bytes.toBytes(rowKey));
        put.addColumn(Bytes.toBytes(colFamily), Bytes.toBytes(col), Bytes.toBytes(val));
        table.put(put);
        table.close();
    }

    /*获取某单元格数据*/
    /**
     * @param tableName 表名
     * @param rowKey 行键
     * @param colFamily 列族
     * @param col 列限定符
     * @throws IOException 异常
     */
    public static void getData(String tableName,String rowKey,String colFamily,String
            col)throws IOException{
        Table table = conn.getTable(TableName.valueOf(tableName));
        Get get = new Get(Bytes.toBytes(rowKey));
        get.addColumn(Bytes.toBytes(colFamily),Bytes.toBytes(col));
//获取的result数据是结果集，还需要格式化输出想要的数据才行
        Result result = table.get(get);
        System.out.println(new
                String(result.getValue(colFamily.getBytes(), col.getBytes())));
        table.close();
    }


    public static void main(String[] args) throws IOException {
        init();
        createTable("student",new String[]{"score"});
        insertData("student","zhangsan","score","English","69");
        insertData("student","zhangsan","score","Math","86");
        insertData("student","zhangsan","score","Computer","77");
        getData("student", "zhangsan", "score", "English");
    }
}
