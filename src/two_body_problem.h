class Model{
public:

    float mass1, mass2, massTotal, q, ec, distance;
    float u [4];
    float coords [4];
    float time, step;

    Model(float, float);

    float* derivative();
    void updateCoord();
    void eulercalc();
    void writeToFile();
};