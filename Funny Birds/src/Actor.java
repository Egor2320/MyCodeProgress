import java.awt.*;

abstract public class Actor {

    protected boolean  active;
    protected int      damage;
    protected int      hp ;
    protected Sprite   s;
    protected Hitbox   h;
    protected double      defaultSpeed;

    public Actor (double x, double y, String fileName, int frameX, int frameY, int w, int h, int pad) {
        this.s = new Sprite(x, y, fileName, frameX, frameY, w, h);
        this.h = new Hitbox(pad, (int)x, (int)y, w, h);
        hp = 100;
        damage = 0;
        active = true;
        defaultSpeed  = this.s.getSpeed();
    }



    abstract public void onIntersection(Actor act);

    public void intersects(Actor act) {

       if( h.intersects( act.h) && active && act.active   ) {
           onIntersection(act);
           act.onIntersection(this);
       }

    }

    public void kill() {
        hp = 0;
        active = false;
    }

    public void update(int ms) {
        if(active) {
            s.update(ms);
            h.update((int)s.getX(), (int)s.getY());
        }

    }

    public void paint(Graphics g) {
        if(active) {
            s.paint(g);
        }
    }

    public void damage(int damage) {
        hp -= damage;
        if(hp <= 0) {
           kill();
        }
    }

    public void stop () {
        s.setSpeed(0);
    }

    public void left () {
        s.setSpeed( defaultSpeed );
        s.setAngle(Math.PI);
    }

    public void up () {
        s.setSpeed( defaultSpeed );
        s.setAngle(- Math.PI / 2);
    }

    public void down () {
        s.setSpeed( defaultSpeed );
        s.setAngle(Math.PI / 2);
    }
    public void right(){
        s.setSpeed( defaultSpeed );
        s.setAngle(0);
    }


}
