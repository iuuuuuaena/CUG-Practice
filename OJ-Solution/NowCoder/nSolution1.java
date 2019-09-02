package nowcoder;

public class nSolution1 {
    public boolean Find(int target, int [][] array) {
        int col=array[0].length-1;
        int row=0;
        while (row<array.length&&col>=0){
            int temp=array[row][col];
            if (temp==target)return true;
            else if (temp>target)col-=1;
            else row+=1;
        }
        return false;
    }
}
