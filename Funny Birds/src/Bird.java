import java.awt.*;

public class Bird extends Actor {
    protected ActorCollection bulletCollection;


    @Override
    public void onIntersection(Actor act) {

        damage(act.damage);
    }

    @Override
    public void update(int ms) {
        super.update(ms);
        if(s.getY() < 0) {
            s.setY(0);
            down();
        }
        else if(s.getY() > 600) {
            s.setY(600);
            up();
        }
    }

    public ActorCollection getBulletCollection() {
        return bulletCollection;
    }

    public Bird(int X, int Y) {
       // body = new Sprite(x, y, "player.png", 0, 0, 110, 100);
        super(X, Y, "player.png", 0, 0, 110, 100, 10);

        damage = 100;

        up();

        int frame = -1;
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                frame++;
                if (frame == 0 || frame == 14) {
                    continue;
                }

                s.addFrame(110 * i, 100 * j);


            }
        }
        for (int n = 0; n < 5; n++){
            bulletCollection.addActor(new Bullet(s.getX(), s.getY(),"128309.png",0,0,110,100,h.getPad()));
        }
    }

}
