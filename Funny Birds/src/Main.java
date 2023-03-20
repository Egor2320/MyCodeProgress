import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {

        Sound.playSound("funny_birds.wav");

        new Window();
    }
}




class Texture {

    protected double x, y;

    protected BufferedImage  image = null;

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public Texture(double x, double y, String fileName) {
        this.x = x;
        this.y = y;

        try {
            image = ImageIO.read(new File(fileName));
        } catch (IOException e) {
            System.exit(1);
        }
    }

    public void paint(Graphics g) {
        g.drawImage(image, (int)x, (int)y, null );
    }


}


class Window extends JFrame {

    public Window()  {
        setExtendedState(MAXIMIZED_BOTH);
        setTitle("Мэйджик Бол");
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);

        KeyState keyState = new KeyState();
        addKeyListener(keyState);

        Panel p = new Panel(keyState);
        add(p);

        revalidate();
    }
}

class Panel extends JPanel {


    long t2, t1;

    ActorCollection collection = new ActorCollection();


    Actor b = new Bird(100, 100);
    Actor enemy = new Enemy();

    KeyState keyState;

    public Panel(KeyState keyState) {
        this.keyState = keyState;
        setFocusable(true);
        setBackground(Color.BLACK);

        t1 = System.currentTimeMillis();
    }

    private void controlGame() {

        b.stop();
        if(keyState.isKeyDown(KeyEvent.VK_W)) {
            b.up();
        }
        else if(keyState.isKeyDown(KeyEvent.VK_S)) {
            b.down();
        }
        else if(keyState.isKeyPress(KeyEvent.VK_INSERT)) {
            collection.addActor( new Enemy()  );
        }
        else if(keyState.isKeyPress((KeyEvent.VK_E))){


        }

    }

    private void updateGame(int ms) {
        b.update(ms);

        collection.intersects(b);
        collection.update(ms);

        keyState.update();

    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        t2 = System.currentTimeMillis();
        int ms = (int)(t2-t1);

        controlGame();
        updateGame(ms);

        b.paint(g);


        collection.paint(g);

        t1 = t2;
        repaint();
    }


}