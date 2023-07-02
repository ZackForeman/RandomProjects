#include <string>

using namespace std;

class Point {
    private:
        int x;
        int y;
    public:
        Point(int Ix,int Iy){
            x = Ix;
            y = Iy;            
        }
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
};

class SVG {
    private:
        string outputString = "";
    
    public:
        SVG(int width, int height){
            outputString += "<svg width=\"";
            outputString += to_string(width);
            outputString += "\" height=\"";
            outputString += to_string(height);
            outputString += "\" xmlns=\"http://www.w3.org/2000/svg\">";
        }

        void addLine(Point p1, Point p2, string colour, int strokeWidth){
            outputString += "<line x1=\"";
            outputString += to_string(p1.getX());
            outputString += "\" y1=\"";
            outputString += to_string(p1.getY());
            outputString += "\" x2=\"";
            outputString += to_string(p2.getX());
            outputString += "\" y2=\"";
            outputString += to_string(p2.getY());
            outputString += "\" stroke=\"";
            outputString += colour;
            outputString += "\" stroke-width=\"";
            outputString += to_string(strokeWidth);
            outputString += "\" />";
        }

        string getOutputString(){
            return outputString += "</svg>";
        }

};