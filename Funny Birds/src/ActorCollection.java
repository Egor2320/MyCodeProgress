import java.awt.*;
import java.lang.reflect.Array;
import java.util.ArrayList;

public class ActorCollection {

    private ArrayList <Actor> list = new ArrayList<>();

    public void addActor(Actor act) {
        list.add( act );
    }

    public void intersects (Actor act2) {
        for ( Actor act : list ) {
            act.intersects(act2);
        }
    }
    public void paint (Graphics g) {
        for ( Actor act : list ) {
            act.paint(g);
        }
    }
    public void update (int ms) {
        for( int i = list.size() - 1; i >=0 ; i-- ) {
            Actor act = list.get(i);
            if(act.active) {
                act.update(ms);
            }
            else {
                list.remove(i);
            }
        }

    }

}
