import std.stdio;
import std.file;
import std.string;
import std.regex;
import std.conv;
import std.algorithm.sorting;
import std.algorithm.searching;
import std.range;
import std.array;

struct Point {
    int x;
    int y;
}

enum Direction {X, Y}

struct Fold {
    Direction direction;
    int line;
}

void parseInput(string input, ref Point[] points, ref Fold[] directions){
    auto pointRegex = regex([`(\d+),(\d+)`]);
    auto directionRegex = regex([`fold along ([xy])=(\d+)`]);
    foreach(line ; lineSplitter(input)){
        const auto match = line.matchFirst(pointRegex);
        if (!match.empty){
            string xStr = match[1];
            string yStr = match[2];
            auto x = parse!int(xStr);
            auto y = parse!int(yStr);
            points ~= Point(x, y);
        } else {
            const auto match2 = line.matchFirst(directionRegex);
            if (!match2.empty){
                string axisStr = match2[1];
                string valueStr = match2[2];
                auto value = parse!int(valueStr);
	            Direction dir;
	            if (axisStr == "x"){
	                dir = Direction.X;
	            } else {
	                dir = Direction.Y;
	            }

                directions ~= Fold(dir, value);
            }
	    
	    }
    }
}

Point[] doFold(Point[] points, Fold fold){
    Point[] newPoints = new Point[0];
    if (fold.direction == Direction.X){
        foreach(point ; points){
            int x;
            int y = point.y;
            if (point.x > fold.line){
                x = fold.line - (point.x - fold.line);
            } else if(point.x == fold.line) {
                continue;
            } else {
                x = point.x;
            }
            newPoints ~= Point(x, y);
        }
    } else {
        foreach(point ; points){
            int x = point.x;
            int y;
            if (point.y > fold.line){
                y = fold.line - (point.y - fold.line);
            }  else if(point.y == fold.line) {
                continue;
            } else {
                y = point.y;
            }
            newPoints ~= Point(x, y);
        }
    }
    
    newPoints.sort!((a, b) => a.x == b.x ? a.y < b.y : a.x < b.x)();
    // create new array without duplicates
    Point[] noDuplicates = new Point[1];
    noDuplicates[0] = newPoints[0];
    foreach(point ; newPoints){
        if (noDuplicates.back != point){
            noDuplicates ~= point;
        }
    }

    return noDuplicates;
}

void visualize(Point[] points){
    int xSize = points.maxElement!"a.x".x + 1;
    int ySize = points.maxElement!"a.y".y + 1;
    char[][] pic = uninitializedArray!(char[][])(xSize, ySize);
    for (int x = 0; x < xSize; x++){
        for (int y = 0; y < ySize; y++){
            pic[x][y] = '.';
        }
    }

    foreach(point ; points){
        pic[point.x][point.y] = '#';
    }
    
    for (int y = 0; y < ySize; y++){
        string line = "";
        for (int x = 0; x < xSize; x++){
            line ~= pic[x][y];
        }
        writeln(line);
    }
}

int main(){
    string input = readText("input.txt");
    Point[] points = new Point[0];
    Fold[] folds = new Fold[0];
    parseInput(input, points, folds);
    
    auto newPoints = doFold(points, folds[0]);
    folds.popFront;

    writeln("Solution1: ", newPoints.length);

    foreach (fold ; folds){
        newPoints = doFold(newPoints, fold);
    }
    
    visualize(newPoints);

    return 0;
}
