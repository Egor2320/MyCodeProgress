import java.awt.*;

public class Bullet extends Actor {
    double _x;
    double _y;
    public Bullet(double x, double y, String fileName, int frameX, int frameY, int w, int h, int pad) {
        super(x, y, "128309.png", frameX, frameY, w, h, pad);
        double _x = x;
        double _y = y;
        active = false;
        defaultSpeed = 0;
    }
    public void respawn1(){
        s.setX(_x);
        s.setY(_y);
    }

    @Override
    public void onIntersection(Actor act) {
        kill();
        defaultSpeed = 0;
    }
    public void shoot(){
        active = true;
        defaultSpeed = 100;
        right();
    }

    @Override
    public void update(int ms) {
        super.update(ms);
        if(s.getX()>1000){
            respawn1();
        }
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
    }
}
