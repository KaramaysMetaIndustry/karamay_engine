
interface Scriptable
{
    def construct();

    def tick(float deltaTime);

    def end();
}

class TraceFPS implements Scriptable
{

    @Override
    def construct() {
        print("TraceFPS has been constructed.")
    }

    @Override
    def tick(float deltaTime) {
        print("TraceFPS ticking.")
    }

    @Override
    def end() {
        print("TraceFPS end.")
    }
}