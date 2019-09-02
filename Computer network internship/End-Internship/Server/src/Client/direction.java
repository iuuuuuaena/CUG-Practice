package Client;

public enum direction{
    NORTH (0), SOUTH(1), EAST(2), WEST(3);
    private int value;
    direction(int i){
        this.value=i;
    }

    public int getValue() {
        return value;
    }

    public static direction valueOf(int i){
        try{
            if (i==0)return direction.NORTH;
            if (i==1)return direction.SOUTH;
            if (i==2)return direction.EAST;
            if (i==3)return direction.WEST;
            throw new Exception("Direction Error");
        }catch (Exception e){
            e.printStackTrace();
        }
        return null;
    }
}
