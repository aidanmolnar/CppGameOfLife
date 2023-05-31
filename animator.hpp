class Animator
{
public:
    virtual void draw() = 0;

    void play(int frame_time); // frame time in milliseconds

    virtual ~Animator(){};
};
