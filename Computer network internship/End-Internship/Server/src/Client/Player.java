package Client;

import java.awt.*;

public class Player {
    private Point position=new Point();
    private int HP;
    private int EXP;
    private String name;

    public Player(String name,int hp,int exp,int x,int y){
        this.name=name;
        this.HP=hp;
        this.EXP=exp;
        this.position.setLocation(x,y);
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

    public void move(int n){
        direction d= direction.valueOf(n);
        try {
            if (d==null)throw new Exception("d Null Point");
            switch (d){
                case NORTH:
                    position.y = (position.y+3)%100;
                    break;
                case SOUTH:
                    position.y = (position.y-3+100)%100;
                    break;
                case WEST:
                    position.x = (position.x-3+100)%100;
                    break;
                case EAST:
                    position.x = (position.x+3)%100;
                    break;
            }
        }catch (Exception e){
            e.printStackTrace();
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
