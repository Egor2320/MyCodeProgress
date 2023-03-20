import java.awt.*;

public class Hitbox {

    private Rectangle r;
    private int pad;

    public Hitbox (int pad, int x, int y, int w, int h) {
        r = new Rectangle( x + pad,  y + pad,  w - 2*pad,  h-2*pad);
        this.pad = pad;
    }

    public void update (int x, int y) {
        r.x = x;
        r.y = y;
    }

    public boolean intersects(Hitbox hb) {
        return this.r.intersects(  hb.r   );
    }

    public int getPad() {
        return pad;
    }
}
