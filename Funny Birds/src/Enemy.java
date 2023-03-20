public class Enemy extends Actor {


    @Override
    public void update(int ms) {
        super.update(ms);
        if(s.getX() < - 500)  {
            respawn();
        }
    }

    public Enemy() {
        // body = new Sprite(x, y, "player.png", 0, 0, 110, 100);
        super(0, 0, "enemy.png", 0, 0, 110, 100, 10);

        damage = 30;



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
        left();
        respawn();
    }

    @Override
    public void onIntersection(Actor act) {

      /*  if (act instanceof Bird) */{
            kill();
            respawn();
        }

    }

    private void respawn() {
        s.setX(Math.random() * 1000);
        s.setY(Math.random() * 700);
        hp = 100;
        active = true;
    }
}
