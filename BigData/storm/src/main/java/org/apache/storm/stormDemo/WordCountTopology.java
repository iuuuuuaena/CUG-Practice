package org.apache.storm.stormDemo;

import org.apache.storm.spout.SpoutOutputCollector;
import org.apache.storm.task.ShellBolt;
import org.apache.storm.task.TopologyContext;
import org.apache.storm.topology.BasicOutputCollector;
import org.apache.storm.topology.IRichBolt;
import org.apache.storm.topology.OutputFieldsDeclarer;
import org.apache.storm.topology.TopologyBuilder;
import org.apache.storm.topology.base.BaseBasicBolt;
import org.apache.storm.topology.base.BaseRichSpout;
import org.apache.storm.tuple.Fields;
import org.apache.storm.tuple.Tuple;
import org.apache.storm.tuple.Values;
import org.apache.storm.utils.Utils;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class WordCountTopology {
    public static class RandomSentenceSpout extends BaseRichSpout {
        SpoutOutputCollector _collector;
        Random _rand;

        public void open(Map map, TopologyContext topologyContext, SpoutOutputCollector spoutOutputCollector) {
            _collector=spoutOutputCollector;
        }

        public void nextTuple() {
            Utils.sleep(100);
            String[] sentences = new String[]{ "the cow jumped over the moon", "an apple a day keeps the doctor away",
                    "four score and seven years ago", "snow white and the seven dwarfs", "i am at two with nature" };
            String sentence = sentences[_rand.nextInt(sentences.length)];
            _collector.emit(new Values(sentence));
        }

        public void declareOutputFields(OutputFieldsDeclarer declarer) {
            declarer.declare(new Fields("sentences"));
        }
    }
    public static class SplitSentence extends ShellBolt implements IRichBolt {

        public SplitSentence(){
            super("python","splitsentence.py");
        }

        public void declareOutputFields(OutputFieldsDeclarer outputFieldsDeclarer) {
            outputFieldsDeclarer.declare(new Fields("word"));
        }

        public Map<String, Object> getComponentConfiguration() {
            return null;
        }
    }
    public static class WordCount extends BaseBasicBolt {

        Map<String ,Integer> counts=new HashMap<>();


        public void execute(Tuple tuple, BasicOutputCollector basicOutputCollector) {
            String word=tuple.getString(0);
            Integer count=counts.get(word);
            if (count==null)count=0;
            count++;
            counts.put(word,count);
            basicOutputCollector.emit(new Values(word,count));
        }

        public void declareOutputFields(OutputFieldsDeclarer outputFieldsDeclarer) {
            outputFieldsDeclarer.declare(new Fields("word","count"));
        }
    }
    public static void main(String[] args) throws Exception {
        TopologyBuilder builder = new TopologyBuilder();
        builder.setSpout("sentences", new RandomSentenceSpout(), 5);
        builder.setBolt("split", new SplitSentence(), 8).shuffleGrouping("sentences");
        builder.setBolt("count", new WordCount(), 12).fieldsGrouping("split", new Fields("word"));
    }
}