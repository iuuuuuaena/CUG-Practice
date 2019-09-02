package Player;

import java.awt.Point;

public class Player
{
    private Point position;
    private int HP;
    private int EXP;
    private String name;

    public Player(String name)
    {
        this.name = name;
        this.position = new Point();
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setHP(int HP) {
        this.HP = HP;
    }

    public void setEXP(int EXP) {
        this.EXP = EXP;
    }

    public void setPoint(int x,int y) {
        this.position.x=x;
        this.position.y=y;
    }

    public void move(int n)
    {
        direction d=direction.valueOf(n);
        switch (d)
        {
            case NORTH:
                position.y += 3;
                break;
            case SOUTH:
                position.y -= 3;
                break;
            case WEST:
                position.x -= 3;
                break;
            case EAST:
                position.x += 3;
                break;
        }
    }

    public String getName() {
        return name;
    }

    public int getEXP() {
        return EXP;
    }

    public int getHP() {
        return HP;
    }

    public Point getPosition() {
        return position;
    }
}


enum direction{
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

