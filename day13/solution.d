import std.stdio;
import std.file;
import std.string;
import std.regex;
import std.conv;

struct Point{
    int x;
    int y;
}

struct Fold{
    enum Direction {X, Y};
    int line;
}

void parseInput(string input, ref Point[] points, ref Fold[] directions){
    auto pointRegex = regex([`(\d+),(\d+)`]);
    foreach(line ; lineSplitter(input)){
        const auto match = line.matchFirst(pointRegex);
        if (!match.empty){
            string xStr = match[1];
            string yStr = match[2];
            auto x = parse!int(xStr);
            auto y = parse!int(yStr);
            points ~= Point(x, y);
        } 
    }

}

int main(){
    string input = readText("input.txt");
    Point[] points = new Point[0];
    Fold[] directions = new Fold[0];
    parseInput(input, points, directions);
    
    foreach(point ; points){
        writeln(point);
    }

    return 0;
}
